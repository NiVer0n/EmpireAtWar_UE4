#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShipAIController.generated.h"

/**
 * 
 */
UCLASS()
class EMPIREATWAR_UE4_API AShipAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ExecuteMoveToLocation(const FVector& Location);
};