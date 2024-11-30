#include "BossHealthWidget.h"
#include "ShooterCharacter.h"

void UBossHealthWidget::SetBossCharacter(AShooterCharacter* InBossCharacter)
{
    BossCharacter = InBossCharacter;
}

float UBossHealthWidget::GetHealthPercent() const
{
    if (BossCharacter)
    {
        // Assuming ShooterCharacter has GetHealth() and GetMaxHealth() methods
        return BossCharacter->Health / BossCharacter->MaxHealth;
    }
    return 0.0f;
}
