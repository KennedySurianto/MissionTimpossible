#include "BSPMazeGenerator.h"

ABSPMazeGenerator::ABSPMazeGenerator()
{
    PrimaryActorTick.bCanEverTick = true;

    Width = 10;
    Height = 10;
    CellSize = 200.0f; // Default size of each cell
}

void ABSPMazeGenerator::BeginPlay()
{
    Super::BeginPlay();
    GenerateMaze();
}

void ABSPMazeGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABSPMazeGenerator::GenerateMaze()
{
    DivideSpace(0, 0, Width, Height);
}

void ABSPMazeGenerator::DivideSpace(int32 StartX, int32 StartY, int32 EndX, int32 EndY)
{
    // Base case: Stop dividing if the region is too small
    if (EndX - StartX <= 1 || EndY - StartY <= 1)
        return;

    // Determine split direction
    bool SplitHorizontally = (EndX - StartX > EndY - StartY) ? false : true;

    // Randomly determine split position
    if (SplitHorizontally)
    {
        int32 SplitY = FMath::RandRange(StartY + 1, EndY - 1);
        PlaceWall(FVector(StartX * CellSize, SplitY * CellSize, 0), FVector(EndX * CellSize, SplitY * CellSize, 0));

        // Recursively divide the two resulting spaces
        DivideSpace(StartX, StartY, EndX, SplitY);
        DivideSpace(StartX, SplitY, EndX, EndY);
    }
    else
    {
        int32 SplitX = FMath::RandRange(StartX + 1, EndX - 1);
        PlaceWall(FVector(SplitX * CellSize, StartY * CellSize, 0), FVector(SplitX * CellSize, EndY * CellSize, 0));

        // Recursively divide the two resulting spaces
        DivideSpace(StartX, StartY, SplitX, EndY);
        DivideSpace(SplitX, StartY, EndX, EndY);
    }
}

void ABSPMazeGenerator::PlaceWall(FVector Start, FVector End)
{
    // Use a wall mesh (e.g., a cube) or draw debug lines
    FVector WallSize = FVector(CellSize, 10.0f, 200.0f); // Example size
    FVector WallLocation = (Start + End) / 2;

    FRotator WallRotation = (Start.X == End.X) ? FRotator(0, 90, 0) : FRotator(0, 0, 0);

    FActorSpawnParameters SpawnParams;
    GetWorld()->SpawnActor<AActor>(WallActorClass, WallLocation, WallRotation, SpawnParams);
}
