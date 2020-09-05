// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootBulletsInGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTBULLETS_API UShootBulletsInGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void SetupChargeGaugeDelegate(class AShootBulletsCharacter* Character);
	
protected:
	UFUNCTION()
	void OnResetButtonClicked();

	UFUNCTION()
	void UpdateCountText();

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NormalCntText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ChargeCntText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SplitCntText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ReflectCntText;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResetCntButton;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ChargeProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UBorder* ChargeBorder;
};
