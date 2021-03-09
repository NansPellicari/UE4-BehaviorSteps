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

#include "NansBehaviorSteps/Public/BTStepsLibrary.h"

#include "BTStepsHandlerContainer.h"

TSharedPtr<IStepsHandler> UBTStepsLibrary::GetHandler(UBTStepsHandlerContainer* Container)
{
	return Container->GetHandler();
}

FBTStep UBTStepsLibrary::GetCurrent(UBTStepsHandlerContainer* Container)
{
	return FBTStep(GetHandler(Container)->GetCurrent());
}

bool UBTStepsLibrary::IsAlreadyDone(UBTStepsHandlerContainer* Container, const FBTStep Step)
{
	return GetHandler(Container)->IsAlreadyDone(static_cast<FNStep>(Step));
}

void UBTStepsLibrary::ClearStepsHandler(UBTStepsHandlerContainer* Container)
{
	GetHandler(Container)->Clear();
}

FBTStep UBTStepsLibrary::GetStepToGo(UBTStepsHandlerContainer* Container)
{
	return FBTStep(GetHandler(Container)->GetStepToGo());
}

void UBTStepsLibrary::FinishedCurrent(UBTStepsHandlerContainer* Container)
{
	return GetHandler(Container)->FinishedCurrent();
}

bool UBTStepsLibrary::IsPlaying(UBTStepsHandlerContainer* Container, const FBTStep& Step)
{
	return GetHandler(Container)->IsPlaying(static_cast<FNStep>(Step));
}

void UBTStepsLibrary::RedoStep(UBTStepsHandlerContainer* Container, FBTStep Step, bool FromFirstIteration)
{
	GetHandler(Container)->Redo(static_cast<FNStep>(Step), FromFirstIteration);
}

void UBTStepsLibrary::JumpTo(UBTStepsHandlerContainer* Container, FBTStep Step)
{
	GetHandler(Container)->JumpTo(static_cast<FNStep>(Step));
}

bool UBTStepsLibrary::Play(UBTStepsHandlerContainer* Container, const FBTStep& Step)
{
	return GetHandler(Container)->Play(static_cast<FNStep>(Step));
}

bool UBTStepsLibrary::CanPlay(UBTStepsHandlerContainer* Container, const FBTStep& Step)
{
	return GetHandler(Container)->CanPlay(static_cast<FNStep>(Step));
}

void UBTStepsLibrary::ConcludeAll(UBTStepsHandlerContainer* Container)
{
	GetHandler(Container)->ConcludeAll();
}

void UBTStepsLibrary::SetDebug(UBTStepsHandlerContainer* Container, bool bDebug)
{
	GetHandler(Container)->SetDebug(bDebug);
}
