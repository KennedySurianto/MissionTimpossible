// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KillEmAllGameMode.h"
#include "ShooterCharacter.h"
#include "BossHealthWidget.h"
#include "BossFightGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MISSIONTIMPOSSIBLE_API ABossFightGameMode : public AKillEmAllGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	AShooterCharacter* BossInstance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBossHealthWidget> BossHealthWidgetClass;

};
