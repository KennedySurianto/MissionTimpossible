// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelTeleporter.h"
#include "ShootingRangeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MISSIONTIMPOSSIBLE_API AShootingRangeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AShootingRangeGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Teleporter")
	TSoftObjectPtr<ALevelTeleporter> LevelTeleporterActor;
	
	void EnableTeleporterIfConditionMet();

	bool HasShot20Times();

	bool IsQuestFinished();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> InteractWidgetClass;

	// Timer handle to manage widget removal
	FTimerHandle TimerHandle;

	void ShowWidgetMessage(FString Text, float Duration);
};
