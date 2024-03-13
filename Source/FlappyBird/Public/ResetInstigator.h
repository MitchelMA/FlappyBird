#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResetInstigator.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogResetInstigator, Log, All);

UCLASS(BlueprintType, Blueprintable)
class FLAPPYBIRD_API AResetInstigator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResetInstigator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void ResetAll() const;
};
