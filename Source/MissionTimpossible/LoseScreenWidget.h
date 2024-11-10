// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoseScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class MISSIONTIMPOSSIBLE_API ULoseScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OpenShootingRange();

	UFUNCTION()
	void RestartCurrentLevel();

	void ResetCursor();

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BackToShootingRangeButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartLevelButton;
};
