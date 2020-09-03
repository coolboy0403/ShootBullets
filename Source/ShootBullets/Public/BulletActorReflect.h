// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletActorBase.h"
#include "BulletActorReflect.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTBULLETS_API ABulletActorReflect : public ABulletActorBase
{
	GENERATED_BODY()
	
public:
	ABulletActorReflect();
	virtual ~ABulletActorReflect();

protected:
	virtual void OnCollisionDetected(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;
};
