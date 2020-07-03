#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "RTS_SpectatorPawn.generated.h"


/**
 * 
 */
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
	float CameraSpeed;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float CameraSpeedMultiplier;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float CameraZoomSpeed;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float MinCameraDistance;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float MaxCameraDistance;

	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	float CurrentCameraZoom;
	
	float DesiredCameraZoom;
	/* Distance from the screen border at which the mouse cursor causes the camera to move, in pixels. */
	UPROPERTY(EditAnywhere, Category = "CameraSettings", meta = (ClampMin = 0))
	int32 CameraScrollThreshold;
};
