// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCatNetworkAdapter.h"

#include <HttpManager.h>
#include <HttpModule.h>
#include <Interfaces/IHttpResponse.h>

#include "ConfigCatLog.h"

using namespace configcat;

bool ConfigCatNetworkAdapter::init(const HttpSessionObserver* httpSessionObserver, uint32_t connectTimeoutMs, uint32_t readTimeoutMs)
{
	UE_LOG(LogConfigCat, Verbose, TEXT("Network Adapter initialized."));

	ConnectionTimeout = connectTimeoutMs;
	ReadTimeout = readTimeoutMs;

	return true;
}

Response ConfigCatNetworkAdapter::get(
	const std::string& url, const std::map<std::string, std::string>& header, const std::map<std::string, std::string>& proxies, const std::map<std::string, ProxyAuthentication>& proxyAuthentications
)
{
	GetRequest = FHttpModule::Get().CreateRequest();
	ON_SCOPE_EXIT
	{
		GetRequest.Reset();
	};

	GetRequest->SetVerb(TEXT("GET"));

	// TODO: Check if we can set each of the 2 separately
	const float Timeout = (ConnectionTimeout + ReadTimeout) / 1000.0f;
	GetRequest->SetTimeout(Timeout);

	for (const auto& it : header)
	{
		const FString HeaderKey = UTF8_TO_TCHAR(it.first.c_str());
		const FString HeaderValue = UTF8_TO_TCHAR(it.second.c_str());
		GetRequest->SetHeader(HeaderKey, HeaderValue);
	}

	const FString Url = UTF8_TO_TCHAR(url.c_str());
	GetRequest->SetURL(Url);

	// TODO: Check if we can set up any proxy
	/*
	const std::string protocol = url.substr(0, url.find(':'));
	if (proxies.contains(protocol))
	{
		curl_easy_setopt(curl, CURLOPT_PROXY, proxies.at(protocol).c_str());
		if (proxyAuthentications.contains(protocol))
		{
			curl_easy_setopt(curl, CURLOPT_PROXYUSERNAME, proxyAuthentications.at(protocol).user.c_str());
			curl_easy_setopt(curl, CURLOPT_PROXYPASSWORD, proxyAuthentications.at(protocol).password.c_str());
		}
	}
	*/

	GetRequest->SetDelegateThreadPolicy(EHttpRequestDelegateThreadPolicy::CompleteOnHttpThread);
	GetRequest->ProcessRequest();

	while (GetRequest->GetStatus() == EHttpRequestStatus::Processing)
	{
		constexpr float SleepInterval = 0.05f;
		UE_LOG(LogConfigCat, Verbose, TEXT("Waiting for Get response (IsGameThread: %s). Retrying in %s second."), *LexToString(IsInGameThread()), *LexToString(SleepInterval));

		// The cpp-sdk excepts this function to bock execution until the HTTP request is finished, therefore:
		// - for requests running on the main thread (game thread), we need to manually tick the HTTP Module to process the request
		// - for requests running on any other thread, we just wait until for the HTTP module to process the request
		if (IsInGameThread())
		{
			FHttpModule::Get().GetHttpManager().Tick(SleepInterval);
		}

		FPlatformProcess::Sleep(SleepInterval);
	}

	const FHttpResponsePtr GetResponse = GetRequest->GetResponse();
	Response Response;
	if (!GetResponse)
	{
		Response.error = "Unreal Engine Network Adapter failed to launch request. Check logs";
		Response.operationTimedOut = GetRequest->GetElapsedTime() > Timeout;
		return Response;
	}

	Response.text = TCHAR_TO_UTF8(*GetResponse->GetContentAsString());
	Response.statusCode = GetResponse->GetResponseCode();

	for (const FString Header : GetResponse->GetAllHeaders())
	{
		FString HeaderKey;
		FString HeaderValue;
		if (Header.Split(TEXT(":"), &HeaderKey, &HeaderValue))
		{
			const std::string KeyString = TCHAR_TO_UTF8(*HeaderKey);
			const std::string KeyValue = TCHAR_TO_UTF8(*HeaderValue);
			Response.header[KeyString] = KeyValue;
		}
	}

	return Response;
}

void ConfigCatNetworkAdapter::close()
{
	UE_LOG(LogConfigCat, Verbose, TEXT("Network Adapter canceling on-going requests."));

	if (GetRequest && GetRequest->GetStatus() == EHttpRequestStatus::Processing)
	{
		GetRequest->CancelRequest();
	}
}
