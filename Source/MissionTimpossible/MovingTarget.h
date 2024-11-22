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

	// Override the TakeDamage function to handle damage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	// Static Mesh
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BallMesh;

	// Movement variables
	UPROPERTY(VisibleAnywhere)
	FVector StartLocation;

	UPROPERTY(VisibleAnywhere)
	FVector EndLocation;

	UPROPERTY(EditAnywhere)
	FVector Offset;

	UPROPERTY(EditAnywhere)
	float MoveSpeed;

	UPROPERTY(VisibleAnywhere)
	float MoveDirection;

	// Timer handle for resetting scale
	FTimerHandle TimerHandle_ResetScale;

	// Functions for movement
	void MoveBall(float DeltaTime);
};
