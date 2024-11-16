// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MISSIONTIMPOSSIBLE_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Resume();

	UFUNCTION()
	void Settings();

	UFUNCTION()
	void BackToMainMenu();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackToMainMenuButton;

	virtual void NativeConstruct() override;

private:
	void ResetCursor();

};
