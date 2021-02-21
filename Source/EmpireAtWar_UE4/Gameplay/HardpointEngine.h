#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HardpointEngine.generated.h"

UCLASS()
class EMPIREATWAR_UE4_API AHardpointEngine : public AActor
{
	GENERATED_BODY()
	
public:	

	UFUNCTION(BlueprintCallable)
	void AttachMovementComponent();
	
	/* Movement component settings */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardpointSettings", meta = (ClampMin = 1.0f))
	float MaxSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardpointSettings", meta = (ClampMin = 1.0f))
	float Acceleration = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardpointSettings", meta = (ClampMin = 1.0f))
	float Deceleration = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardpointSettings", meta = (ClampMin = 0.f))
	float TurningBoost = 0.f;
};