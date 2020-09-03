// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletActorBase.h"
#include "BulletActorNormal.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTBULLETS_API ABulletActorNormal : public ABulletActorBase
{
	GENERATED_BODY()
	
public:
	ABulletActorNormal();
	virtual ~ABulletActorNormal();
};
