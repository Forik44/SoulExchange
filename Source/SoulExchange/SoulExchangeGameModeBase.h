// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SoulExchangeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeCharacterPressed, ACharacter*, Item);
UCLASS()
class SOULEXCHANGE_API ASoulExchangeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	void ChangeCharacter(ACharacter* Character);

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FChangeCharacterPressed OnChangeCharacterPressed;
};
