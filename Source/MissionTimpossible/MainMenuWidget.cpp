// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UMainMenuWidget::OpenLevel(FString LevelString)
{
    const FName LevelName = FName(LevelString);
    UGameplayStatics::OpenLevel(GetWorld(), LevelName);
    ResetCursor();
}

void UMainMenuWidget::PlayGame()
{
    OpenLevel("ShootingRange");
}

void UMainMenuWidget::Settings()
{
}

void UMainMenuWidget::QuitGame()
{
    UE_LOG(LogTemp, Warning, TEXT("Quitting..."))
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

void UMainMenuWidget::ResetCursor()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = false;
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
    }
}

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = true;
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(this->TakeWidget());
        PlayerController->SetInputMode(InputMode);
    }

    if (PlayGameButton)
    {
        PlayGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGame);
    }

    if (SettingsButton)
    {
        SettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::Settings);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
    }
}
