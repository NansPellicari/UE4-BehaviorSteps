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

#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTSteps::UBTSteps()
{
	FinishedSteps = TArray<int32>();
}

void UBTSteps::BeginDestroy()
{
	FinishedSteps.Empty();
	StepToGo = 0;
	Super::BeginDestroy();
}

int32 UBTSteps::GetCurrentStep_Implementation()
{
	return CurrentStep;
}

bool UBTSteps::StepIsAlreadyDone_Implementation(const int32 Step) const
{
	int32 Index;
	return FinishedSteps.Find(Step, Index);
}

void UBTSteps::Clear_Implementation()
{
	FinishedSteps.Empty();
	StepToGo = 0;
}

int32 UBTSteps::GetStepToGo_Implementation()
{
	return StepToGo;
}

void UBTSteps::AddFinishedStep(int32 Step)
{
	if (Execute_StepIsAlreadyDone(this, Step))
	{
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("%s: Step %d already done"), *GetName(), Step);
		return;
	}

	FinishedSteps.Add(Step);
}

void UBTSteps::FinishedCurrentStep_Implementation()
{
	if (Execute_StepIsAlreadyDone(this, CurrentStep))
	{
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("%s: Current Step %d already done"), *GetName(), CurrentStep);
		return;
	}

	FinishedSteps.Add(CurrentStep);
}

void UBTSteps::RedoStep_Implementation(int32 Step, bool FromLastPlay)
{
	int32 Index = FromLastPlay ? FinishedSteps.FindLast(Step) : FinishedSteps.Find(Step);

	if (Index < 0)
	{
		EDITOR_ERROR(
			"BehaviorSteps",
			FText::Format(
				LOCTEXT("InvalidStepNumberToRedo",
					"The step Number {0} has not been played already, use JumpTo() method instead."),
				Step)
		);
		return;
	}

	int32 Length = FinishedSteps.Num();
	for (int32 i = Length - 1; i >= Index; i--)
	{
		FinishedSteps.RemoveAt(i);
	}
	StepToGo = Step;
}

void UBTSteps::JumpTo_Implementation(int32 Step)
{
	StepToGo = Step;
}

bool UBTSteps::StepIsPlayable_Implementation(const int32& Step, bool ResetStepToGoIfPlay)
{
	if (StepToGo == -1)
	{
		return Step == -1;
	}

	if (StepToGo > 0 && Step != StepToGo)
	{
		return false;
	}

	// We are in, so reset StepToGo
	if (StepToGo > 0 && Step == StepToGo && ResetStepToGoIfPlay == true)
	{
		StepToGo = 0;
	}

	// Check if Step is already done (In case we try to replay an old step without a Redo)
	return !Execute_StepIsAlreadyDone(this, Step);
}

bool UBTSteps::StepCanPlayAndReset_Implementation(const int32& Step)
{
	return Execute_StepIsPlayable(this, Step, true);
}

bool UBTSteps::PlayStepAndMoveForward_Implementation(const int32& Step)
{
	bool bCanPlay = Execute_StepCanPlay(this, Step);
	if (bCanPlay)
	{
		CurrentStep = Step;
		StepToGo = CurrentStep + 1;
	}
	return bCanPlay;
}

bool UBTSteps::StepCanPlay_Implementation(const int32& Step)
{
	bool bCanPlay = Execute_StepIsPlayable(this, Step, false);
	if (bCanPlay)
	{
		++StepToGo;
	}
	return bCanPlay;
}

void UBTSteps::ConcludeAllSteps_Implementation()
{
	StepToGo = -1;
}

#undef LOCTEXT_NAMESPACE
