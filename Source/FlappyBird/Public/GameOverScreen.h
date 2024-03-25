#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOverScreen.generated.h"

class UWidgetComponent;

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API AGameOverScreen : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UWidgetComponent> Widget;
	
public:	
	// Sets default values for this actor's properties
	AGameOverScreen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Close() const noexcept;
	UFUNCTION(BlueprintCallable)
	void Open() const noexcept;

	UFUNCTION(BlueprintCallable)
	void OnRestartClicked() const noexcept;
	UFUNCTION(BlueprintCallable)
	void OnQuitClicked() const noexcept;
};
