// George Griffiths, University of Liverpool

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PulsatingCube.generated.h"

UCLASS()
class GEORGESMAZE_API APulsatingCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APulsatingCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    void Pulsate();
    void CubeCollision();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* StaticMesh;
    
    float time;
    float Increment;
    float RandomXVector;
    float RandomYVector;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
