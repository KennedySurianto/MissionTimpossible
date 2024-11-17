// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingRangeGameMode.h"
#include "Kismet/GameplayStatics.h"

AShootingRangeGameMode::AShootingRangeGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShootingRangeGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnableTeleporterIfConditionMet();
}

void AShootingRangeGameMode::EnableTeleporterIfConditionMet()
{
    if (IsQuestFinished())
    {
        if (LevelTeleporterActor)
        {
            LevelTeleporterActor->EnableTeleporter();

            PrimaryActorTick.bCanEverTick = false;
        }
    }
}

bool AShootingRangeGameMode::HasShot20Times()
{
    if (AShooterCharacter* Character = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
        return Character->BulletsShot >= 20;

    return false;
}

bool AShootingRangeGameMode::IsQuestFinished()
{
    return HasShot20Times();
}
