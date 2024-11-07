// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "Engine/Engine.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
	// Set this character to call Tick() every frame. 
	// Dimatiin karena gabutuh
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCCharacter::SayHello()
{
    // Print "Hello" to the screen
    if (GEngine)
    {
		FString Message = NPCName + TEXT(": Hello!");
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Message);
    }
}

