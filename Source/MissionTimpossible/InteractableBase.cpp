#include "InteractableBase.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h" // For Player Controller
#include "ShooterCharacter.h"  // For interacting with the player character
#include "ShooterPlayerController.h" // For custom player controller if needed

// Constructor
AInteractableBase::AInteractableBase()
{
    // Set default values for the actor's properties
    PrimaryActorTick.bCanEverTick = true;

    // Create the sphere component for proximity detection
    ProximityTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("ProximityTrigger"));
    RootComponent = ProximityTrigger;  // Set sphere as the root component
    ProximityTrigger->SetSphereRadius(200.0f);  // Radius for interaction area
    ProximityTrigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractableBase::OnOverlapBegin);
    ProximityTrigger->OnComponentEndOverlap.AddDynamic(this, &AInteractableBase::OnOverlapEnd);
}

// BeginPlay function
void AInteractableBase::BeginPlay()
{
    Super::BeginPlay();
}

// Tick function (if needed for any other functionality in the future)
void AInteractableBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Overlap begin - called when something enters the proximity sphere
void AInteractableBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Display, TEXT("Player overlapped."))

    // Check if the overlapping actor is a valid character (ShooterCharacter)
    AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OtherActor);

    if (ShooterCharacter && MessageWidgetClass)
    {
        ShooterCharacter->NearbyInteractable = this;

        // Get the PlayerController of the ShooterCharacter
        APlayerController* PlayerController = Cast<APlayerController>(ShooterCharacter->GetController());
        AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(PlayerController);

        // Check if we successfully cast to ShooterPlayerController and if MessageWidget isn't already created
        if (ShooterPlayerController && !MessageWidget)
        {
            // Create and display the widget
            MessageWidget = CreateWidget<UUserWidget>(ShooterPlayerController, MessageWidgetClass);
            if (MessageWidget)
            {
                MessageWidget->AddToViewport();  // Add widget to the player's viewport
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("ShooterCharacter or MessageWidgetClass is null."));
    }
}

// Overlap end - called when something leaves the proximity sphere
void AInteractableBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
    // Check if the actor leaving is the ShooterCharacter
    AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OtherActor);

    if (ShooterCharacter && MessageWidget)
    {
        // Remove the message widget when the character leaves the proximity
        MessageWidget->RemoveFromViewport();
        MessageWidget = nullptr;
    }
}

// Interact function - can be overridden in child classes for specific interactions
void AInteractableBase::Interact()
{
    // Logic for interaction (e.g., NPC talking, picking up an item, etc.)
}
