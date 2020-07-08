#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTS_HUD.generated.h"

class ARTS_PlayerController;

UCLASS()
class EMPIREATWAR_UE4_API ARTS_HUD : public AHUD
{
	GENERATED_BODY()

public:
	/* Array of actors for selection */
	TArray<AActor*> ActorsInSelectionRect;

	virtual void DrawHUD() override;

	/* Call deselection in selected actors */
	void DeselectActors();

	/* Select actors if possible */
	void SelectActors();

private:
	/* Player controller reference */
	UPROPERTY(VisibleAnywhere, Category = "HUD")
	ARTS_PlayerController* PlayerController;

	/* Selection frame color */
	UPROPERTY(EditAnywhere, Category = "HUD")
	FLinearColor SelectionFrameColor;

	/* Draws the current selection frame if mouse is being dragged */
	void DrawSelectionFrame();

protected:

	virtual void BeginPlay() override;
};