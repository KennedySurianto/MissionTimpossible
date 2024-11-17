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

private:
	UPROPERTY(EditAnywhere, Category = "Teleporter")
	TSoftObjectPtr<ALevelTeleporter> LevelTeleporterActor;
	
	void EnableTeleporterIfConditionMet();

	bool HasShot20Times();

	bool IsQuestFinished();

};
