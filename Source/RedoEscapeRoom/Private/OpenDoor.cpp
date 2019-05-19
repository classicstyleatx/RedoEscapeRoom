// No Copyright

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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

	//Looks down the inheritence tree and finds the first player controller's pawn to use for trigger volume overlap detection
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	// ...
	
}

float UOpenDoor::GetTimeInSeconds()
{
	return GetWorld()->GetTimeSeconds();
}

void UOpenDoor::OpenDoor()
{
	OwnerofDoor->SetActorLocation(DoorOpenVector);
}

void UOpenDoor::CloseDoor()
{
	OwnerofDoor->SetActorLocation(DoorCloseVector);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//Poll the door every frame
	//If ActorThatOpens is in Pressure Plate volume, open the door
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastOpenTime = GetTimeInSeconds();
	}
	
	if (LastOpenTime + CloseDelay <= GetTimeInSeconds())
	{
		CloseDoor();
	}

	
	
	// ...
}

