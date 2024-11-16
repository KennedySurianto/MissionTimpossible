// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "ShooterPlayerController.h"

void UPauseMenuWidget::Resume()
{
    RemoveFromParent();
    ResetCursor();
}

void UPauseMenuWidget::Settings()
{
}

void UPauseMenuWidget::BackToMainMenu()
{
    const FName LevelName = FName("MainMenuMap");
    UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void UPauseMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(GetWorld()->GetFirstPlayerController());
    if (ShooterPlayerController)
    {
        ShooterPlayerController->PauseGame();
    }

    if (ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Resume);
    }

    if (SettingsButton)
    {
        SettingsButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Settings);
    }

    if (BackToMainMenuButton)
    {
        BackToMainMenuButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::BackToMainMenu);
    }
    
}

void UPauseMenuWidget::ResetCursor()
{
    AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(GetWorld()->GetFirstPlayerController());
    if (ShooterPlayerController)
    {
        ShooterPlayerController->UnpauseGame();
    }
}
