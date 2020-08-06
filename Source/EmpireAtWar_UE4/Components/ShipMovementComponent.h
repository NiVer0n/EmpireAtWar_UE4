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
	// Sets default values for this component's properties
	virtual void InitializeComponent() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Move to desired point on map with calculation of correct and fastest path */
	void CommandMoveTo(const FVector& Location);

private:

	/* Component owner */
	AActor* Owner;

	/* Location to move */
	FVector TargetLocation;

	/* Timer for launch rotation functionality */
	FTimerHandle ShipRotationTimer;

	/* Turn speed of ship */
	UPROPERTY(EditAnywhere, Category = "MovementSettings", meta = (ClampMin = 0.1))
	float TurnSpeed = 1.0f;

	void SetShipRotation();
};