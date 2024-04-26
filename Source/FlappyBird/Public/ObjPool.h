#pragma once

#include "CoreMinimal.h"
#include "ObjPool.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API AObjPool : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> Pool;

	UPROPERTY(EditAnywhere, Category=Settings)
	UClass* ActorType = nullptr;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR
	
public:	
	// Sets default values for this actor's properties
	AObjPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	AActor* RequestObject(const FVector& SpawnLocation) noexcept;
	UFUNCTION(BlueprintCallable)
	bool StoreObject(AActor* Object) noexcept;

	static void ActivateObject(AActor* Object) noexcept;
	static void DeactivateObject(AActor* Object) noexcept;
};
