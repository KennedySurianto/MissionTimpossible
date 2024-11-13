#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h" // Inherit from AInteractableBase
#include "NPCCharacter.generated.h"

UCLASS()
class MISSIONTIMPOSSIBLE_API ANPCCharacter : public AInteractableBase
{
    GENERATED_BODY()

public:
    // Constructor to set default values for this NPC character
    ANPCCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Override the Interact function to add NPC-specific behavior (like dialogue)
    virtual void Interact() override;

private:
    // Add any NPC-specific properties here (e.g., a dialog message)
    UPROPERTY(EditAnywhere, Category = "NPC")
    FString DialogueMessage;
};
