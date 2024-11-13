// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacter.h"

#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "MissionTimpossibleGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // NPC Logics
    NearbyInteractable = nullptr;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

    Gun = GetWorld()->SpawnActor<AGun>(GunClass);
    // Hide the default gun in hand (the bone name is 'weapon_r')
    GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
    Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
    Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Basic movement
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
    // ^ Arguments: binding in UE, target, function (pointer)
    // Lookup, LookRight, Jump lgsg pake parent function karena argsnya gadiapa"in lg

    // Actions
    PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Interact);
    PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    DamageToApply = FMath::Min(DamageToApply, Health);
    Health -= DamageToApply;

    UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

    if (IsDead())
    {
        AMissionTimpossibleGameModeBase* GameMode = Cast<AMissionTimpossibleGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode != nullptr)
        {
            GameMode->PawnKilled(this);
        }
        DetachFromControllerPendingDestroy();
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    return DamageToApply;
}

bool AShooterCharacter::IsDead() const
{
    return Health <= 0;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
    AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
    AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::Shoot()
{
    Gun->PullTrigger();
}

void AShooterCharacter::Interact()
{
    // Implement interact logic for main character here
    if (NearbyInteractable)
    {
        //ANPCCharacter* NPCCharacter = Cast<ANPCCharacter>(NearbyInteractable);
        NearbyInteractable->Interact();
    }
}