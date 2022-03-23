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

#include "Step.h"

class NANSBEHAVIORSTEPS_API NStepsHandler : public TSharedFromThis<NStepsHandler>
{
public:
	NStepsHandler();
	virtual ~NStepsHandler();
	const FNStep& GetCurrent() const;
	void ConcludeAll();
	void FinishedCurrent();
	void Redo(const FNStep& Step, bool FromFirstIteration = false);
	void JumpTo(const FNStep& Step);
	bool CanPlay(const FNStep& Step) const;
	bool IsPlaying(const FNStep& Step) const;
	bool IsAlreadyDone(const FNStep& Step) const;
	bool Play(const FNStep& Step);
	const FNStep& GetStepToGo() const;
	void Clear();
	void SetDebug(bool bInDebug);

	bool bDebug = false;
private:
	FNStep StepToGo = FNStep(0);
	FNStep CurrentStep = FNStep(0);

	TArray<FNStep> FinishedSteps;
};
