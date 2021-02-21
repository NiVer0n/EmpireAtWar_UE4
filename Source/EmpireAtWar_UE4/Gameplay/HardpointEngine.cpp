#include "HardpointEngine.h"
#include "EmpireAtWar_UE4/Components/ShipMovementComponent.h"

/* Create ship movement component */
void AHardpointEngine::AttachMovementComponent()
{
	auto MovementComponent = NewObject<UShipMovementComponent>(GetOwner(), TEXT("Movement Component"));
	MovementComponent->SetOwner(GetOwner());
	MovementComponent->MaxSpeed = MaxSpeed;
	MovementComponent->Acceleration = Acceleration;
	MovementComponent->Deceleration = Deceleration;
	MovementComponent->TurningBoost = TurningBoost;
	MovementComponent->RegisterComponent();
}