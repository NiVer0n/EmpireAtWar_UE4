#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "RTS_CollisionUtils.generated.h"

/* Utility functions for calculating actor collisions */
UCLASS()
class EMPIREATWAR_UE4_API URTS_CollisionUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Gets the approximated collision size of the specified actor */
	UFUNCTION(BlueprintPure, Category = "Collision Utils")
	static float GetActorCollisionSize(AActor* Actor);

	/* Gets the approximated collision height of the specified actor */
	UFUNCTION(BlueprintPure, Category = "Collision Utils")
	static float GetActorCollisionHeight(AActor* Actor);

	/* Gets the approximated collision size of the specified shape */
	UFUNCTION(BlueprintPure, Category = "Collision Utils")
	static float GetShapeCollisionSize(UShapeComponent* ShapeComponent);

	/* Gets the approximated collision height of the specified shape */
	UFUNCTION(BlueprintPure, Category = "Collision Utils")
	static float GetShapeCollisionHeight(UShapeComponent* ShapeComponent);
};