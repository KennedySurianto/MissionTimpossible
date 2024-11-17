// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class MISSIONTIMPOSSIBLE_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // Function to set the text of the widget
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetWidgetText(FString NewText);

protected:
    // Reference to the TextBlock in the widget
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* MyTextBlock; 
};
