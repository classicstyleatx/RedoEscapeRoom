// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REDOESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	float GetTimeInSeconds();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = DoorTransform)
		FVector DoorOpenVector = FVector(-130.04f, -508.01f, 20.0f);
	UPROPERTY(EditAnywhere, Category = DoorTransform)
		FVector DoorCloseVector = FVector(-348.45f, -508.01f, 20.0f);
	UPROPERTY(EditAnywhere, Category = DoorActivation)
		ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere, Category = DoorActivation)
		float CloseDelay = 1.0f;
	UPROPERTY(VisibleAnywhere, Category = DoorActivation)
		float LastOpenTime = 1.0f;
	UPROPERTY(VisibleAnywhere, Category = DoorActivation)
		AActor* ActorThatOpens; //Defining the property for which actor can affect the trigger volume
	AActor* OwnerofDoor = GetOwner();
	
};
