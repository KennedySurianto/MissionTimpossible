#include "AStarPathfinder.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Main function to find the path
TArray<FVector> UAStarPathfinder::FindPath(const FVector& Start, const FVector& Goal)
{
    // clear the lists
    OpenList.Empty();
    ClosedList.Empty();

    // create start and goal nodes
    FNode* StartNode = new FNode();
    StartNode->Position = Start;

    FNode* GoalNode = new FNode();
    GoalNode->Position = Goal;

    OpenList.Add(StartNode);

    while (OpenList.Num() > 0)
    {
        // sort the open list by FCost
        OpenList.Sort([](const FNode& A, const FNode& B) { return A.FCost() < B.FCost(); });

        // get the node with the lowest FCost
        FNode* CurrentNode = OpenList[0];

        // check if we reached the goal
        if (FVector::Dist(CurrentNode->Position, GoalNode->Position) < 100.f) // Adjust threshold as needed
        {
            return ReconstructPath(CurrentNode);
        }

        // move the current node to the closed list
        OpenList.RemoveAt(0);
        ClosedList.Add(CurrentNode);

        // generate neighbors
        TArray<FNode*> Neighbors = GenerateNeighbors(CurrentNode);
        for (FNode* Neighbor : Neighbors)
        {
            if (ClosedList.Contains(Neighbor))
            {
                continue; // ignore already evaluated nodes
            }

            // calculate costs
            float TentativeGCost = CurrentNode->GCost + FVector::Dist(CurrentNode->Position, Neighbor->Position);
            if (!OpenList.Contains(Neighbor))
            {
                OpenList.Add(Neighbor); // discover a new node
            }
            else if (TentativeGCost >= Neighbor->GCost)
            {
                continue; // not a better path
            }

            // update costs and parent
            Neighbor->GCost = TentativeGCost;
            Neighbor->HCost = Heuristic(Neighbor->Position, GoalNode->Position);
            Neighbor->Parent = CurrentNode;
        }
    }

    // no path found
    return TArray<FVector>();
}

// generate neighboring nodes
TArray<FNode*> UAStarPathfinder::GenerateNeighbors(FNode* Node)
{
    TArray<FNode*> Neighbors;

    // example of generating 4 neighbors (up, down, left, right)
    FVector Directions[4] = {
        FVector(0, 1, 0),   // up
        FVector(0, -1, 0),  // down
        FVector(1, 0, 0),   // right
        FVector(-1, 0, 0)   // left
    };

    for (const FVector& Direction : Directions)
    {
        FVector NeighborPos = Node->Position + Direction * 100.f; // size
        if (IsWalkable(NeighborPos))
        {
            FNode* NeighborNode = new FNode();
            NeighborNode->Position = NeighborPos;
            Neighbors.Add(NeighborNode);
        }
    }

    return Neighbors;
}



// heuristic function (using manhattan distance)
float UAStarPathfinder::Heuristic(const FVector& A, const FVector& B)
{
    return FMath::Abs(A.X - B.X) + FMath::Abs(A.Y - B.Y);
}

// check if a position is walkable
bool UAStarPathfinder::IsWalkable(const FVector& Position)
{
    return true;
}

// reconstruct the path from the goal node to the start node
TArray<FVector> UAStarPathfinder::ReconstructPath(FNode* Node)
{
    TArray<FVector> Path;
    while (Node != nullptr)
    {
        Path.Add(Node->Position);
        Node = Node->Parent;
    }
    Algo::Reverse(Path); // reverse the path to get it from start to goal
    return Path;
}