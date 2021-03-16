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

#include "StepsHandlerBase.h"

#include "NansBehaviorStepsCoreLog.h"

NStepsHandlerBase::NStepsHandlerBase()
{
	FinishedSteps = TArray<FNStep>();
}

NStepsHandlerBase::~NStepsHandlerBase()
{
	FinishedSteps.Empty();
	StepToGo.Reset();
	CurrentStep.Reset();
}

FNStep NStepsHandlerBase::GetCurrent() const
{
	return CurrentStep;
}

bool NStepsHandlerBase::IsAlreadyDone(const FNStep Step) const
{
	if (FinishedSteps.Num() <= 0)
	{
		return false;
	}
	return FinishedSteps.Contains(Step);
}

void NStepsHandlerBase::Clear()
{
	FinishedSteps.Empty();
	StepToGo.Reset();
	CurrentStep.Reset();
}

FNStep NStepsHandlerBase::GetStepToGo() const
{
	return StepToGo;
}

void NStepsHandlerBase::FinishedCurrent()
{
	if (IsAlreadyDone(CurrentStep))
	{
		if (bDebug)
		{
			UE_LOG(LogTemp, Warning, TEXT("Current Step %d already done"), *CurrentStep.ToString());
		}
		return;
	}

	if (!StepToGo.IsDefined())
	{
		StepToGo = CurrentStep + 1;
	}
	if (StepToGo > CurrentStep)
	{
		FinishedSteps.Add(CurrentStep);
	}
	if (bDebug)
	{
		UE_LOG(LogBehaviorStepsC, Display, TEXT("Step %s has stopped"), *CurrentStep.ToString());
	}
	CurrentStep.Reset();
}

bool NStepsHandlerBase::IsPlaying(const FNStep& Step) const
{
	return Step == CurrentStep;
}

void NStepsHandlerBase::Redo(FNStep Step, bool FromFirstIteration)
{
	const int32 Index = !FromFirstIteration ? FinishedSteps.FindLast(Step) : FinishedSteps.Find(Step);

	if (Index < 0 && Step != CurrentStep)
	{
		UE_LOG(
			LogBehaviorStepsC,
			Error,
			TEXT("The step %s has not been played already, use JumpTo() method instead."),
			*Step.ToString()
		);
		return;
	}
	FNStep RealStep = CurrentStep;
	if (Step != CurrentStep)
	{
		RealStep = FinishedSteps[Index];
	}

	const int32 Length = FinishedSteps.Num();
	if (Length > 0)
	{
		for (int32 I = Length - 1; I >= Index; I--)
		{
			FinishedSteps.RemoveAt(I);
		}
	}
	StepToGo = RealStep;
}

void NStepsHandlerBase::JumpTo(FNStep Step)
{
	StepToGo = Step;
}

bool NStepsHandlerBase::CanPlay(const FNStep& Step) const
{
	if (StepToGo == -1)
	{
		return Step == -1;
	}

	if (StepToGo.IsDefined() && Step != StepToGo)
	{
		return false;
	}

	if (!StepToGo.IsDefined() && Step > 1)
	{
		return false;
	}

	// Check if Step is already done (In case we try to replay an old step without a Redo)
	const bool bCanPlay = !IsAlreadyDone(Step);

	return bCanPlay;
}

bool NStepsHandlerBase::Play(const FNStep& Step)
{
	if (Step.Id == 0)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("You can't play a step with Id=0, this label-only's steps are reserved for searches, or Redo and Jump")
		);
		return false;
	}
	const bool bCanPlay = CanPlay(Step);
	if (bCanPlay)
	{
		CurrentStep = Step;
		if (bDebug)
		{
			UE_LOG(LogBehaviorStepsC, Display, TEXT("Step %s is playing"), *CurrentStep.ToString());
		}
		StepToGo.Reset();
	}
	return bCanPlay;
}

void NStepsHandlerBase::ConcludeAll()
{
	CurrentStep.Reset();
	StepToGo.Reset();
	StepToGo = -1;
}

void NStepsHandlerBase::SetDebug(bool bInDebug)
{
	bDebug = bInDebug;
}

#undef LOCTEXT_NAMESPACE
