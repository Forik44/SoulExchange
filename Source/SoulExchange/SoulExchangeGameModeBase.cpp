// Copyright Epic Games, Inc. All Rights Reserved.


#include "SoulExchangeGameModeBase.h"

void ASoulExchangeGameModeBase::ChangeCharacter(ACharacter* Character)
{
	if (!Character)
	{
		return;
	}
	OnChangeCharacterPressed.Broadcast(Character);
}
