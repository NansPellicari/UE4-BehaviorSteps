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

#include "BTSteps.h"


#include "Step.h"
#include "StepsHandlerBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTSteps::UBTSteps()
{
	Handler = MakeUnique<NStepsHandlerBase>();
}

void UBTSteps::BeginDestroy()
{
	if (Handler.IsValid())
	{
		Handler.Reset();
	}
	Super::BeginDestroy();
}


FBTStep UBTSteps::GetCurrentStep_Implementation()
{
	return FBTStep(Handler->GetCurrent());
}

bool UBTSteps::StepIsAlreadyDone_Implementation(const FBTStep Step) const
{
	return Handler->IsAlreadyDone(static_cast<FNStep>(Step));
}

void UBTSteps::Clear_Implementation()
{
	Handler->Clear();
}

FBTStep UBTSteps::GetStepToGo_Implementation()
{
	return FBTStep(Handler->GetStepToGo());
}

void UBTSteps::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() == FName("bDebug"))
	{
		Handler->bDebug = bDebug;
	}
}

void UBTSteps::FinishedCurrentStep_Implementation()
{
	return Handler->FinishedCurrent();
}

bool UBTSteps::StepIsPlaying_Implementation(const FBTStep& Step)
{
	return Handler->IsPlaying(static_cast<FNStep>(Step));
}

void UBTSteps::RedoStep_Implementation(FBTStep Step, bool FromFirstIteration)
{
	Handler->Redo(static_cast<FNStep>(Step), FromFirstIteration);
}

void UBTSteps::JumpTo_Implementation(FBTStep Step)
{
	Handler->JumpTo(static_cast<FNStep>(Step));
}

bool UBTSteps::StepIsPlayable_Implementation(const FBTStep& Step) const
{
	return Handler->IsPlayable(static_cast<FNStep>(Step));
}

bool UBTSteps::PlayStep_Implementation(const FBTStep& Step)
{
	return Handler->Play(static_cast<FNStep>(Step));
}

bool UBTSteps::StepCanPlay_Implementation(const FBTStep& Step)
{
	return Handler->CanPlay(static_cast<FNStep>(Step));
}

void UBTSteps::ConcludeAllSteps_Implementation()
{
	Handler->ConcludeAll();
}

#undef LOCTEXT_NAMESPACE
