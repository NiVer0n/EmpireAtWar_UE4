#include "RTS_HUD.h"
#include "EmpireAtWar_UE4/Components/SelectionComponent.h"
#include "RTS_PlayerController.h"

void ARTS_HUD::BeginPlay()
{
	Super::BeginPlay();
	/* Get player controller reference */
	PlayerController = Cast<ARTS_PlayerController>(PlayerOwner);
}

void ARTS_HUD::DrawHUD()
{
	if (PlayerController->bCreatingSelectionFrame)
	{
		DrawSelectionFrame();
	}
}

void ARTS_HUD::DrawSelectionFrame()
{
	/* Update current mouse position and draw rect */
	PlayerController->EndPoint = PlayerController->GetCurrentMousePosition();
	FVector2D SelectionFrameSize = FVector2D(
		PlayerController->EndPoint.X - PlayerController->StartPoint.X,
		PlayerController->EndPoint.Y - PlayerController->StartPoint.Y);
	DrawRect(SelectionFrameColor, PlayerController->StartPoint.X, PlayerController->StartPoint.Y, SelectionFrameSize.X, SelectionFrameSize.Y);
	
	DeselectActors();
	/* Clear array to store updated info */
	ActorsInSelectionRect.Empty();
	GetActorsInSelectionRectangle<AActor>(PlayerController->StartPoint, PlayerController->EndPoint, ActorsInSelectionRect, false, false);
	SelectActors();
}

void ARTS_HUD::DeselectActors()
{
	if (ActorsInSelectionRect.Num() > 0)
	{
		for (auto SelectedActor : ActorsInSelectionRect)
		{
			auto SelectionComponent = SelectedActor->FindComponentByClass<USelectionComponent>();
			if (SelectionComponent)
			{
				SelectionComponent->DeselectActor();
				PlayerController->SelectedActors.Remove(SelectedActor);
			}
		}
	}
}

void ARTS_HUD::SelectActors()
{
	if (ActorsInSelectionRect.Num() > 0)
	{
		for (auto SelectedActor : ActorsInSelectionRect)
		{
			auto SelectionComponent = SelectedActor->FindComponentByClass<USelectionComponent>();
			if (SelectionComponent)
			{
				SelectionComponent->SelectActor();
				PlayerController->SelectedActors.AddUnique(SelectedActor);
			}
		}
	}
}