// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Gun.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
    // NPC Logics
    NearbyNPC = nullptr;

	    // Create a sphere component for detecting overlap with NPCs
    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->InitSphereRadius(200.0f);
    InteractionSphere->SetupAttachment(RootComponent);

        // Bind overlap events
    InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AShooterCharacter::OnOverlapBegin);
    InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AShooterCharacter::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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

void AShooterCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
									class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
									bool bFromSweep, const FHitResult & SweepResult)
{
    // Check if overlapping actor is an NPCCharacter
    ANPCCharacter* OverlappedNPC = Cast<ANPCCharacter>(OtherActor);
    if (OverlappedNPC)
    {
        NearbyNPC = OverlappedNPC; // Store reference to the NPC
    }
}

void AShooterCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
                                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor == NearbyNPC)
    {
        NearbyNPC = nullptr; // Clear reference when leaving the NPC’s range
    }
}

void AShooterCharacter::Interact()
{
    if (NearbyNPC)
    {
        NearbyNPC->SayHello(); // Call SayHello on the NPC
    }
}