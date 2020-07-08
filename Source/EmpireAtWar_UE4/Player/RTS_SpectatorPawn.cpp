#include "RTS_SpectatorPawn.h"

ARTS_SpectatorPawn::ARTS_SpectatorPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	bAddDefaultMovementBindings = false;
	/* Create and setup components */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = CurrentCameraZoom;
	SpringArm->bDoCollisionTest = false;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	PawnCamera->SetupAttachment(SpringArm);
}