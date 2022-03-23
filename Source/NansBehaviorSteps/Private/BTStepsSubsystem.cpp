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

#include "BTStepsSubsystem.h"
#include "AIController.h"
#include "StepsHandler.h"
#include "Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

void UBTStepsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBTStepsSubsystem::Deinitialize()
{
	Super::Deinitialize();
	StepsHandlers.Empty();
}

const TSharedPtr<NStepsHandler>& UBTStepsSubsystem::CreateStepsHandler(const AAIController* Owner)
{
	const AActor* Pawn = Owner->GetPawn<AActor>();
	check(IsValid(Pawn));
	return StepsHandlers.FindOrAdd(Pawn->GetPathName(), MakeShared<NStepsHandler>());
}

const TSharedPtr<NStepsHandler>& UBTStepsSubsystem::GetStepsHandler(const AAIController* Owner)
{
	const AActor* Pawn = Owner->GetPawn<AActor>();
	check(IsValid(Pawn));
	const FString Name = Pawn->GetPathName();
	const TSharedPtr<NStepsHandler>& StepHandler = StepsHandlers.FindRef(Name);
	if (!StepHandler.IsValid())
	{
		return CreateStepsHandler(Owner);
	}
	return StepHandler;
}

void UBTStepsSubsystem::RemoveStepsHandler(const AAIController* Owner)
{
	const AActor* Pawn = Owner->GetPawn<AActor>();
	check(IsValid(Pawn));
	StepsHandlers.FindAndRemoveChecked(Pawn->GetPathName());
}

#undef LOCTEXT_NAMESPACE
