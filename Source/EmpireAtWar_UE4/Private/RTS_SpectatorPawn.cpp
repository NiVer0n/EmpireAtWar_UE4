#include "RTS_SpectatorPawn.h"

ARTS_SpectatorPawn::ARTS_SpectatorPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	bAddDefaultMovementBindings = false;
	/* Initialize camera settings*/
	CameraSpeed = 1000.0f;
	CameraSpeedMultiplier = 1.0f;
	CameraZoomSpeed = 5.0f;
	MinCameraDistance = 300.0f;
	MaxCameraDistance = 2000.0f;
	CurrentCameraZoom = 1000.0f;
	DesiredCameraZoom = CurrentCameraZoom;
	CameraScrollThreshold = 20.0f;
	/* Create and setup components */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = CurrentCameraZoom;
	SpringArm->bDoCollisionTest = false;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	PawnCamera->SetupAttachment(SpringArm);
}