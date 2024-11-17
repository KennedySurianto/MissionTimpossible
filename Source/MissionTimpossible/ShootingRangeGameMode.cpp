// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingRangeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "InteractWidget.h"  // Include your custom widget header
#include "Components/Widget.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"

AShootingRangeGameMode::AShootingRangeGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShootingRangeGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnableTeleporterIfConditionMet();
}

void AShootingRangeGameMode::BeginPlay()
{
    Super::BeginPlay();  // Ensure you call the base class BeginPlay

    ShowWidgetMessage("Talk to Asuna!", 3);
}


void AShootingRangeGameMode::EnableTeleporterIfConditionMet()
{
    if (IsQuestFinished())
    {
        if (LevelTeleporterActor)
        {
            LevelTeleporterActor->EnableTeleporter();

            ShowWidgetMessage("All quests are done! Now go to the teleporter.", 5);

            PrimaryActorTick.bCanEverTick = false; // ini still looping, nanti fix
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

void AShootingRangeGameMode::ShowWidgetMessage(FString Text, float Duration)
{
    // Create the widget and add it to the player's viewport
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController && InteractWidgetClass)
    {
        UUserWidget* InteractWidget = CreateWidget<UUserWidget>(PlayerController, InteractWidgetClass);

        if (InteractWidget)
        {
            UInteractWidget* SpecificInteractWidget = Cast<UInteractWidget>(InteractWidget);
            if (SpecificInteractWidget)
            {
                // Set the text to display "Talk to Asuna!"
                SpecificInteractWidget->SetWidgetText(Text);
                SpecificInteractWidget->AddToViewport();

                // Set a timer to hide the widget after 3 seconds
                GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([SpecificInteractWidget]()
                {
                    if (SpecificInteractWidget)
                    {
                        SpecificInteractWidget->RemoveFromViewport(); // Remove the widget from the viewport
                    }
                }), Duration, false); // Timer set for 3 seconds, not looping
            }
        }
    }
}
