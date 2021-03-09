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
#include "BehaviorTree/BTService.h"

#include "BTService_JumpTo.generated.h"

/**
 *
 */
UCLASS()
class NANSBEHAVIORSTEPS_API UBTService_JumpTo : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = "Blackboard")
	FName StepsKeyName = FName("Steps");

	UPROPERTY(EditInstanceOnly, Category = "Step")
	int32 StepToGo = 0;

	UPROPERTY(EditInstanceOnly, Category = "Step")
	FName StepToGoLabel = NAME_None;

	UBTService_JumpTo(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif	  // WITH_EDITOR
};
