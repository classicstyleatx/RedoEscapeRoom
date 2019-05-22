// No Copyright

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Looks down the inheritance tree and finds the first player controller's pawn to use for trigger volume overlap detection
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//Poll the door every frame
	if (GetTotalMassOfActors() >= TriggerMass)
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}

	
	
	// ...
}

float UOpenDoor::GetTotalMassOfActors()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) 
	{
		UE_LOG(LogTemp, Error, TEXT("Missing an Trigger Volume Assignment on %s"), *GetOwner()->GetName())
		return TotalMass; 
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//Find all the actors and add their mass
	for (const auto* WeightedActors : OverlappingActors)
	{
		TotalMass += WeightedActors->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	

	//Sum their mass to TotalMass

	return TotalMass;
}