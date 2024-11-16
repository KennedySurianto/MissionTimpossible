#include "LoseScreenWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "ShooterPlayerController.h"

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

    AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(GetWorld()->GetFirstPlayerController());
    if (ShooterPlayerController)
    {
        ShooterPlayerController->PauseGame();
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
    AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(GetWorld()->GetFirstPlayerController());
    if (ShooterPlayerController)
    {
        ShooterPlayerController->UnpauseGame();
    }
}
