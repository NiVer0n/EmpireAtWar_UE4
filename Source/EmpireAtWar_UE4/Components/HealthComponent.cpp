#include "HealthComponent.h"
#include "EmpireAtWar_UE4/Components/SelectionComponent.h"

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (!IsValid(Owner))
	{
		return;
	}

	Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	HealthbarWidgetComponent = NewObject<UWidgetComponent>(Owner, TEXT("Healthbar Widget"));
	
	if (!HealthbarWidgetComponent)
	{
		return;
	}

	InitializeHealthWidget();
}

void UHealthComponent::TakeDamage(AActor* DamagedActor,  float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	/* If owner has shields - decrease it, else decrease HP */
	(bHasShields ? CurrentShields : CurrentHealth) -= Damage;

	if (HealthbarWidget)
	{
		HealthbarWidget->UpdateHealth(CurrentHealth, MaxHealth, CurrentShields, MaxShields);
	}

	if (bHasShields && CurrentShields <= 0)
	{
		bHasShields = false;
	}

	if (!bIsDead && CurrentHealth <= 0)
	{
		bIsDead = true;
		DestroyUnit();
	}
}

void UHealthComponent::DestroyUnit()
{
	USelectionComponent* SelectionComponent = Cast<USelectionComponent>(Owner->GetComponentByClass(USelectionComponent::StaticClass()));
	if (SelectionComponent)
	{
		SelectionComponent->DeselectActor();
		SelectionComponent->SetCanBeSelected(false);
		HealthbarWidgetComponent->DestroyComponent(false);
	}
}

void UHealthComponent::InitializeHealthWidget()
{
	CurrentHealth = MaxHealth;
	CurrentShields = MaxShields;

	HealthbarWidgetComponent->RegisterComponent();
	HealthbarWidgetComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	HealthbarWidgetComponent->SetWidgetClass(HealthbarWidgetClass);
	HealthbarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthbarWidgetComponent->SetRelativeLocation(HealthbarOffset);
	HealthbarWidgetComponent->SetDrawSize(HealthbarSize);
	HealthbarWidget = Cast<UHealthbarWidget>(HealthbarWidgetComponent->GetUserWidgetObject());

	if (HealthbarWidget) HealthbarWidget->bOwnerHasShields = bHasShields;
}