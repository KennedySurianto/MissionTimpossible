#include "MovingTarget.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"


AMovingTarget::AMovingTarget()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set up the ball mesh
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    RootComponent = BallMesh;

    // Enable collision
    BallMesh->SetSimulatePhysics(false);
    BallMesh->SetNotifyRigidBodyCollision(true);

    // Set initial movement variables
    MoveSpeed = 300.0f;
    MoveDirection = 1.0f;

    // Bind the hit event
    BallMesh->OnComponentHit.AddDynamic(this, &AMovingTarget::OnHit);
}

void AMovingTarget::BeginPlay()
{
    Super::BeginPlay();

    // Set the starting position
    StartLocation = GetActorLocation();
    EndLocation = StartLocation + FVector(1000.0f, 0.0f, 0.0f);

    // Create a dynamic material instance and set the initial color to cyan
    if (BallMesh->GetMaterial(0))
    {
        DynamicMaterial = UMaterialInstanceDynamic::Create(BallMesh->GetMaterial(0), this);
        if (DynamicMaterial)
        {
            FLinearColor Cyan(0.0f, 1.0f, 1.0f);
            DynamicMaterial->SetVectorParameterValue("BaseColor", Cyan);
            BallMesh->SetMaterial(0, DynamicMaterial);
        }
    }
}

void AMovingTarget::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MoveBall(DeltaTime);
}

void AMovingTarget::MoveBall(float DeltaTime)
{
    FVector CurrentLocation = GetActorLocation();
    float Distance = (EndLocation - StartLocation).Size();

    CurrentLocation += FVector(MoveDirection * MoveSpeed * DeltaTime, 0, 0);

    if ((CurrentLocation - StartLocation).Size() >= Distance || (CurrentLocation - EndLocation).Size() >= Distance)
    {
        MoveDirection *= -1;
    }

    SetActorLocation(CurrentLocation);
}

void AMovingTarget::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (DynamicMaterial)
    {
        // Change the color to red on hit
        FLinearColor TestRedColor(1.0f, 0.0f, 0.0f); // Test red
        DynamicMaterial->SetVectorParameterValue("BaseColor", TestRedColor);

        // Set a timer to reset the color after 1 second
        GetWorld()->GetTimerManager().SetTimer(ColorResetTimer, this, &AMovingTarget::ResetColor, 1.0f, false);
    }

}

void AMovingTarget::ResetColor()
{
    if (DynamicMaterial)
    {
        // Reset color to cyan
        FLinearColor Cyan(0.0f, 1.0f, 1.0f);
        DynamicMaterial->SetVectorParameterValue("BaseColor", Cyan);
    }
}
