// Copyright Epic Games, Inc. All Rights Reserved.


#include "SoulExchangeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "FPCharacter.h"
#include "GameFramework/Actor.h"

void ASoulExchangeGameModeBase::SetSoulSpeed(float Speed)
{
	SoulSpeed = Speed;
}

FTransform ASoulExchangeGameModeBase::QuatRotate_AroundOtherTransform(const FTransform& TargetT, const FTransform& TPoint, const FQuat& AddRotation)
{
	FTransform T2 = TPoint;
	T2.ConcatenateRotation(AddRotation);
	FTransform T = TargetT * TPoint.Inverse() * T2;
	T.NormalizeRotation();
	return T;
}

FTransform ASoulExchangeGameModeBase::Rotate_AroundOtherTransform(const FTransform& TargetT, const FTransform& TPoint, const FRotator& AddRotation)
{
	return QuatRotate_AroundOtherTransform(TargetT, TPoint, FQuat(AddRotation));
}

void ASoulExchangeGameModeBase::ChangeCharacter(ACharacter* Character)
{
	if (!Character)
	{
		return;
	}
	OnChangeCharacterPressed.Broadcast(Character);
}

void ASoulExchangeGameModeBase::JumpToSoulPrivate()
{

	MainFPCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!MainFPCharacter)
	{
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AFPSoulCharacter* Soul = GetWorld()->SpawnActor<AFPSoulCharacter>(Cast<AFPCharacter>(MainFPCharacter)->Camera->GetComponentLocation(), FRotator(0, Cast<AFPCharacter>(MainFPCharacter)->Camera->GetComponentRotation().Yaw, Cast<AFPCharacter>(MainFPCharacter)->Camera->GetComponentRotation().Roll), SpawnParameters);
	Soul->SetSpeed(SoulSpeed);
	ChangeCharacter(Soul);
	StartSoulLife();
}

void ASoulExchangeGameModeBase::StartSpawnTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(SoulSpawnTimer);
	GetWorld()->GetTimerManager().SetTimer(SoulSpawnTimer, this, &ASoulExchangeGameModeBase::JumpToSoulPrivate, SoulSpawnTime, false);
}

void ASoulExchangeGameModeBase::StopSpawnTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(SoulSpawnTimer);
}

void ASoulExchangeGameModeBase::StartSoulLife()
{
	GetWorld()->GetTimerManager().SetTimer(SoulLifeTimer, this, &ASoulExchangeGameModeBase::EndSoulLife, SoulLifeTime, false);
}

void ASoulExchangeGameModeBase::EndSoulLife()
{
	Cast<AFPSoulCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->DeleteLastItem();
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->Destroy();
	ChangeCharacter(MainFPCharacter);
}

void ASoulExchangeGameModeBase::JumpToSoul()
{
	StartSpawnTimer();
}

void ASoulExchangeGameModeBase::CancelJumpToSoul()
{
	StopSpawnTimer();
}

