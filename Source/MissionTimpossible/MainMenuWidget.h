// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MISSIONTIMPOSSIBLE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void PlayGame();

	UFUNCTION()
	void Settings();

	UFUNCTION()
	void QuitGame();


protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* PlayGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGameButton;

	virtual void NativeConstruct() override;

private:
	void OpenLevel(FString LevelString);
	void ResetCursor();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> SettingsMenuClass;
};
