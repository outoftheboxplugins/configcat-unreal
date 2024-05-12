﻿// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/configcatuser.h>

#include <memory>

#include "ConfigCatUserWrapper.generated.h"

UCLASS(DisplayName="Config Cat User", Hidden)
class CONFIGCAT_API UConfigCatUserWrapper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	static UConfigCatUserWrapper* CreateUser(const FString& Id, const FString& Email, const FString& Country, const TMap<FString, FString>& Attributes);

	/**
     * Gets the Id of a ConfigCatUser
     */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	FString GetIdentifier() const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	FString GetStringAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	double GetNumberAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	FDateTime GetTimeAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	TArray<FString> GetStringArrayAttribute(const FString& Key) const;

	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	bool HasAnyAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	bool HasStringAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	bool HasNumberAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	bool HasTimeAttribute(const FString& Key) const;
	UFUNCTION(BlueprintPure, Category = "ConfigCat|User")
	bool HasStringArrayAttribute(const FString& Key) const;

	std::shared_ptr<configcat::ConfigCatUser> User;
	
private:
	const configcat::ConfigCatUser::AttributeValue* GetUserAttributeForKey(const FString& Key) const;
};