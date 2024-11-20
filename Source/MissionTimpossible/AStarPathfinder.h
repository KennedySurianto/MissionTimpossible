#pragma once

#include "CoreMinimal.h"
#include "AStarPathfinder.generated.h"

USTRUCT()
struct FNode
{
    GENERATED_BODY()

    FVector Position;
    float GCost; // cost from start to this node
    float HCost; // heuristic cost to the goal
    float FCost() const { return GCost + HCost; } // total cost
    FNode* Parent; // pointer to the parent node

    FNode() : GCost(0), HCost(0), Parent(nullptr) {}
};

UCLASS()
class MISSIONTIMPOSSIBLE_API UAStarPathfinder : public UObject
{
    GENERATED_BODY()

public:
    TArray<FVector> FindPath(const FVector& Start, const FVector& Goal);

private:
    TArray<FNode*> OpenList; // nodes to be evaluated
    TArray<FNode*> ClosedList; // nodes already evaluated
    TArray<FNode*> GenerateNeighbors(FNode* Node);
    float Heuristic(const FVector& A, const FVector& B);
    bool IsWalkable(const FVector& Position);
    TArray<FVector> ReconstructPath(FNode* Node);
};