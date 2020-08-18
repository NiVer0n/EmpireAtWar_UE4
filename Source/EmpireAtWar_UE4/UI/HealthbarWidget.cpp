#include "HealthbarWidget.h"
#include "Components/Progressbar.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void UHealthbarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PB_Healthbar)
	{
		PB_Healthbar->SetPercent(1.0f);
		PB_Healthbar->SetFillColorAndOpacity(GoodHealthColor);
	}
	if (PB_Shieldsbar && bOwnerHasShields)
	{
		PB_Shieldsbar->SetVisibility(ESlateVisibility::Visible);
		PB_Shieldsbar->SetPercent(1.0f);
		PB_Shieldsbar->SetFillColorAndOpacity(ShieldsColor);
	}
}

void UHealthbarWidget::UpdateHealth(float CurrentHealth, float MaxHealth, float CurrentShields, float MaxShields)
{
	if (PB_Healthbar)
	{
		float HealthPercent = CurrentHealth / MaxHealth;
		PB_Healthbar->SetPercent(HealthPercent);
		PB_Healthbar->SetFillColorAndOpacity(UKismetMathLibrary::CInterpTo(BadHealthColor, GoodHealthColor,
			UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), CurrentHealth));
	}
	if (PB_Shieldsbar)
	{
		PB_Shieldsbar->SetPercent(CurrentShields / MaxShields);
	}
}