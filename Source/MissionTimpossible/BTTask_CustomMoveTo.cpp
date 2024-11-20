#include "BTTask_CustomMoveTo.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_CustomMoveTo::UBTTask_CustomMoveTo()
{
    NodeName = "Custom Move To";
    AStarPathfinder = NewObject<UAStarPathfinder>();
}

EBTNodeResult::Type UBTTask_CustomMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // get the AI controller and target actor
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
    if (!TargetActor) return EBTNodeResult::Failed;

    // calculate the path using A*
    FVector StartLocation = AIController->GetPawn()->GetActorLocation();
    FVector GoalLocation = TargetActor->GetActorLocation();
    Path = AStarPathfinder->FindPath(StartLocation, GoalLocation);

    if (Path.Num() == 0) return EBTNodeResult::Failed; // no path found

    CurrentPathIndex = 0; // the beginning of the path

    return EBTNodeResult::InProgress;
}

void UBTTask_CustomMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return;

    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn) return;

    // move to the current path point
    FVector TargetLocation = Path[CurrentPathIndex];
    FVector Direction = (TargetLocation - ControlledPawn->GetActorLocation()).GetSafeNormal();
    ControlledPawn->AddActorLocalOffset(Direction * MoveSpeed * DeltaSeconds, true);

    // check if // Check if the pawn has reached the current path point
    if (FVector::Dist(ControlledPawn->GetActorLocation(), TargetLocation) < AcceptableRadius)
    {
        CurrentPathIndex++; // move to the next point in the path

        // check if we have reached the end of the path
        if (CurrentPathIndex >= Path.Num())
        {
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // Task succeeded
            return;
        }
    }

    // continue the task if not finished
    FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
}