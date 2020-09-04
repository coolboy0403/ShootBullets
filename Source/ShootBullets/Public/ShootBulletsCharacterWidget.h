// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootBulletsCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTBULLETS_API UShootBulletsCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void SetupDelegate(class AShootBulletsCharacter* Character);

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ChargeProgressBar;
};
