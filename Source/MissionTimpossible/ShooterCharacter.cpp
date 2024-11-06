// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NearbyNPC = nullptr; // Initialize NearbyNPC to nullptr

	// Create a sphere component for detecting overlap with NPCs
    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->InitSphereRadius(200.0f); // Adjust radius as needed
    InteractionSphere->SetupAttachment(RootComponent);

    // Bind overlap events
    InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AShooterCharacter::OnOverlapBegin);
    InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AShooterCharacter::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	// ^ Arguments: binding in UE, target, function (pointer)
	// Lookup, LookRight, Jump lgsg pake parent function karena argsnya gadiapa"in lg

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AShooterCharacter::Interact);
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
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