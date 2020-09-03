// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShootBulletsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTBULLETS_API UShootBulletsGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UShootBulletsGameInstance();
	void Init() override;
	

};
