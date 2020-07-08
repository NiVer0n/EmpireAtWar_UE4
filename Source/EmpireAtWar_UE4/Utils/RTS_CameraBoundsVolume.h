#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "RTS_CameraBoundsVolume.generated.h"
/*
 * Volume that restricts RTS camera movement.
 * RTS cameras are not allowed to move outside of this volume.
 * There should never be more than one camera bounds volume per level.
 */
UCLASS()
class EMPIREATWAR_UE4_API ARTS_CameraBoundsVolume : public AVolume
{
	GENERATED_BODY()
	
};