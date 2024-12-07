#include "BossFightGameMode.h"
#include "BossHealthWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h" // For AActor
#include "GameFramework/PlayerController.h" // For PlayerController
#include "EngineUtils.h"

void ABossFightGameMode::BeginPlay()
{
    Super::BeginPlay();

    BossInstance = nullptr;

    for (TActorIterator<AShooterCharacter> It(GetWorld()); It; ++It)
    {
        AShooterCharacter* Boss = *It;
        UE_LOG(LogTemp, Log, TEXT("Iterating: %s"), *Boss->GetName());
        if (Boss && Boss->GetName().Contains("BP_ShooterCharacter_C_3"))
        {
            UE_LOG(LogTemp, Log, TEXT("Found Boss with label: %s"), *Boss->GetName());
            BossInstance = Boss;
            break;
        }
    }


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
