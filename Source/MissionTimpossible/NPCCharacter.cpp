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
    Super::Interact();

    if (QuestWidgetClass)
    {
        UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), QuestWidgetClass);

        if (WidgetInstance)
        {
            WidgetInstance->AddToViewport();
        }
    }
}
