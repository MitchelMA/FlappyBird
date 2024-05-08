#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacles/PipeObstacle.h"
#include "ObstacleSpawner.generated.h"

class AObjPool;
class AScoreCounter;
class UBoxComponent;
class ABirdCharacter;

DECLARE_LOG_CATEGORY_EXTERN(LogObstacleSpawner, Log, All);

UCLASS(BlueprintType, Blueprintable)
class FLAPPYBIRD_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<AObjPool> ObjectPool = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<AScoreCounter> ScoreCounter = nullptr;

	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	APipeObstacle* SpawnPipe() noexcept;
};
