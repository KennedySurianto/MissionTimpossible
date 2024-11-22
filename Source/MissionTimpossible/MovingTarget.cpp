#include "MovingTarget.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AMovingTarget::AMovingTarget()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set up the ball mesh
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = BallMesh;

	// Enable collision
	BallMesh->SetSimulatePhysics(false);
	BallMesh->SetNotifyRigidBodyCollision(true);
	BallMesh->SetGenerateOverlapEvents(true);

	// Set initial movement variables
	MoveSpeed = 300.0f;
	MoveDirection = 1.0f;

	// Set up the damage response
	SetCanBeDamaged(true);
}

void AMovingTarget::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + Offset;
}

void AMovingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveBall(DeltaTime);
}

void AMovingTarget::MoveBall(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (EndLocation - StartLocation).GetSafeNormal();
	float Distance = (EndLocation - StartLocation).Size();

	// Update the current location
	CurrentLocation += MoveDirection * Direction * MoveSpeed * DeltaTime;

	// Check if the actor has moved beyond StartLocation or EndLocation
	if ((CurrentLocation - StartLocation).Size() > Distance || (CurrentLocation - EndLocation).Size() > Distance)
	{
		MoveDirection *= -1; // Reverse the direction
	}

	SetActorLocation(CurrentLocation);
}

float AMovingTarget::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// Set the actor's scale to 0 when hit
	SetActorScale3D(FVector(0.0f, 0.0f, 0.0f));

	// Use a timer to reset the scale after 3 seconds
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_ResetScale,
			FTimerDelegate::CreateLambda([this]()
		{
			//UE_LOG(LogTemp, Warning, TEXT("Resetting scale to 1.0"));
			SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
		}),
			1.0f,
			false
		);
	}

	return DamageAmount;
}
