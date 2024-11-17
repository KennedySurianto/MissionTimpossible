// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "ShooterCharacter.h"

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
