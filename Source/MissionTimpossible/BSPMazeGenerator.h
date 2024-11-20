#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSPMazeGenerator.generated.h"

UCLASS(Blueprintable)
class MISSIONTIMPOSSIBLE_API ABSPMazeGenerator : public AActor
{
    GENERATED_BODY()

public:
    ABSPMazeGenerator();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
    int32 Width;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
    int32 Height;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze")
    float CellSize;

    UPROPERTY(EditAnywhere, Category = "Maze")
    TSubclassOf<AActor> WallActorClass;

    void GenerateMaze();

private:
    void DivideSpace(int32 StartX, int32 StartY, int32 EndX, int32 EndY);
    void PlaceWall(FVector Start, FVector End);
};
