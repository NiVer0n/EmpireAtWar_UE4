#include "ShipAIController.h"

void AShipAIController::ExecuteMoveToLocation(const FVector& Location)
{
	MoveToLocation(Location, 1.0f, false, true, false);
}