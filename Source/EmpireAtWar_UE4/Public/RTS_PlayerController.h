#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS_SpectatorPawn.h"
#include "RTS_PlayerController.generated.h"

class ARTS_CameraBoundsVolume;

UCLASS()
class EMPIREATWAR_UE4_API ARTS_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;

protected:

	virtual void SetupInputComponent() override;

	void GetCameraPawnReference();

private:

	/* Volume that restricts the camera movement of this player. */
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
};