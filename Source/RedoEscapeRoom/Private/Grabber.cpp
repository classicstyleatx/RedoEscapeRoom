// No Copyright

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	//
	GetPhysicsHandle();
	GetInputControl();
	
	//UE_LOG(LogTemp, Warning, TEXT("Reporting for duty"))
	
}
//
///Look for attached physics handle
void UGrabber::GetPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Look out, we didn't find a physics handle on %s"), *GetOwner()->GetName())
	}
}///

void UGrabber::GetInputControl()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Input controller"))
			InputComponent->BindAction("ActGrab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Input Controller on Default Pawn"))
	}
}

void UGrabber::Grab()
{
	//raycast and grab what's in reach - to be defined
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))
}

void UGrabber::GetPlayerViewPointVectors()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
}

//Get the vector and end of the linetrace debug draw
FVector UGrabber::GetLineTraceEnd()
{
	return (FVector(PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * PlayerReach)));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
	GetPlayerViewPointVectors();
	
	GetLineTraceEnd();
	
	//Simple trace to find simple collision ignoring the player
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	
	
	
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
		);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorHit->GetName());
	}
	/*else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hit"));
	}*/
	

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, GetLineTraceEnd(),FColor(255,0,0,50),false,0.f,100,5.0f);
	
}

