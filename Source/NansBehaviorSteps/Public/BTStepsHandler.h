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

#pragma once

#include "CoreMinimal.h"


#include "IStepsHandler.h"
#include "Step.h"
#include "UObject/Interface.h"

#include "BTStepsHandler.generated.h"


USTRUCT(BlueprintType)
struct FBTStep : public FNStep
{
	GENERATED_USTRUCT_BODY()
	FBTStep() {}
	FBTStep(FNStep InStep) : FNStep(InStep.Id, InStep.Label, InStep.ParentId) {}
	FBTStep(int32 InId) : FNStep(InId) {}
	FBTStep(int32 InId, FName InLabel) : FNStep(InId, InLabel) {}
	FBTStep(int32 InId, FName InLabel, int32 InParentId) : FNStep(InId, InLabel, InParentId) {}
};

UINTERFACE(BlueprintType)
class NANSBEHAVIORSTEPS_API UBTStepsHandler : public UInterface
{
	GENERATED_BODY()
};

/** TODO Try to light it and use only native StepsHandler */
class NANSBEHAVIORSTEPS_API IBTStepsHandler
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	FBTStep GetCurrentStep();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void ConcludeAllSteps();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void FinishedCurrentStep();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void RedoStep(FBTStep Step, bool FromFirstIteration = false);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void JumpTo(FBTStep Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepIsAlreadyDone(const FBTStep Step) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepCanPlay(const FBTStep& Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepIsPlaying(const FBTStep& Step);

	// If the step is the same as StepToGo, this method reset StepToGo to 0
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepCanPlayAndReset(const FBTStep& Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool PlayStep(const FBTStep& Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	FBTStep GetStepToGo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepIsPlayable(const FBTStep& Step) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void Clear();
};
