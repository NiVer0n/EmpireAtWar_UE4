#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectionComponent.generated.h"

class UMaterialInterface;
class UMaterialInstanceDynamic;
class USoundCue;

UCLASS(meta=(BlueprintSpawnableComponent))
class EMPIREATWAR_UE4_API USelectionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void DestroyComponent(bool bPromoteChildren = false) override;

public:
	/* Selects the unit for the local player */
	UFUNCTION(BlueprintCallable)
	void SelectActor();

	/* Deselects the unit for the local player */
	UFUNCTION(BlueprintCallable)
	void DeselectActor();

	/* Checks whether the unit is currently selected by the local player, or not */
	UFUNCTION(BlueprintPure)
	bool IsSelected() const;

	/* Gets the sort index for selected units */
	UFUNCTION(BlueprintPure)
	int32 GetSelectionPriority() const;

	/* Gets the sound to play when the actor is selected */
	USoundCue* GetSelectedSound() const;

private:
	/* Sort index for selected units */
	UPROPERTY(EditDefaultsOnly, Category = "Selection Settings")
	int32 SelectionPriority;

	/* Material for rendering the selection circle of the actor */
	UPROPERTY(EditDefaultsOnly, Category = "Selection Settings")
	UMaterialInterface* SelectionCircleMaterial;

	/* Sound to play when the actor is selected */
	UPROPERTY(EditDefaultsOnly, Category = "Selection Settings")
	USoundCue* SelectedSound;

	/* Whether the unit is currently selected by the local player, or not */
	bool bSelected;

	/* Whether the unit is currently hovered by the local player, or not */
	bool bHovered;

	/* Decal used for rendering the selection circle of the actor */
	UPROPERTY()
	UDecalComponent* DecalComponent;

	/* Material instance for rendering the selection circle of the actor */
	UPROPERTY()
	UMaterialInstanceDynamic* SelectionCircleMaterialInstance;
};