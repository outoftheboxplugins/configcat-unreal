// Copyright (c) ConfigCat 2024. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnrealBuildTool;

public class ConfigCatCppSdk : ModuleRules
{
	public ConfigCatCppSdk(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			AddPrecompiledLibraries(Path.Combine(ModuleDirectory, "Binaries", "Win64", "x64-windows-unreal"), "*.lib");
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{ 
			AddPrecompiledLibraries(Path.Combine(ModuleDirectory, "Binaries", "MacOS", "universal-osx-unreal"), "*.a");
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			AddPrecompiledLibraries(Path.Combine(ModuleDirectory, "Binaries", "Linux-x64", "x64-linux-unreal"), "*.a");
		}
		else if (Target.Platform == UnrealTargetPlatform.LinuxArm64)
		{
			AddPrecompiledLibraries(Path.Combine(ModuleDirectory, "Binaries", "Linux-arm64", "arm64-linux-unreal"), "*.a");
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			AddPrecompiledLibraries(Path.Combine(ModuleDirectory, "Binaries", "Android", "arm64-android"), "*.a");
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			AddPrecompiledLibraries(Path.Combine(ModuleDirectory, "Binaries", "iOS", "arm64-ios-unreal"), "*.a");
		}
	}

	public void AddPrecompiledLibraries(string FolderPath, string Extension)
	{
		List<string> Files = Directory.GetFiles(FolderPath, Extension, SearchOption.AllDirectories).ToList();
		foreach (string File in Files)
		{
			PublicAdditionalLibraries.Add(Path.Combine(FolderPath, File));
			Console.WriteLine(Name + " adding library: " + File);
		}
	}
}
