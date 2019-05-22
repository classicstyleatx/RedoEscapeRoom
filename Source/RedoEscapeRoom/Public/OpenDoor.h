// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDOESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = DoorTransform)
		FVector DoorOpenVector = FVector(-130.04f, -508.01f, 20.0f);
	UPROPERTY(EditAnywhere, Category = DoorTransform)
		FVector DoorCloseVector = FVector(-348.45f, -508.01f, 20.0f);
	UPROPERTY(EditAnywhere, Category = DoorActivation)
		ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(VisibleAnywhere, Category = DoorActivation)
		AActor* ActorThatOpens; //Defining the property for which actor can affect the trigger volume
	UPROPERTY(EditAnywhere, Category = DoorActivation)
		float TriggerMass = 50.f;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpenRequest;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnCloseRequest;
		
	AActor* OwnerofDoor = GetOwner();
	
	//Mass required to open the plate in KG
	float GetTotalMassOfActors();
};
