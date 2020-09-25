// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSteps.h"

#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTSteps::UBTSteps()
{
	FinishedSteps = TArray<int32>();
}

UBTSteps::~UBTSteps()
{
	Clear();
}

bool UBTSteps::StepIsAlreadyDone(const int32 Step) const
{
	int32 Index;
	return FinishedSteps.Find(Step, Index);
}

void UBTSteps::Clear()
{
	FinishedSteps.Empty();
	StepToGo = 0;
}

int32 UBTSteps::GetStepToGo()
{
	return StepToGo;
}

void UBTSteps::AddFinishedStep(int32 Step)
{
	if (StepIsAlreadyDone(Step))
	{
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("%s: Step %d already done"), *GetName(), Step);
		return;
	}

	FinishedSteps.Add(Step);
}
void UBTSteps::FinishedCurrentStep()
{
	if (StepIsAlreadyDone(CurrentStep))
	{
		if (bDebug) UE_LOG(LogTemp, Warning, TEXT("%s: Current Step %d already done"), *GetName(), CurrentStep);
		return;
	}

	FinishedSteps.Add(CurrentStep);
}

void UBTSteps::RedoStep(int32 Step, bool FromLastPlay)
{
	int32 Index = FromLastPlay ? FinishedSteps.FindLast(Step) : FinishedSteps.Find(Step);

	if (Index < 0)
	{
		EDITOR_ERROR("BehaviorSteps",
			FText::Format(
				LOCTEXT("InvalidStepNumberToRedo", "The step Number {0} has not been played already, use JumpTo() method instead."),
				Step));
		return;
	}

	int32 Length = FinishedSteps.Num();
	for (int32 i = Length - 1; i >= Index; i--)
	{
		FinishedSteps.RemoveAt(i);
	}
	StepToGo = Step;
}

void UBTSteps::JumpTo(int32 Step)
{
	StepToGo = Step;
}

bool UBTSteps::IsStepPlayable(const int32& Step, const bool& ResetStepToGoIfPlay)
{
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
	return !StepIsAlreadyDone(Step);
}

bool UBTSteps::StepCanPlayAndReset(const int32& Step)
{
	return IsStepPlayable(Step, true);
}

bool UBTSteps::PlayStepAndMoveForward(const int32& Step)
{
	bool bCanPlay = StepCanPlay(Step);
	if (bCanPlay)
	{
		CurrentStep = Step;
		StepToGo = CurrentStep + 1;
	}
	return bCanPlay;
}

bool UBTSteps::StepCanPlay(const int32& Step)
{
	bool bCanPlay = IsStepPlayable(Step, false);
	if (bCanPlay)
	{
		++StepToGo;
	}
	return bCanPlay;
}

#undef LOCTEXT_NAMESPACE
