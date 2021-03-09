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
#include "IStepsHandler.h"

class NANSBEHAVIORSTEPSCORE_API NStepsHandlerBase : public IStepsHandler, public TSharedFromThis<NStepsHandlerBase>
{
public:
	NStepsHandlerBase();
	virtual ~NStepsHandlerBase();
	virtual FNStep GetCurrent() const override;
	virtual void ConcludeAll() override;
	virtual void FinishedCurrent() override;
	virtual void Redo(FNStep Step, bool FromFirstIteration = false) override;
	virtual void JumpTo(FNStep Step) override;
	virtual bool CanPlay(const FNStep& Step) override;
	virtual bool IsPlaying(const FNStep& Step) const override;
	virtual bool IsAlreadyDone(const FNStep Step) const override;
	virtual bool Play(const FNStep& Step) override;
	virtual FNStep GetStepToGo() const override;
	virtual bool IsPlayable(const FNStep& Step) const override;
	virtual void Clear() override;

	bool bDebug = false;
protected:
	FNStep StepToGo = FNStep(0);
	FNStep CurrentStep = FNStep(0);

	TArray<FNStep> FinishedSteps;
};
