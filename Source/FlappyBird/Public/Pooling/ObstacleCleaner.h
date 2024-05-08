#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleCleaner.generated.h"

class UBoxComponent;
class AObjPool;

DECLARE_LOG_CATEGORY_EXTERN(LogObstacleCleaner, Log, All);

UCLASS(BlueprintType, Blueprintable)
class FLAPPYBIRD_API AObstacleCleaner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> DefaultSceneRoot = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> CleanTrigger = nullptr;

	UPROPERTY(EditAnywhere, Category=ObstacleHandling)
	TObjectPtr<AObjPool> ObjectPool = nullptr;

	UPROPERTY(EditAnywhere, Category=ObstacleHandling)
	TArray<FName> ObstacleTags;

	UFUNCTION()
	void OnCleanTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		                const FHitResult& SweepResult);
	
public:	
	// Sets default values for this actor's properties
	AObstacleCleaner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
