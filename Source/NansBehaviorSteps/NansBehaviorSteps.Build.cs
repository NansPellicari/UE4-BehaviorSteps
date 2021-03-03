// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class NansBehaviorSteps : ModuleRules
	{
		public NansBehaviorSteps(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicDependencyModuleNames.AddRange(
				new[]
				{
					"Core",
					"AIModule",
					"Engine",
					"GameplayTasks",
					"CoreUObject",
					"NansCoreHelpers",
					"NansUE4Utilities"
					// ... add other public dependencies that you statically link with here ...
				}
			);

			PrivateIncludePathModuleNames.AddRange(
				new[]
				{
					"MessageLog"
				}
			);
		}
	}
}
