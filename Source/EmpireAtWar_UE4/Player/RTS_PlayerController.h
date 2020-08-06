#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS_SpectatorPawn.h"
#include "EmpireAtWar_UE4/Utils/RTS_CameraBoundsVolume.h"
#include "RTS_PlayerController.generated.h"

UCLASS()
class EMPIREATWAR_UE4_API ARTS_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/* Whether currently creating a selection frame by dragging the mouse */
	bool bCreatingSelectionFrame;

	/* Initial mouse cursor location when pressing */
	FVector2D StartPoint;

	/* Last mouse cursor location when releasing */
	FVector2D EndPoint;

	/* Selected units */
	TArray<AActor*> SelectedActors;

	virtual void PlayerTick(float DeltaTime) override;

	/* Gets the current selection frame, in screen space */
	UFUNCTION()
	FVector2D GetCurrentMousePosition();

protected:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetupInputComponent() override;

private:

	/* Volume that restricts the camera movement of this player */
	UPROPERTY()
	ARTS_CameraBoundsVolume* CameraBoundsVolume;

	/* Camera pawn reference */
	ARTS_SpectatorPawn* PlayerPawn;

	/* Is camera movement allowed */
	bool bIsMovementEnabled;

	/* Last vertical axis input applied to camera movement */
	float CameraForwardAxisValue;

	/* Last horizontal axis input applied to camera movement */
	float CameraRightAxisValue;

	/* Last horizontal axis input applied to camera movement */
	float CameraZoomAxisValue;

	/* Viewport size for detection of screen edge */
	FVector2D ViewportSize;

	/* Screen Y edge */
	float ScrollBorderTop;

	/* Screen X edge */
	float ScrollBorderRight;

	/* Update camera coordinates while input or screen edge dragging */
	void UpdateCameraMovement(float DeltaTime);

	/* Update camera zoom */
	void UpdateCameraZoom(float DeltaTime);
	
	/* Vertical axis input to camera movement */
	void MoveForward(float Value);
	
	/* Horizontal axis input to camera movement */
	void MoveRight(float Value);

	/* Zoom input */
	void ZoomCamera(float Value);

	/* Remembers the current mouse position for multi-selection, finished by FinishSelectActors */
	UFUNCTION()
	void StartSelectActors();

	/* Selects all selectable actors within the created selection frame, started by StartSelectActors */
	UFUNCTION()
	void FinishSelectActors();


	UFUNCTION()
	void HandleOrder();
};