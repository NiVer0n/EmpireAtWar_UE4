#include "ShipMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EmpireAtWar_UE4/AI/ShipAIController.h"

void UShipMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
	Owner = GetOwner();
}

void UShipMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Owner) return;
}

void UShipMovementComponent::CommandMoveTo(const FVector& Location)
{
	TargetLocation = Location;
	/* Initiate rotate to target */
	GetWorld()->GetTimerManager().SetTimer(ShipRotationTimer, this, &UShipMovementComponent::SetShipRotation, 0.01f, true);
}

void UShipMovementComponent::SetShipRotation()
{
	AShipAIController* AIController = Cast<AShipAIController>(Owner->GetInstigator()->GetController());
	if (AIController)
	{
		float YawRotation = UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), TargetLocation).Yaw;
		FRotator TargetRotation = FRotator(Owner->GetActorRotation().Pitch, YawRotation, Owner->GetActorRotation().Roll);
		//UE_LOG(LogTemp, Log, TEXT("Yaw Rot: %f"), YawRotation);
		//UE_LOG(LogTemp, Log, TEXT("Target Rotation: %f:%f:%f"), TargetRotation.Roll, TargetRotation.Pitch, TargetRotation.Yaw);
		FRotator InterpolatedRotation = FMath::RInterpTo(Owner->GetActorRotation(), TargetRotation, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), TurnSpeed);
		//UE_LOG(LogTemp, Log, TEXT("Interp Rot: %f:%f:%f"), InterpolatedRotation.Roll, InterpolatedRotation.Pitch, InterpolatedRotation.Yaw);
		Owner->SetActorRotation(InterpolatedRotation);

		FVector FocalPoint = FVector(Owner->GetActorLocation() + Owner->GetActorForwardVector() * 100.0f);
		FVector NextMovePoint = FVector(Owner->GetActorLocation() + Owner->GetActorForwardVector() * 50.0f);
			
		AIController->SetFocalPoint(FocalPoint, EAIFocusPriority::Default);
		AIController->ExecuteMoveToLocation(NextMovePoint);

		if (Owner->GetActorLocation().Equals(TargetLocation, 200.0f))
		{
			GetWorld()->GetTimerManager().ClearTimer(ShipRotationTimer);
		}
	}
}