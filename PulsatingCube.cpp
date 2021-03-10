// George Griffiths, University of Liverpool

#include "PulsatingCube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"


// Sets default values
APulsatingCube::APulsatingCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));

}

// Called when the game starts or when spawned
void APulsatingCube::BeginPlay()
{
	Super::BeginPlay();
    
    // Defining variables for cube key actor pulsation effect.
    time = FMath::FRandRange(0,100);
    Increment = 0.05f;
    RandomXVector = FMath::RandRange(0.f,5.f);
    RandomYVector = FMath::RandRange(0.f,5.f);
}

// Called every frame
void APulsatingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    Pulsate();
    CubeCollision();
}

// Giving the cube key actors a pulsating visual effect.
void APulsatingCube::Pulsate()
{
    FVector PulsateScale = FVector(1.0f, 1.0f, 1.0f);
    time = time + Increment;
    
    PulsateScale = FVector(FMath::Cos(time) + 2.0f);
    PulsateScale *= 0.15;
    
    if (StaticMesh) // Null pointer check.
    {
        StaticMesh->SetWorldScale3D(PulsateScale);
    }
    
}

// Ensure cube key actors bounce off of other actors.
void APulsatingCube::CubeCollision()
{
    FVector CollisionSpeed = FVector(RandomXVector, RandomYVector, 0.0f);
    CollisionSpeed *= 1;
    
    FHitResult HitResult;
    
    if (StaticMesh) // Null pointer check.
    {
        StaticMesh->AddLocalOffset(CollisionSpeed, true, &HitResult);
        
        if (HitResult.bBlockingHit)
        {
            FVector2D Velocity2D = FVector2D(RandomXVector, RandomYVector);
            FVector2D WallNormal = FVector2D(HitResult.Normal).GetSafeNormal();
            
            float Dot = WallNormal | Velocity2D;
            Velocity2D = Velocity2D + WallNormal * (-2.0f * Dot);
            
            RandomXVector = Velocity2D.X;
            RandomYVector = Velocity2D.Y;}
    }
}
