// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingBulletsCharacterWidget.h"
#include "Components/ProgressBar.h"
#include "ShootBulletsCharacter.h"

void UShootingBulletsCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ChargeProgressBar->SetPercent(0.5f);
}

void UShootingBulletsCharacterWidget::SetupDelegate(AShootBulletsCharacter* Character)
{
	if (nullptr == Character)
		return;
	
	Character->OnChargeBulletTimeUpdated.BindLambda([&](const float& ChargeTime)
	{
		ChargeProgressBar->SetPercent(ChargeTime / AShootBulletsCharacter::ChargeTimeMax);
	});
}