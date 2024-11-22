// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "ShooterCharacter.h"
#include "ShootingRangeGameMode.h"

void UQuestWidget::Back()
{
    RemoveFromParent();
    ResetCursor();
}

FText UQuestWidget::GetBulletsShotText() const
{
    if (AShooterCharacter* Character = Cast<AShooterCharacter>(GetOwningPlayerPawn()))
    {
        return FText::AsNumber(Character->BulletsShot);
    }
    return FText::FromString(TEXT("0"));
}

FText UQuestWidget::GetMoveStatusText() const
{
    if (UWorld* World = GetWorld()) // Get the world context
    {
        // Get the current game mode
        AGameModeBase* GameMode = World->GetAuthGameMode();
        if (GameMode)
        {
            // Check if it's your specific game mode class
            AShootingRangeGameMode* ShootingRangeGameMode = Cast<AShootingRangeGameMode>(GameMode);
            if (ShootingRangeGameMode)
            {
                if (ShootingRangeGameMode->HasMoved())
                {
                    return FText::FromString(TEXT("Done"));
                }
                else
                {
                    return FText::FromString(TEXT("Not Done"));
                }
            }
        }
    }

    // Fallback return if conditions are not met
    return FText::FromString(TEXT("Unknown"));
}

FText UQuestWidget::GetReloadStatusText() const
{
    if (UWorld* World = GetWorld()) // Get the world context
    {
        // Get the current game mode
        AGameModeBase* GameMode = World->GetAuthGameMode();
        if (GameMode)
        {
            // Check if it's your specific game mode class
            AShootingRangeGameMode* ShootingRangeGameMode = Cast<AShootingRangeGameMode>(GameMode);
            if (ShootingRangeGameMode)
            {
                if (ShootingRangeGameMode->HasReloaded())
                {
                    return FText::FromString(TEXT("Done"));
                }
                else
                {
                    return FText::FromString(TEXT("Not Done"));
                }
            }
        }
    }

    // Fallback return if conditions are not met
    return FText::FromString(TEXT("Unknown"));
}

void UQuestWidget::NativeConstruct()
{
    Super::NativeConstruct();

    AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(GetWorld()->GetFirstPlayerController());
    if (ShooterPlayerController)
    {
        ShooterPlayerController->PauseGame();
    }

    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &UQuestWidget::Back);
    }
}

void UQuestWidget::ResetCursor()
{
    AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(GetWorld()->GetFirstPlayerController());
    if (ShooterPlayerController)
    {
        ShooterPlayerController->UnpauseGame();
    }
}
