// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/httpsessionadapter.h>
#include <Interfaces/IHttpRequest.h>

/**
 * Implementation of the configcat::HttpSessionAdapter so we can handle HTTP requests directly inside Unreal
 */
class ConfigCatNetworkAdapter : public configcat::HttpSessionAdapter
{
public:
	explicit ConfigCatNetworkAdapter() = default;
	virtual ~ConfigCatNetworkAdapter() override = default;

	void WaitForNextRequest();

private:
	// Begin configcat::HttpSessionAdapter interface
	virtual bool init(const configcat::HttpSessionObserver* httpSessionObserver, uint32_t connectTimeoutMs, uint32_t readTimeoutMs) override;
	virtual configcat::Response
	get(const std::string& url,
		const std::map<std::string, std::string>& header,
		const std::map<std::string, std::string>& proxies,
		const std::map<std::string, configcat::ProxyAuthentication>& proxyAuthentications) override;
	virtual void close() override;
	// End configcat::HttpSessionAdapter interface
	/*
	 * The number of milliseconds to wait for the server to make the initial connection
	 */
	int32 ConnectionTimeout = 0;
	/*
	 * The number of milliseconds to wait for the server to respond before giving up.
	 */
	int32 ReadTimeout = 0;
	/**
	 * HTTP request currently being executed
	 */
	FHttpRequestPtr GetRequest;
};
