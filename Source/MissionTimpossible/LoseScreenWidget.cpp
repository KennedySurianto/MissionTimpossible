#include "LoseScreenWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void ULoseScreenWidget::OpenShootingRange()
{
    const FName LevelName = FName("ShootingRange");

    // Load the specified level
    UGameplayStatics::OpenLevel(GetWorld(), LevelName);
    ResetCursor();
}

void ULoseScreenWidget::RestartCurrentLevel()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->RestartLevel();
        ResetCursor();
    }
}

void ULoseScreenWidget::NativeConstruct()
{
    Super::NativeConstruct();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        // Show the mouse cursor
        PlayerController->bShowMouseCursor = true;

        // Set input mode to UI only, so player can interact with the widget
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(this->TakeWidget());
        PlayerController->SetInputMode(InputMode);
    }

    // Bind BackToShootingRangeButton to OpenShootingRange function
    if (BackToShootingRangeButton)
    {
        BackToShootingRangeButton->OnClicked.AddDynamic(this, &ULoseScreenWidget::OpenShootingRange);
    }

    // Bind RestartLevelButton to RestartCurrentLevel function
    if (RestartLevelButton)
    {
        RestartLevelButton->OnClicked.AddDynamic(this, &ULoseScreenWidget::RestartCurrentLevel);
    }
}

void ULoseScreenWidget::ResetCursor()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = false;
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
    }
}
