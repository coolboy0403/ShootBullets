// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletActorBase.h"
#include "BulletActorSplit.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTBULLETS_API ABulletActorSplit : public ABulletActorBase
{
	GENERATED_BODY()
	
public:
	ABulletActorSplit();
	virtual ~ABulletActorSplit();
	
protected:
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	virtual void OnCollisionDetected(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;
private:
	bool IsCollisionDetected;

	class UArrowComponent* PositiveArrowComp;
	class UArrowComponent* NegativeArrowComp;
};
