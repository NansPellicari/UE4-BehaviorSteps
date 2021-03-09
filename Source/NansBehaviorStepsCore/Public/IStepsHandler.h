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

class NANSBEHAVIORSTEPSCORE_API IStepsHandler
{
public:
	virtual ~IStepsHandler() {}
	virtual FNStep GetCurrent() const = 0;
	virtual void ConcludeAll() = 0;
	virtual void FinishedCurrent() = 0;
	virtual void Redo(FNStep Step, bool FromFirstIteration = false) = 0;
	virtual void JumpTo(FNStep Step) = 0;
	virtual bool IsAlreadyDone(const FNStep Step) const = 0;
	virtual bool CanPlay(const FNStep& Step) const = 0;
	virtual bool IsPlaying(const FNStep& Step) const = 0;
	virtual bool Play(const FNStep& Step) = 0;
	virtual FNStep GetStepToGo() const = 0;
	virtual void Clear() = 0;
	virtual void SetDebug(bool bInDebug) = 0;
};
