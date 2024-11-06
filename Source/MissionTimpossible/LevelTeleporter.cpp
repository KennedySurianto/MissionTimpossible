// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTeleporter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

ALevelTeleporter::ALevelTeleporter()
{
    // Bind the overlap event
    OnActorBeginOverlap.AddDynamic(this, &ALevelTeleporter::OnOverlapBegin);
}

void ALevelTeleporter::BeginPlay()
{
    Super::BeginPlay();
}

void ALevelTeleporter::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    // Check if the overlapping actor is the player
    if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
    {
        // Check if LevelName is valid
        if (!LevelName.IsNone())
        {
            UWorld* World = GetWorld();
            if (World)
            {
                // Open the specified level
                UGameplayStatics::OpenLevel(World, LevelName);
            }
        }
    }
}
