#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthbarWidget.generated.h"

UCLASS()
class EMPIREATWAR_UE4_API UHealthbarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float CurrentHealth, float MaxHealth, float CurrentShields, float MaxShields);

	/* Whether owner has shields */
	bool bOwnerHasShields;

protected:

	virtual void NativeConstruct() override;

	/* Widget subclass of type Progressbar for healthbar */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* PB_Healthbar;

	/* Widget subclass of type Progressbar for shieldsbar */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* PB_Shieldsbar;
	
	/* Color for full health */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Settings")
	FLinearColor GoodHealthColor;

	/* Color for low health */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Settings")
	FLinearColor BadHealthColor;

	/* Color for shields */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Settings")
	FLinearColor ShieldsColor;
};
