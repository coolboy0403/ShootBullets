// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootBulletsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTBULLETS_API AShootBulletsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AShootBulletsPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TSubclassOf<class UShootBulletsInGameWidget> InGameWidgetClass;

	UPROPERTY()
	class UShootBulletsInGameWidget* InGameWidgetInstance;
};
