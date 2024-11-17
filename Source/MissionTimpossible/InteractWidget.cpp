// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWidget.h"
#include "Components/TextBlock.h"

void UInteractWidget::SetWidgetText(FString NewText)
{
    if (MyTextBlock)
    {
        MyTextBlock->SetText(FText::FromString(NewText));  // Set the text dynamically
    }
}
