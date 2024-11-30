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

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	void Shoot();
	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	FText GetAmmoText() const;

	UPROPERTY(VisibleAnywhere)
	AInteractableBase* NearbyInteractable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	int32 BulletsShot;

	UPROPERTY(VisibleAnywhere, Category = "Quest")
	bool bHasReloaded;

	UPROPERTY(VisibleAnywhere, Category = "Quest")
	bool bHasMovedForward;

	UPROPERTY(VisibleAnywhere, Category = "Quest")
	bool bHasMovedLeft;

	UPROPERTY(VisibleAnywhere, Category = "Quest")
	bool bHasMovedBackward;

	UPROPERTY(VisibleAnywhere, Category = "Quest")
	bool bHasMovedRight;

	UPROPERTY(VisibleAnywhere, Category = "Quest")
	bool bHasJumped;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
    void Interact();
	void Reload();
	void Pause();
	void Jump();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PauseMenuClass;
};
