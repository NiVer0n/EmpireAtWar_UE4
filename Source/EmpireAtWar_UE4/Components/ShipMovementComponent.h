#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TimerManager.h"
#include "ShipMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EMPIREATWAR_UE4_API UShipMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:	
	/* Sets component's owner */
	UFUNCTION(BlueprintCallable)
	void SetOwner(AActor* ComponentOwner);

	/* Move to desired point on map with calculation of correct and fastest path */
	void CommandMoveTo(const FVector& Location);

private:
	
	/* Component owner*/
	AActor* Owner;

	/* Location to move */
	FVector TargetLocation;

	/* Timer for launch rotation functionality */
	FTimerHandle ShipRotationTimer;

	void SetShipRotation();
};