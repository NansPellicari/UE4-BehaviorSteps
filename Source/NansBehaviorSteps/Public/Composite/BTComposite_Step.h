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

#include "BehaviorTree/BTCompositeNode.h"
#include "BTComposite_Step.generated.h"

/**
 * 
 */
UCLASS()
class NANSBEHAVIORSTEPS_API UBTComposite_Step : public UBTCompositeNode
{
	GENERATED_BODY()
	UBTComposite_Step();

	/** Is not a sequence, it behaves like a selector node */
	UPROPERTY(EditAnywhere, Category="Blackboard")
	bool bIsSequence = true;
	UPROPERTY(EditAnywhere, Category="Blackboard")
	bool bDebug = false;

	UPROPERTY(EditAnywhere, Category="Steps")
	FNStep Step;

	void FindStepsInChildren(const UBTCompositeNode* NodeToParse, int32& Num, int32 ParentNum, int32& FinalParentNum,
		bool& bBreak) const;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual void NotifyNodeActivation(FBehaviorTreeSearchData& SearchData) const override;
	virtual void
	NotifyNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult) const override;
	virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild,
		EBTNodeResult::Type LastResult) const override;

#if WITH_EDITOR
	virtual bool CanAbortLowerPriority() const override;
	virtual FName GetNodeIconName() const override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
public:
	virtual FString GetStaticDescription() const override;
};
