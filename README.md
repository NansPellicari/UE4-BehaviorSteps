# Behavior steps

This plugins offer a simple way to create a steps flow on a behavior tree.

> :information_source: To see a most advanced usage, please take a look at my Dialog System plugin:  
> https://github.com/NansPellicari/UE4-DialogSystem

|                                                                                                       <a href="https://www.buymeacoffee.com/NansUE4" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-green.png" alt="Buy Me A Coffee" height="51" width="217"></a>                                                                                                       |
| :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| I've decided to make all the code I developed for my games free to use and open source.<br> I am a true believer in the mindset that sharing and collaborating makes the world a better place.<br> The thing is: I'm fulltime dedicated to my project and these open source plugins, for coding I need a looooot of coffee, so please, help me to get my drug :stuck_out_tongue_closed_eyes: !! |

<!-- TOC -->

-   [1. Requirements](#1-requirements)
    -   [1.1. UE4 Plugins](#11-ue4-plugins)
-   [2. Steps Handler](#2-steps-handler)
-   [3. Behavior Tree nodes](#3-behavior-tree-nodes)
-   [4. Contributing and Supporting](#4-contributing-and-supporting)

<!-- /TOC -->

<a id="markdown-1-requirements" name="1-requirements"></a>

## 1. Requirements

<a id="markdown-11-ue4-plugins" name="11-ue4-plugins"></a>

### 1.1. UE4 Plugins

-   [NansUE4TestsHelpers](https://github.com/NansPellicari/UE4-TestsHelpers) (free UE4 plugins)
-   [NansCoreHelpers](https://github.com/NansPellicari/UE4-CoreHelpers) (free UE4 plugins)

<a id="markdown-2-steps-handler" name="2-steps-handler"></a>

## 2. Steps Handler

-   The **StepsHandler** is a c++ Interface (see [IStepsHandler.h](./Source/NansBehaviorStepsCore/Public/IStepsHandler.h)), which allow you to create you own StepsHandler object.
-   It is instanciated by the **CreateStepsHandler** service's node (see section below) in a BehaviorTree (aka BT), you just have to choose the class object you need to work with.
-   A basic **StepsHandler** (see [StepsHandlerBase.h](./Source/NansBehaviorStepsCore/Public/StepsHandlerBase.h)) is provided here, this way you can directly use this plugin.
-   In the [GGTest](./Source/GGTest) folder, you can check directly some basics usages.

<a id="markdown-3-behavior-tree-nodes" name="3-behavior-tree-nodes"></a>

## 3. Behavior Tree nodes

| Node                                                                                            | Node Type    | Usefull for/when                                                                                                                                                                                                                                                                                     |
| ----------------------------------------------------------------------------------------------- | ------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| ![Step](./Docs/images/task-step.png)                                                            | Composite    | It is dedicated to control the **steps flow**. It checks first if it can run children depending on its order in the BT, then it plays all of the children (you can choose to play them as **sequence** or **selector** nodes do). When the last children is played, it allows the next step to play. |
| ![CreateStepsHandler](./Docs/images/service-createStepsHandler.png)                             | Service      | It should be the first element you need in your Behavior tree, it instances the **steps Handler** object and save it into the BlackBoard (BB) for the next nodes.                                                                                                                                    |
| ![ClearSteps](./Docs/images/service-ClearSteps.png)                                             | Service      | This should be called before ending the BT. It cleans up the **handler** to its initial state.                                                                                                                                                                                                       |
| ![EndStep](./Docs/images/service-EndStep.png)<br/>![EndStep](./Docs/images/task-EndStep.png)    | Service/Task | (Optional) You can used it to prematurely end the current step. It can be associated to a Decorator node for example to create an optional BT branch.                                                                                                                                                |
| ![JumpTo](./Docs/images/service-JumpTo.png)<br>![JumpTo](./Docs/images/task-JumpTo.png)         | Service/Task | It tells to the **handler** which is the next step to play, breaking the default flow.<br> :warning: Be careful that it can't replay and already played step. For that use **RedoStep**.                                                                                                             |
| ![RedoStep](./Docs/images/service-RedoStep.png)<br>![RedoStep](./Docs/images/task-RedoStep.png) | Service/Task | This will replay an already played step.<br> :warning: Be aware of: this will reset all steps which has been played after the steps you specified in the Steps Handlers history.                                                                                                                     |

<a id="markdown-4-contributing-and-supporting" name="4-contributing-and-supporting"></a>

## 4. Contributing and Supporting

I've decided to make all the code I developed for my games free to use and open source.  
I am a true believer in the mindset that sharing and collaborating makes the world a better place.  
I'll be very glad if you decided to help me to follow my dream.

| How?                                                                                                                                                                               |                                                                                         With                                                                                         |
| :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| **Donating**<br> Because I'm an independant developer/creator and for now I don't have<br> any income, I need money to support my daily needs (coffeeeeee).                        | <a href="https://www.buymeacoffee.com/NansUE4" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-green.png" alt="Buy Me A Coffee" height="51" width="217" ></a> |
| **Contributing**<br> You are very welcome if you want to contribute. I explain [here](./CONTRIBUTING.md) in details what<br> is the most comfortable way to me you can contribute. |                                                                         [CONTRIBUTING.md](./CONTRIBUTING.md)                                                                         |
