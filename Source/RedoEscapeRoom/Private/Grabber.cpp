// No Copyright

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}
//
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	//
	GetPhysicsHandle();
	GetInputControl();
	
	//UE_LOG(LogTemp, Warning, TEXT("Reporting for duty"))
	
}

///Look for attached physics handle
void UGrabber::GetPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{	
		UE_LOG(LogTemp, Error, TEXT("Look out, we didn't find a physics handle on %s"), *GetOwner()->GetName())
	}
}

void UGrabber::GetInputControl()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) 
	{
			InputComponent->BindAction("ActGrab", IE_Pressed, this, &UGrabber::Grab);
			InputComponent->BindAction("ActGrab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Input Controller on Default Pawn"))
	}
}

void UGrabber::Grab()
{
	///reach out and touch something with a physics body collision channel set
	GetLineTraceEnd();

	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();


	if (ActorHit)
	{
		if (!PhysicsHandle) { return; }
		{
		}
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None, //No Bones Needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation());
	}
}

void UGrabber::Release()
{
	//raycast and grab what's in reach - to be defined
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"))
		if (!PhysicsHandle) { return; }
		PhysicsHandle->ReleaseComponent();
		///TODO Release physics
}

//Get the vector and end of the ray trace
FVector UGrabber::GetLineTraceEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return (FVector(PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * PlayerReach)));
}



//Not currently called anywhere, removable
/*
void UGrabber::DrawMyDebugTrace()
{
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, GetLineTraceEnd(), FColor(255, 0, 0, 50), false, 0.f, 100, 5.0f);
}*/

void UGrabber::GetLineTraceHitActor(FHitResult& Hit)
{
	ActorHit = Hit.GetActor();
	if (ActorHit)
	{

		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorHit->GetName());
	}
}

void UGrabber::IfGrabbingThenMove()
{
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	IfGrabbingThenMove();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//Simple trace to find simple collision ignoring the player
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	FHitResult HitResult; 

	//Raycast and get the first physics body collision channel object
	GetLineTraceHit(HitResult, TraceParams); 

	//Get the Actor name of the actor the raycast hit. Refactor this out before shipping.
	GetLineTraceHitActor(HitResult); 

	return HitResult;
}

void UGrabber::GetLineTraceHit(FHitResult& HitResult, FCollisionQueryParams& TraceParams)
{
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerViewPointLocation,
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
}