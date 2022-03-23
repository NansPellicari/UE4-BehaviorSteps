// Copyright 2020-present Nans Pellicari (nans.pellicari@gmail.com).
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "NansBehaviorSteps/Public/BTStepsLibrary.h"
#include "Misc/ErrorUtils.h"
#include "AIController.h"

#include "BTStepsSubsystem.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTStepsSubsystem* UBTStepsLibrary::GetStepsSubsystem(const UBehaviorTreeComponent& OwnerComp)
{
	const AAIController* AIOwner = OwnerComp.GetAIOwner();
	check(IsValid(AIOwner))
	const UWorld* World = GEngine->GetWorldFromContextObject(AIOwner, EGetWorldErrorMode::LogAndReturnNull);
	check(IsValid(World))
	const UGameInstance* GI = World->GetGameInstance();
	UBTStepsSubsystem* MySubsystem = GI->GetSubsystem<UBTStepsSubsystem>();
	check(IsValid(MySubsystem));
	return MySubsystem;
}
#undef LOCTEXT_NAMESPACE
