#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AStarPathfinder.h"
#include "BTTask_CustomMoveTo.generated.h"

UCLASS()
class MISSIONTIMPOSSIBLE_API UBTTask_CustomMoveTo : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTTask_CustomMoveTo();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
    UPROPERTY(EditAnywhere, Category = "AI")
    float MoveSpeed = 300.f;

    UPROPERTY(EditAnywhere, Category = "AI")
    float AcceptableRadius = 500.f;

    AActor* TargetActor;
    TArray<FVector> Path; // calculated path
    int32 CurrentPathIndex; // current index in the path
    UAStarPathfinder* AStarPathfinder; // reference to the A* pathfinder
};