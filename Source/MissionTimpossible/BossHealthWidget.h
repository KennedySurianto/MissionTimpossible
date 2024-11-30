#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterCharacter.h"
#include "BossHealthWidget.generated.h"

class AShooterCharacter; // Forward declaration

UCLASS()
class MISSIONTIMPOSSIBLE_API UBossHealthWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** Set the boss character to track */
    UFUNCTION(BlueprintCallable, Category = "Boss Health")
    void SetBossCharacter(AShooterCharacter* BossCharacter);

protected:
    /** Reference to the boss character being tracked */
    UPROPERTY(BlueprintReadOnly, Category = "Boss Health", meta = (ExposeOnSpawn = true))
    AShooterCharacter* BossCharacter;

    /** Updates the progress bar value */
    UFUNCTION(BlueprintPure, Category = "Boss Health")
    float GetHealthPercent() const;
};
