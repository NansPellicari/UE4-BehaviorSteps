// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "INansBehaviorSteps.h"
#include "MessageLog/Public/MessageLogInitializationOptions.h"
#include "MessageLog/Public/MessageLogModule.h"
#include "Modules/ModuleManager.h"
#include "NansBehaviorStepsLog.h"

// TODO @see Engine\Source\Editor\EditorStyle\Private\SlateEditorStyle.cpp to add some style
class FNansBehaviorSteps : public INansBehaviorSteps
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FNansBehaviorSteps, NansBehaviorSteps)

void FNansBehaviorSteps::StartupModule()
{
	// create a message log to use in my module
	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	FMessageLogInitializationOptions InitOptions;
	InitOptions.bAllowClear = true;
	InitOptions.bShowFilters = true;
	MessageLogModule.RegisterLogListing(
		"BehaviorSteps", NSLOCTEXT("BehaviorSteps", "BehaviorStepsLogLabel", "Behavior Steps"), InitOptions);
}

void FNansBehaviorSteps::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("MessageLog"))
	{
		// unregister message log
		FMessageLogModule& MessageLogModule = FModuleManager::GetModuleChecked<FMessageLogModule>("MessageLog");
		MessageLogModule.UnregisterLogListing("BehaviorSteps");
	}
}
