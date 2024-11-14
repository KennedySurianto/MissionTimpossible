// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingTarget.generated.h"

UCLASS()
class MISSIONTIMPOSSIBLE_API AMovingTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Static Mesh
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BallMesh;

	// Movement variables
	FVector StartLocation;
	FVector EndLocation;
	float MoveSpeed;
	float MoveDirection;

	// Dynamic Material Instance for color change
	UMaterialInstanceDynamic* DynamicMaterial;

	// Function to reset color
	void ResetColor();

	// Timer to revert color
	FTimerHandle ColorResetTimer;

	// Functions for movement
	void MoveBall(float DeltaTime);

	// Function to handle being hit
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
