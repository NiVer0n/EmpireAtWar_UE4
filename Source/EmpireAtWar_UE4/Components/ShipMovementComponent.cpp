#include "ShipMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EmpireAtWar_UE4/AI/ShipAIController.h"

void UShipMovementComponent::SetOwner(AActor* ComponentOwner)
{
	Owner = ComponentOwner;
}

void UShipMovementComponent::CommandMoveTo(const FVector& Location)
{
	TargetLocation = Location;
	/* Initiate rotation to target */
	GetWorld()->GetTimerManager().SetTimer(ShipRotationTimer, this, &UShipMovementComponent::SetShipRotation, 0.01f, true);
}

void UShipMovementComponent::SetShipRotation()
{
	if (Owner)
	{
		AShipAIController* AIController = Cast<AShipAIController>(Owner->GetInstigator()->GetController());
		if (AIController)
		{
			float YawRotation = UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), TargetLocation).Yaw;
			FRotator TargetRotation = FRotator(Owner->GetActorRotation().Pitch, YawRotation, Owner->GetActorRotation().Roll);
			FRotator InterpolatedRotation = FMath::RInterpTo(Owner->GetActorRotation(), TargetRotation, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 1.0f);
			Owner->SetActorRotation(InterpolatedRotation);

			FVector FocalPoint = FVector(Owner->GetActorLocation() + Owner->GetActorForwardVector() * 100.0f);
			FVector NextMovePoint = FVector(Owner->GetActorLocation() + Owner->GetActorForwardVector() * 50.0f);

			AIController->SetFocalPoint(FocalPoint, EAIFocusPriority::Default);
			AIController->ExecuteMoveToLocation(NextMovePoint);

			//UE_LOG(LogTemp, Warning, TEXT("Owner: %s"), *UKismetSystemLibrary::GetDisplayName(Owner));
			//UE_LOG(LogTemp, Warning, TEXT("FocalPoint: %f:%f:%f"), FocalPoint.X, FocalPoint.Y, FocalPoint.Z);
			//UE_LOG(LogTemp, Warning, TEXT("Location: %f"), NextMovePoint.X, NextMovePoint.Y, NextMovePoint.Z);

			if (Owner->GetActorLocation().Equals(TargetLocation, 200.0f))
			{
				GetWorld()->GetTimerManager().ClearTimer(ShipRotationTimer);
			}
		}
	}
}