#include "SelectionComponent.h"
#include "EmpireAtWar_UE4/Utils/RTS_CollisionUtils.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Actor.h"
#include "WorldCollision.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts
void USelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (!IsValid(Owner))
	{
		return;
	}

	float DecalHeight = URTS_CollisionUtils::GetActorCollisionHeight(Owner);
	float DecalRadius = URTS_CollisionUtils::GetActorCollisionSize(Owner);
	// Create selection circle decal
	DecalComponent = NewObject<UDecalComponent>(Owner, TEXT("SelectionCircleDecal"));

	if (!DecalComponent)
	{
		return;
	}
	// Set decal size
	DecalComponent->RegisterComponent();
	DecalComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	DecalComponent->DecalSize = FVector(DecalHeight, DecalRadius, DecalRadius);
	// Rotate decal to face ground
	DecalComponent->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0.0f, -90.0f, 0.0f)));
	// Setup decal material
	SelectionCircleMaterialInstance = UMaterialInstanceDynamic::Create(SelectionCircleMaterial, this);
	DecalComponent->SetDecalMaterial(SelectionCircleMaterialInstance);

	DecalComponent->SetHiddenInGame(true);
}

void USelectionComponent::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);

	if (IsValid(DecalComponent))
	{
		DecalComponent->DestroyComponent();
	}
}

void USelectionComponent::SelectActor()
{
	if (bSelected)
	{
		return;
	}

	if (bCanBeSelected)
	{
		bSelected = true;
		// Update selection circle
		if (IsValid(DecalComponent))
		{
			DecalComponent->SetHiddenInGame(false);
		}
	}
}

void USelectionComponent::DeselectActor()
{
	if (!bSelected)
	{
		return;
	}

	bSelected = false;
	// Update selection circle
	if (IsValid(DecalComponent))
	{
		DecalComponent->SetHiddenInGame(true);
	}
}

bool USelectionComponent::IsSelected() const
{
	return bSelected;
}

void USelectionComponent::SetCanBeSelected(bool CanBeSelected)
{
	bCanBeSelected = CanBeSelected;
}

int32 USelectionComponent::GetSelectionPriority() const
{
	return SelectionPriority;
}

USoundCue* USelectionComponent::GetSelectedSound() const
{
	return SelectedSound;
}