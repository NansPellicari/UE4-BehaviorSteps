// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
    public class NansBehaviorSteps : ModuleRules
    {
        public NansBehaviorSteps(ReadOnlyTargetRules Target) : base(Target)
        {
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
