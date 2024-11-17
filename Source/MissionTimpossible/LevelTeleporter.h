// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "LevelTeleporter.generated.h"

/**
 * 
 */
UCLASS()
class MISSIONTIMPOSSIBLE_API ALevelTeleporter : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	// Constructor
	ALevelTeleporter();

	// Function to handle overlap events
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// Name of the level to teleport to
	UPROPERTY(EditAnywhere, Category="Teleporter")
	FName LevelName;

	UFUNCTION(BlueprintCallable)
	void EnableTeleporter();

private:
	UPROPERTY(VisibleAnywhere)
	bool bIsEnabled;
};
