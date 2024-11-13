#include "NPCCharacter.h"
#include "ShooterCharacter.h" // For character reference
#include "ShooterPlayerController.h" // For PlayerController reference

// Constructor
ANPCCharacter::ANPCCharacter()
{
    // Set default values for NPC properties
    PrimaryActorTick.bCanEverTick = true;

    // You could set custom values for the NPC here
    DialogueMessage = TEXT("Hello, brave adventurer! How can I assist you?");
}

// BeginPlay function (you can add specific initialization logic for the NPC here)
void ANPCCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Tick function (if you need NPC-specific ticking behavior, such as animations or movement)
void ANPCCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Override the Interact function to define NPC interaction (e.g., displaying a dialogue)
void ANPCCharacter::Interact()
{
    // Call base class interaction (if you want to keep common functionality)
    Super::Interact();

    // Logic for NPC-specific interaction, e.g., displaying a message
    if (DialogueMessage.Len() > 0)
    {
        // Display dialogue or do something else
        UE_LOG(LogTemp, Log, TEXT("NPC says: %s"), *DialogueMessage);

        // You can add more complex interaction logic, like showing a UI for dialogue here
    }
}
