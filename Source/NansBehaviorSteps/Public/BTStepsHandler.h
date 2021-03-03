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
#include "UObject/Interface.h"

#include "BTStepsHandler.generated.h"

UINTERFACE(BlueprintType)
class NANSBEHAVIORSTEPS_API UBTStepsHandler : public UInterface
{
	GENERATED_BODY()
};

class NANSBEHAVIORSTEPS_API IBTStepsHandler
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	int32 GetCurrentStep();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void ConcludeAllSteps();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void FinishedCurrentStep();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void RedoStep(int32 Step, bool FromLastPlay = false);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void JumpTo(int32 Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepIsAlreadyDone(const int32 Step) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepCanPlay(const int32& Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepIsPlaying(const int32& Step);

	// If the step is the same as StepToGo, this method reset StepToGo to 0
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepCanPlayAndReset(const int32& Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool PlayStep(const int32& Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	int32 GetStepToGo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepIsPlayable(const int32& Step, bool ResetStepToGoIfPlay = true);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void Clear();
};
