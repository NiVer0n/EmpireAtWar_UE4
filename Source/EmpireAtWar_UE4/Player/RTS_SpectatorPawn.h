#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "RTS_SpectatorPawn.generated.h"

UCLASS()
class EMPIREATWAR_UE4_API ARTS_SpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
public:
	
	ARTS_SpectatorPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* PawnCamera;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float CameraSpeed = 1000.0f;;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float CameraSpeedMultiplier = 1.0f;;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float CameraZoomSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float MinCameraDistance = 300.0f;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float MaxCameraDistance = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float CurrentCameraZoom = 1000.0f;
	
	float DesiredCameraZoom = CurrentCameraZoom;
	/* Distance from the screen border at which the mouse cursor causes the camera to move, in pixels. */
	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	int32 CameraScrollThreshold = 20;
};