#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSoulCharacter.h"
#include "SoulExchangeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeCharacterPressed, ACharacter*, Item);

UCLASS()
class SOULEXCHANGE_API ASoulExchangeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void JumpToSoul();
	void CancelJumpToSoul();

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FChangeCharacterPressed OnChangeCharacterPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soul")
	float SoulSpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soul")
	float SoulLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soul")
	float SoulSpeed;

	void SetSoulSpeed(float Speed);

	FTransform QuatRotate_AroundOtherTransform(const FTransform& TargetT, const FTransform& TPoint, const FQuat& AddRotation);
	UFUNCTION(BlueprintCallable, Category = "Interactive")
	FTransform Rotate_AroundOtherTransform(const FTransform& TargetT, const FTransform& TPoint, const FRotator& AddRotation);
	
private:
	void ChangeCharacter(ACharacter* Character);

	void JumpToSoulPrivate();

	FTimerHandle SoulSpawnTimer;
	void StartSpawnTimer();
	void StopSpawnTimer();

	FTimerHandle SoulLifeTimer;
	void StartSoulLife();
	void EndSoulLife();

	ACharacter* MainFPCharacter;
};
