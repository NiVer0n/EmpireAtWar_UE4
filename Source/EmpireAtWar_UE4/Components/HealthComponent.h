#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "EmpireAtWar_UE4/UI/HealthbarWidget.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EMPIREATWAR_UE4_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	// Sets default values for this component's properties
	virtual void BeginPlay() override;

	/* Component owner */
	AActor* Owner;

	/* Event for applying any damage to unit */
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/* Destroy current unit */
	UFUNCTION(BlueprintCallable)
	void DestroyUnit();

	UFUNCTION()
	void InitializeHealthWidget();

	/* Max unit health value */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Settings", meta = (ClampMin = "1.0"))
	float MaxHealth = 1.0f;

	/* Current unit health value */
	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;
	
	/* Component used for rendering the healthbar of the actor */
	UPROPERTY()
	UWidgetComponent* HealthbarWidgetComponent;

	/* Healthbar widget class for owning actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Settings")
	TSubclassOf<UUserWidget> HealthbarWidgetClass;
	
	/* Healthbar widget needed to update visual */
	UPROPERTY()
	UHealthbarWidget* HealthbarWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Settings")
	FVector HealthbarOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Settings")
	FVector2D HealthbarSize = FVector2D(200.0f, 10.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Settings")
	bool bHasShields;

	/* Max unit shields value */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Settings", meta=(EditCondition="bHasShields"))
	float MaxShields = 1.0f;

	/* Max unit shields value */
	UPROPERTY(BlueprintReadOnly)
	float CurrentShields;
};