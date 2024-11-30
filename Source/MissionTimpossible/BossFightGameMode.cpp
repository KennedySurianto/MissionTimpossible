#include "BossFightGameMode.h"
#include "BossHealthWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h" // For AActor
#include "GameFramework/PlayerController.h" // For PlayerController

void ABossFightGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (BossHealthWidgetClass && BossInstance)
    {
        UBossHealthWidget* BossHealthWidget = CreateWidget<UBossHealthWidget>(GetWorld(), BossHealthWidgetClass);
        if (BossHealthWidget)
        {
            BossHealthWidget->SetBossCharacter(BossInstance);
            BossHealthWidget->AddToViewport();

            UE_LOG(LogTemp, Log, TEXT("Boss Health Widget successfully created and added to viewport."));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create Boss Health Widget."));
        }
    }
    else
    {
        if (!BossHealthWidgetClass)
        {
            UE_LOG(LogTemp, Error, TEXT("BossHealthWidgetClass is not set in the GameMode."));
        }

        if (!BossInstance)
        {
            UE_LOG(LogTemp, Error, TEXT("Boss is not assigned in the GameMode."));
        }
    }
}
