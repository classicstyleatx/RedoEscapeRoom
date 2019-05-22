// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDOESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	

private:
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector LineTraceEndDraw = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = Interactions)
		float PlayerReach = 150.0f;
	
	AActor* ActorHit = nullptr;

	//Find assumed attached physics handle component
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	void GetPhysicsHandle();

	//Setup assumed attached input component
	UInputComponent* InputComponent = nullptr;
	void GetInputControl();

	//Return hit  for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//Check if Grab found an actor, and if so, move it.
	void IfGrabbingThenMove();

	void GetLineTraceHit(FHitResult& Hit, FCollisionQueryParams& TraceParams);

	void DrawMyDebugTrace();

	//Figures out the actor hit by the line trace
	void GetLineTraceHitActor(FHitResult& Hit);

	//Finds the current player vector and draws a line the length of PlayerReach
	FVector GetLineTraceEnd();

	//It grabs a physics body collision object transform and rotation
	void Grab();

	//It drops a physics body collision object
	void Release();
};