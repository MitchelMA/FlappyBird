#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreCounter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScoreIncreasedDelegate, int64, TotalAmount, int64, Diff);

class UTextRenderComponent;

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API AScoreCounter : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UTextRenderComponent> ScoreText;

	UPROPERTY(Category=Settings, EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	int32 ScoreMinimalDisplaylength = 3;
	
	UPROPERTY(BlueprintGetter=GetScore)
	int64 Score = 0;
	
public:	
	// Sets default values for this actor's properties
	AScoreCounter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void IncreaseScore(int64 Amount = 1);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int64 GetScore() const { return Score; }

	UFUNCTION()
	void SetDisplayScore(int64 DisplayScore) noexcept;

	UPROPERTY(Category=Events, BlueprintAssignable)
	FScoreIncreasedDelegate OnScoreIncreasedDelegate;
};
