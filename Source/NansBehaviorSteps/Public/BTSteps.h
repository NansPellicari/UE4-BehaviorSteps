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
#include "BTStepsHandler.h"
#include "StepsHandlerBase.h"
#include "UObject/NoExportTypes.h"

#include "BTSteps.generated.h"


/**
 */
UCLASS(BlueprintType)
class NANSBEHAVIORSTEPS_API UBTSteps : public UObject, public IBTStepsHandler
{
	GENERATED_BODY()

public:
	UBTSteps();
	virtual void BeginDestroy() override;

	// BEGIN IBTStepsHandler overrides
	virtual FBTStep GetCurrentStep_Implementation() override;
	virtual void ConcludeAllSteps_Implementation() override;
	virtual void FinishedCurrentStep_Implementation() override;
	virtual bool PlayStep_Implementation(const FBTStep& Step) override;
	virtual bool StepIsPlaying_Implementation(const FBTStep& Step) override;
	virtual void RedoStep_Implementation(FBTStep Step, bool FromFirstIteration = false) override;
	virtual void JumpTo_Implementation(FBTStep Step) override;
	virtual bool StepIsAlreadyDone_Implementation(const FBTStep Step) const override;
	virtual void Clear_Implementation() override;
	virtual bool StepCanPlay_Implementation(const FBTStep& Step) override;
	// If the step is the same as StepToGo, this method reset StepToGo to 0
	virtual bool StepIsPlayable_Implementation(const FBTStep& Step) const override;
	virtual FBTStep GetStepToGo_Implementation() override;
	// END IBTStepsHandler overrides


	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
protected:
	TUniquePtr<NStepsHandlerBase> Handler;

	UPROPERTY(BlueprintReadWrite, Category = "Step")
	bool bDebug = false;
};
