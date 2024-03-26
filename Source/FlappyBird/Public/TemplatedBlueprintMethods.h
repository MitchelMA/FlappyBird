#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"

namespace Templated
{
	template <class T>
	requires std::is_base_of_v<AActor, T>
	FORCEINLINE T*
	GetActorOfClass(
		const UWorld* World
	) noexcept
	{
		return Cast<T>(UGameplayStatics::GetActorOfClass(World, T::StaticClass()));
	}
}
