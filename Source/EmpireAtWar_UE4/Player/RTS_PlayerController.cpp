#include "RTS_PlayerController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/CollisionProfile.h"
#include "EmpireAtWar_UE4/Components/ShipMovementComponent.h"

void ARTS_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerPawn = Cast<ARTS_SpectatorPawn>(InPawn);
	//UE_LOG(LogTemp, Log, TEXT("%s"), *UKismetSystemLibrary::GetDisplayName(PlayerPawn));
	if (!PlayerPawn) return;
}

void ARTS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	/* Enable mouse input */
	bShowMouseCursor = true; 
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bIsMovementEnabled = true;
	/* Bind actions */
	InputComponent->BindAction(TEXT("Select"), IE_Pressed, this, &ARTS_PlayerController::StartSelectActors);
	InputComponent->BindAction(TEXT("Select"), IE_Released, this, &ARTS_PlayerController::FinishSelectActors);
	InputComponent->BindAction(TEXT("ExecuteOrder"), IE_Pressed, this, &ARTS_PlayerController::HandleOrder); /* 66 */
	//InputComponent->BindAction(TEXT("ExecuteOrder"), IE_Released, this, &ARTS_PlayerController::FinishSelectActors);

	InputComponent->BindAxis(TEXT("MoveForward"),	this, &ARTS_PlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"),		this, &ARTS_PlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("ZoomCamera"),	this, &ARTS_PlayerController::ZoomCamera);
	/* Get camera bounds */
	for (TActorIterator<ARTS_CameraBoundsVolume> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		CameraBoundsVolume = *ActorItr;
		break;
	}

	if (!CameraBoundsVolume)
	{
		UE_LOG(LogTemp, Warning, TEXT("No RTS_CameraBoundsVolume found. Free camera movement enabled."));
	}
}

void ARTS_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	UpdateCameraMovement(DeltaTime);
	UpdateCameraZoom(DeltaTime);
}

void ARTS_PlayerController::UpdateCameraMovement(float DeltaTime)
{
	float MouseX, MouseY;
	/* Get viewport bounds */
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ScrollBorderRight = ViewportSize.X - PlayerPawn->CameraScrollThreshold;
	ScrollBorderTop = ViewportSize.Y - PlayerPawn->CameraScrollThreshold;
	/* Detect if cursor approach to the edge */
	if (GetMousePosition(MouseX, MouseY) && bIsMovementEnabled)
	{
		if (MouseX <= PlayerPawn->CameraScrollThreshold)
		{
			CameraRightAxisValue -= 1 - (MouseX / PlayerPawn->CameraScrollThreshold);
		}
		else if (MouseX >= ScrollBorderRight)
		{
			CameraRightAxisValue += (MouseX - ScrollBorderRight) / PlayerPawn->CameraScrollThreshold;
		}
		if (MouseY <= PlayerPawn->CameraScrollThreshold)
		{
			CameraForwardAxisValue += 1 - (MouseY / PlayerPawn->CameraScrollThreshold);
		}
		else if (MouseY >= ScrollBorderTop)
		{
			CameraForwardAxisValue -= (MouseY - ScrollBorderTop) / PlayerPawn->CameraScrollThreshold;
		}
	}

	CameraForwardAxisValue = FMath::Clamp(CameraForwardAxisValue, -1.0f, +1.0f);
	CameraRightAxisValue = FMath::Clamp(CameraRightAxisValue, -1.0f, +1.0f);

	FVector Location = PlayerPawn->GetActorLocation();
	Location += FVector::ForwardVector * PlayerPawn->CameraSpeed * PlayerPawn->CameraSpeedMultiplier * CameraForwardAxisValue * DeltaTime;
	Location += FVector::RightVector * PlayerPawn->CameraSpeed * PlayerPawn->CameraSpeedMultiplier * CameraRightAxisValue * DeltaTime;
	/* Enforce camera bounds */
	if (!CameraBoundsVolume || CameraBoundsVolume->EncompassesPoint(Location))
	{
		PlayerPawn->SetActorLocation(Location);
	}
}

void ARTS_PlayerController::UpdateCameraZoom(float DeltaTime)
{
	if (PlayerPawn->CurrentCameraZoom != PlayerPawn->DesiredCameraZoom)
	{
		PlayerPawn->CurrentCameraZoom = FMath::FInterpTo(PlayerPawn->CurrentCameraZoom, PlayerPawn->DesiredCameraZoom, DeltaTime, PlayerPawn->CameraZoomSpeed);
		PlayerPawn->SpringArm->TargetArmLength = PlayerPawn->CurrentCameraZoom;
	}
}

void ARTS_PlayerController::MoveForward(float Value)
{
	if (bIsMovementEnabled)
	{
		CameraForwardAxisValue = Value;
	}
}

void ARTS_PlayerController::MoveRight(float Value)
{
	if (bIsMovementEnabled)
	{
		CameraRightAxisValue = Value;
	}
}

void ARTS_PlayerController::ZoomCamera(float Value)
{
	PlayerPawn->DesiredCameraZoom = FMath::Clamp(PlayerPawn->DesiredCameraZoom + Value, PlayerPawn->MinCameraDistance, PlayerPawn->MaxCameraDistance);
}

void ARTS_PlayerController::StartSelectActors()
{
	StartPoint = GetCurrentMousePosition();
	bCreatingSelectionFrame = true;
}

void ARTS_PlayerController::FinishSelectActors()
{
	bCreatingSelectionFrame = false;
}

void ARTS_PlayerController::HandleOrder()
{
	FHitResult HitResult;
	UCollisionProfile* CollisionProfile = UCollisionProfile::Get();
	if (GetHitResultUnderCursorByChannel(CollisionProfile->ConvertToTraceType(ECC_Visibility), true, HitResult) && SelectedActors.Num() > 0)
	{
		for (AActor* SelectedActor : SelectedActors)
		{
			auto MovementComponent = SelectedActor->FindComponentByClass<UShipMovementComponent>();
			if (MovementComponent)
			{
				MovementComponent->CommandMoveTo(HitResult.Location);
			}
		}
	}
}

FVector2D ARTS_PlayerController::GetCurrentMousePosition()
{
	float MouseX, MouseY;
	if (GetMousePosition(MouseX, MouseY))
	{
		return FVector2D(MouseX, MouseY);
	}
	return FVector2D();
}