// George Griffiths, University of Liverpool

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

    //Defining variables for door actor rotation.
    InitialYaw = GetOwner()->GetActorRotation().Yaw;
    CurrentYaw = InitialYaw;
    TargetYaw += InitialYaw;
    ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Checking for null pointer and door actor trigger collision.
    if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
    {
        OpenDoor();
        DoorLastOpened = GetWorld()->GetTimeSeconds();
    }
    else // Ensuring door always closes after specified time delay.
    {
        if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
        {
            CloseDoor();
        }
    }
}

// Opening the door Actor.
void UOpenDoor::OpenDoor()
{
    CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, LerpDuration);
    RotateDoor();
}

// Closing the door Actor.
// Identical to UOpenDoor::OpenDoor.
// Created for code clarity.
void UOpenDoor::CloseDoor()
{
    CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, LerpDuration);
    RotateDoor();
}

// Rotating the door Actor.
void UOpenDoor::RotateDoor()
{
    FRotator DoorRotation = GetOwner()->GetActorRotation();
    DoorRotation.Yaw = CurrentYaw;
    GetOwner()-> SetActorRotation(DoorRotation);
}
