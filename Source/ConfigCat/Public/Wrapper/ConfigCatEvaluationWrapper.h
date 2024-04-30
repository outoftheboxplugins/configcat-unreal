﻿// Copyright (c) ConfigCat 2024. All Rights Reserved.

#pragma once

#include <ConfigCatCppSDK/Include/evaluationdetails.h>

#include <optional>

#include "ConfigCatEvaluationWrapper.generated.h"

UCLASS(DisplayName="Config Cat Evaluation", Hidden)
class CONFIGCAT_API UConfigCatEvaluationWrapper : public UObject
{
	GENERATED_BODY()

public:
	// static UConfigCatEvaluationWrapper* CreateEvaluation(const configcat::EvaluationDetailsBase& InEvaluationDetails);
	static UConfigCatEvaluationWrapper* CreateEvaluation(std::shared_ptr<const configcat::EvaluationDetailsBase> InEvaluationDetails);

	/**
     * Gets the identifier Key of the evaluated feature flag
     */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	FString GetKey() const;
	/**
	 * Gets the variation identifier of the evaluated feature flag
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	FString GetVariationId() const;
	/**
     * Gets the timestamp of the last fetch at the time of evaluation
     */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	FDateTime GetFetchTime() const;
	/**
	 * Gets the user the evaluation was performed against
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	UConfigCatUserWrapper* GetUser() const;
	/**
	 * Gets if the value returned is the default value of the feature flag
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	bool IsDefaultValue() const;
	/**
	 * Gets the error associated with the evaluation (if any)
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	FString GetError() const;
	/**
	 *
     */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	FString GetException() const;
	// TODO: Create getters for:
	//std::optional<TargetingRule> matchedTargetingRule;
	//std::optional<PercentageOption> matchedPercentageOption;
	/**
	 * Gets the value of the evaluated feature flag
	 */
	UFUNCTION(BlueprintPure, Category = "ConfigCat|EvaluationDetails")
	UConfigCatValueWrapper* GetValue() const;

	void SetEvaluationDetails(std::shared_ptr<const configcat::EvaluationDetailsBase> InEvaluationDetails);

private:
	std::shared_ptr<const configcat::EvaluationDetailsBase> EvaluationDetails;
};