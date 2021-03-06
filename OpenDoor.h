// George Griffiths, University of Liverpool

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEORGESMAZE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    
    void OpenDoor();
    void CloseDoor();
    void RotateDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    float InitialYaw;
    float CurrentYaw;
    
    UPROPERTY(EditAnywhere);
    float TargetYaw = -90.f;
    
    UPROPERTY(EditAnywhere);
    ATriggerVolume* PressurePlate;
    
    UPROPERTY(EditAnywhere);
    AActor* ActorThatOpensDoor;

    float DoorLastOpened = 0.f;
    float DoorCloseDelay = 2.f;
    float LerpDuration = 0.01f;
    
};
