# Behavior steps

This plugins offer a simple way to create a steps flow on a behavior tree

| Node              | Node Type | Usefull for/when                                                                                                                                                                                                          |
| ----------------- | --------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| CreateStepHandler | Service   | It should be the first element you need in your Behavior tree, it instances the **steps Handler** object and save it to the BlackBoard (BB) for the next nodes                                                            |
| CreateAStep       | Decorator | This should be associated to a **task** or a **composite** node to control the **steps flow**. Depends on the Step number you parameterized, it checks first if it can be run, then, if it's ok, it plays children nodes. |
| EndStep           | Service   | This service should be attached to your **last descending node** under the **CreateStep branch**. It tells to the handler that the current step is finished.                                                              |
| ClearSteps        | Service   | It cleans up the **handler** to its initial state.                                                                                                                                                                        |
| JumpTo            | Task      | It tells to the **handler** which is the next step to play. Be carreful that it can't replayed and already played step. For that use **RedoStep**.                                                                        |
| RedoStep          | Task      | This will replay an already played step. :warning: Be aware of: this will reset all steps which has been played after the steps you specified.                                                                            |
