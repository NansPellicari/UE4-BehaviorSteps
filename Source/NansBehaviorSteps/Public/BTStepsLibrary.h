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
#include "Step.h"
#include "StepsHandlerBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BTStepsLibrary.generated.h"

class UBTStepsHandlerContainer;

/**
 * Just an adapter allowing to transit FNStep in Blueprint
 */
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

/**
 * The purpose of this BlueprintLibrary is to access all of the StepsHandler c++ functions.
 * This way you can create your own Blueprint's BehaviorTree Task, Decorator Or Service
 * and have access to the core features.
 */
UCLASS()
class NANSBEHAVIORSTEPS_API UBTStepsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	static TSharedPtr<IStepsHandler> GetHandler(UBTStepsHandlerContainer* Container);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Get current"))
	static FBTStep GetCurrent(UBTStepsHandlerContainer* Container);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Conclude all"))
	static void ConcludeAll(UBTStepsHandlerContainer* Container);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Finish current"))
	static void FinishedCurrent(UBTStepsHandlerContainer* Container);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Redo"))
	static void RedoStep(UBTStepsHandlerContainer* Container, FBTStep Step, bool FromFirstIteration = false);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Jump To"))
	static void JumpTo(UBTStepsHandlerContainer* Container, FBTStep Step);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Is already done"))
	static bool IsAlreadyDone(UBTStepsHandlerContainer* Container, const FBTStep Step);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Can Play"))
	static bool CanPlay(UBTStepsHandlerContainer* Container, const FBTStep& Step);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Is Playing"))
	static bool IsPlaying(UBTStepsHandlerContainer* Container, const FBTStep& Step);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Play"))
	static bool Play(UBTStepsHandlerContainer* Container, const FBTStep& Step);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Get step to go"))
	static FBTStep GetStepToGo(UBTStepsHandlerContainer* Container);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Clear"))
	static void ClearStepsHandler(UBTStepsHandlerContainer* Container);

	UFUNCTION(BlueprintCallable, Category = "StepsHandler", Meta=(DisplayName="Steps Handler: Debug"))
	static void SetDebug(UBTStepsHandlerContainer* Container, bool bDebug);
};
