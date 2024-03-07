// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjPool.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API AObjPool : public AActor
{
	GENERATED_BODY()

	TArray<TObjectPtr<AActor>> Pool;

	UPROPERTY(EditAnywhere, Category=Settings)
	UClass* ActorType = nullptr;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
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
	FORCEINLINE AActor* RequestObject(const FVector& SpawnLocation) noexcept;
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool StoreObject(AActor* Object) noexcept;

	static void ActivateObject(AActor* Object) noexcept;
	static void DeactivateObject(AActor* Object) noexcept;
};
