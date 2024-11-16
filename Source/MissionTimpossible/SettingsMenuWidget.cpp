// SettingsMenuWidget.cpp
#include "SettingsMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/GameViewportClient.h"

void USettingsMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Initialize supported resolutions
    SupportedResolutions = {
        FIntPoint(1280, 720),   // HD
        FIntPoint(1920, 1080),  // Full HD
        FIntPoint(2560, 1440),  // QHD
        FIntPoint(3840, 2160)   // 4K
    };

    // Initialize supported window modes
    SupportedWindowModes = {
        EWindowMode::Windowed,
        EWindowMode::WindowedFullscreen,
        EWindowMode::Fullscreen
    };

    // Get current game user settings
    UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings();

    // Set initial indices
    CurrentResolutionIndex = SupportedResolutions.IndexOfByKey(GameUserSettings->GetScreenResolution());
    CurrentWindowModeIndex = SupportedWindowModes.IndexOfByKey(GameUserSettings->GetFullscreenMode());
    CurrentGraphicsQualityLevel = GameUserSettings->GetOverallScalabilityLevel();

    // Bind button clicks
    if (WindowModeMin)
        WindowModeMin->OnClicked.AddDynamic(this, &USettingsMenuWidget::OnWindowModeMinClicked);

    if (WindowModePlus)
        WindowModePlus->OnClicked.AddDynamic(this, &USettingsMenuWidget::OnWindowModePlusClicked);

    if (ResolutionMin)
        ResolutionMin->OnClicked.AddDynamic(this, &USettingsMenuWidget::OnResolutionMinClicked);

    if (ResolutionPlus)
        ResolutionPlus->OnClicked.AddDynamic(this, &USettingsMenuWidget::OnResolutionPlusClicked);

    if (VSyncMin)
        VSyncMin->OnClicked.AddDynamic(this, &USettingsMenuWidget::OnVSyncButtonClicked);

    if (GraphicsMin)
        GraphicsMin->OnClicked.AddDynamic(this, &USettingsMenuWidget::OnGraphicsMinClicked);

    if (GraphicsPlus)
        GraphicsPlus->OnClicked.AddDynamic(this, &USettingsMenuWidget::OnGraphicsPlusClicked);

    if (SaveChangesButton)
        SaveChangesButton->OnClicked.AddDynamic(this, &USettingsMenuWidget::OnSaveChangesClicked);

    if (BackToMainMenuButton)
        BackToMainMenuButton->OnClicked.AddDynamic(this, &USettingsMenuWidget::OnBackToMainMenuClicked);
}

void USettingsMenuWidget::OnWindowModeMinClicked()
{

}

void USettingsMenuWidget::OnWindowModePlusClicked()
{
    
}

void USettingsMenuWidget::OnResolutionMinClicked()
{
    
}

void USettingsMenuWidget::OnResolutionPlusClicked()
{
    
}

void USettingsMenuWidget::OnVSyncButtonClicked()
{
    
}

void USettingsMenuWidget::OnGraphicsMinClicked()
{
    
}

void USettingsMenuWidget::OnGraphicsPlusClicked()
{
    
}

void USettingsMenuWidget::OnSaveChangesClicked()
{

}

void USettingsMenuWidget::OnBackToMainMenuClicked()
{
    UUserWidget* MainMenu = CreateWidget(this, MainMenuClass);
    if (MainMenu != nullptr)
    {
        RemoveFromParent();
        MainMenu->AddToViewport();
    }
}
