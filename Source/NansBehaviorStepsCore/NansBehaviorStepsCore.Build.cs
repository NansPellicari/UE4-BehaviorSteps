// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class NansBehaviorStepsCore : ModuleRules
	{
		public NansBehaviorStepsCore(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicDependencyModuleNames.AddRange(
				new[]
				{
					"Core",
					"CoreUObject",
					"NansCoreHelpers"
				}
			);
		}
	}
}
