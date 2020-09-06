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
	const static float ArrowHalfLength;
	
public:	
	// Sets default values for this actor's properties
	ABulletActorBase();

protected:
	virtual void PostInitializeComponents() override;

	virtual void ChangeDirection(const FVector& Direction);

protected:
	float ArrowScale;
	FLinearColor ArrowColor;

	UPROPERTY(VisibleAnywhere, Category = Bullet)
	class UBoxComponent* BoxComp; 

	UPROPERTY(VisibleAnywhere, Category = Bullet)
	class UArrowComponent* ArrowComp;

	UPROPERTY(VisibleAnywhere, Category = Bullet)
	class UProjectileMovementComponent* MovementComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnCollisionDetected();
};
