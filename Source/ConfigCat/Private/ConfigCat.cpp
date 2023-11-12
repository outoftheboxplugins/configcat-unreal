﻿// Copyright (c) ConfigCat 2023. All Rights Reserved.

#include "ConfigCat.h"

#include <Misc/Paths.h>

IMPLEMENT_MODULE(FConfigCatModule, ConfigCat)

FString FConfigCatModule::GetContentFolder()
{
	return FPaths::ProjectContentDir() + TEXT("ConfigCat");
}
