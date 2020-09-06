// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootBulletsCharacterWidget.h"
#include "ShootBulletsCharacter.h"
#include "Components/ProgressBar.h"

void UShootBulletsCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UShootBulletsCharacterWidget::SetupDelegate(AShootBulletsCharacter* Character)
{
	if (nullptr == Character || nullptr == ChargeProgressBar)
		return;

	Character->OnChargeBulletTimeUpdated.AddLambda([&](const float& ChargeTime)
	{
		FLinearColor BarColor = FLinearColor::Red;
		if (ChargeTime < 1.0f)
			BarColor = FLinearColor::Yellow;

		ChargeProgressBar->SetFillColorAndOpacity(BarColor);
		ChargeProgressBar->SetPercent(ChargeTime / AShootBulletsCharacter::ChargeTimeMax);
	});
}