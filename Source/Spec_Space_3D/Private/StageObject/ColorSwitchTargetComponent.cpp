

#include "StageObject/ColorSwitchTargetComponent.h"


UColorSwitchTargetComponent::UColorSwitchTargetComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

}


void UColorSwitchTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UColorSwitchTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


// ‹¤’Ê“ü—ÍŒû
void UColorSwitchTargetComponent::Execute(EProcessTypes Type)
{
	switch (Type)
	{	

	case EProcessTypes::Test:


		case EProcessTypes::Gravity:
			SetGravity();
			break;

		default:
			break;
	}
		

}

// Šeˆ—
void UColorSwitchTargetComponent::SetGravity()
{

}

void UColorSwitchTargetComponent::Test()
{
	AActor* Owner = GetOwner();

	if (Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner Name: %s"), *Owner->GetName());
	}
}