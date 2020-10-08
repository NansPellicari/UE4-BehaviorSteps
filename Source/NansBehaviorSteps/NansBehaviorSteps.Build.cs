// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class NansBehaviorSteps : ModuleRules
	{
		public NansBehaviorSteps(ReadOnlyTargetRules Target) : base(Target)
		{
			// This to allow dynamic_cast
			// https://answers.unrealengine.com/questions/477792/how-do-i-cast-between-polymorphic-classes-that-don.html?sort=oldest
			bUseRTTI = true;

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"AIModule",
					"GameplayTasks",
					"CoreUObject",
					"NansCoreHelpers",
					"NansUE4Utilities",
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateIncludePathModuleNames.AddRange(
				new string[]
				{
					"MessageLog",
				}
			);
		}
	}
}
