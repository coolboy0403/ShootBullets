// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootingBulletsCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTBULLETS_API UShootingBulletsCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
public:
	void SetupDelegate(class AShootBulletsCharacter* Character);
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* ChargeProgressBar;
};
