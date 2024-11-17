#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h" // For USphereComponent
#include "Blueprint/UserWidget.h" // For UUserWidget
#include "InteractWidget.h"
#include "InteractableBase.generated.h"

UCLASS()
class MISSIONTIMPOSSIBLE_API AInteractableBase : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AInteractableBase();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to handle interactions (can be overriden in sub-class)
    virtual void Interact();

private:
    // Proximity detection using a sphere
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* ProximityTrigger;

    // UI widget class to display when the player is near
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> InteractWidgetClass;

    // The widget instance
    UPROPERTY()
    UUserWidget* InteractWidget;

    // Trigger events when the player overlaps the proximity sphere
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
