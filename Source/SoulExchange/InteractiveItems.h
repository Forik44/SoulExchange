// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "InteractiveItems.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUseKeyPressedEvent);

UCLASS()
class SOULEXCHANGE_API AInteractiveItems : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveItems();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Interactive")
	bool CanBeInteractive;

	UFUNCTION(BlueprintCallable, Category = "Interactive")
	void SetCustomDeapth(bool value);

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FUseKeyPressedEvent OnUseKeyPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	UStaticMeshComponent* Mesh;



};
