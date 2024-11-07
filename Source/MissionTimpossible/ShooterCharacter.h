// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class MISSIONTIMPOSSIBLE_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Shoot();

	// Reference to the NPC for interaction
    ANPCCharacter* NearbyNPC;

    // Function to interact with the NPC
    void Interact();

    // Function to detect when the player is near an NPC
    UFUNCTION()
    void OnOverlapBegin(
		class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult & SweepResult
	);

    UFUNCTION()
    void OnOverlapEnd(
		class UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
	);

	// Sphere component for detecting overlap with NPCs
    UPROPERTY(VisibleAnywhere)
    class USphereComponent* InteractionSphere;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;
};
