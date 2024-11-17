// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

/**
 * 
 */
UCLASS()
class MISSIONTIMPOSSIBLE_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Back();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GetBulletsShotText() const;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	virtual void NativeConstruct() override;

private:
	void ResetCursor();
};
