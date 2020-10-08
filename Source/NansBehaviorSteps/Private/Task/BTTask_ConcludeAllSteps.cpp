// Fill out your copyright notice in the Description page of Project Settings.

#include "Task/BTTask_ConcludeAllSteps.h"

#include "BTSteps.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

EBTNodeResult::Type UBTTask_ConcludeAllSteps::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* BTSteps = BlackboardComp->GetValueAsObject(StepsKeyName);

	if (BTSteps != nullptr && BTSteps->Implements<UBTStepsHandler>())
	{
		IBTStepsHandler::Execute_ConcludeAllSteps(BTSteps);
		return EBTNodeResult::Succeeded;
	}

	EDITOR_ERROR(
		"BehaviorSteps", LOCTEXT("StepsHandlerNotInitiated", "The steps handler can not be retrieved from the blackboard"));
	return EBTNodeResult::Aborted;
}

FString UBTTask_ConcludeAllSteps::GetStaticDescription() const
{
	FString ReturnDesc;
	return ReturnDesc;
}

#if WITH_EDITOR
FName UBTTask_ConcludeAllSteps::GetNodeIconName() const
{
	// TODO import my own icon
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}
#endif	  // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
