// SettingsMenuWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "SettingsMenuWidget.generated.h"

UCLASS()
class MISSIONTIMPOSSIBLE_API USettingsMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    // Window Mode Buttons
    UPROPERTY(meta = (BindWidget))
    UButton* WindowModeMin;

    UPROPERTY(meta = (BindWidget))
    UButton* WindowModePlus;

    // Resolution Buttons
    UPROPERTY(meta = (BindWidget))
    UButton* ResolutionMin;

    UPROPERTY(meta = (BindWidget))
    UButton* ResolutionPlus;

    // VSync Button
    UPROPERTY(meta = (BindWidget))
    UButton* VSyncMin;

    UPROPERTY(meta = (BindWidget))
    UButton* VSyncPlus;

    // Graphics Quality Buttons
    UPROPERTY(meta = (BindWidget))
    UButton* GraphicsMin;

    UPROPERTY(meta = (BindWidget))
    UButton* GraphicsPlus;

    UPROPERTY(meta = (BindWidget))
    UButton* SaveChangesButton;

    UPROPERTY(meta = (BindWidget))
    UButton* BackToMainMenuButton;

private:
    // Window Mode Functions
    UFUNCTION()
    void OnWindowModeMinClicked();

    UFUNCTION()
    void OnWindowModePlusClicked();

    // Resolution Functions
    UFUNCTION()
    void OnResolutionMinClicked();

    UFUNCTION()
    void OnResolutionPlusClicked();

    // VSync Function
    UFUNCTION()
    void OnVSyncButtonClicked();

    // Graphics Quality Functions
    UFUNCTION()
    void OnGraphicsMinClicked();

    UFUNCTION()
    void OnGraphicsPlusClicked();

    UFUNCTION()
    void OnSaveChangesClicked();

    UFUNCTION()
    void OnBackToMainMenuClicked();

    UPROPERTY(EditAnywhere)
    TSubclassOf<class UUserWidget> MainMenuClass;

    // Helper Arrays for Resolutions and Window Modes
    TArray<FIntPoint> SupportedResolutions;
    TArray<EWindowMode::Type> SupportedWindowModes;
    int32 CurrentResolutionIndex;
    int32 CurrentWindowModeIndex;
    int32 CurrentGraphicsQualityLevel;
};