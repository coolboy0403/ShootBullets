// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActorBase.generated.h"

UCLASS()
class SHOOTBULLETS_API ABulletActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	float ArrowScale;
	FLinearColor ArrowColor;

	UPROPERTY(VisibleAnywhere, Category = Bullet)
	class UCapsuleComponent* CapsuleComp; 

	UPROPERTY(VisibleAnywhere, Category = Bullet)
	class UArrowComponent* ArrowComp;

	UPROPERTY(VisibleAnywhere, Category = Bullet)
	class UProjectileMovementComponent* MovementComp;
};
