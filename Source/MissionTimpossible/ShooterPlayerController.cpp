// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "InteractWidget.h"

void AShooterPlayerController::BeginPlay()
{
    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}


void AShooterPlayerController::PauseGame()
{
    this->SetPause(true);
    this->bShowMouseCursor = true;
    FInputModeUIOnly InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    this->SetInputMode(InputMode);
}

void AShooterPlayerController::UnpauseGame()
{
    this->SetPause(false);
    this->bShowMouseCursor = false;
    FInputModeGameOnly InputMode;
    this->SetInputMode(InputMode);
}

void AShooterPlayerController::GameHasEnded(AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD->RemoveFromViewport();
    if (bIsWinner)
    {
        /*UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }*/
        UE_LOG(LogTemp, Warning, TEXT("bIsWinner is true"));

        UUserWidget* InteractWidget = CreateWidget<UUserWidget>(this, InteractWidgetClass);
        if (InteractWidget)
        {
            UInteractWidget* SpecificInteractWidget = Cast<UInteractWidget>(InteractWidget);
            if (SpecificInteractWidget)
            {
                SpecificInteractWidget->SetWidgetText("All enemies are dead, go to the teleporter!");
                SpecificInteractWidget->AddToViewport();
            }
            else {
                UE_LOG(LogTemp, Warning, TEXT("SpecificInteractWidget is null"));
            }
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("InteractWidget is null"));
        }

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("bIsWinner is false"));

        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }

    UE_LOG(LogTemp, Display, TEXT("Game has ended"));
}
