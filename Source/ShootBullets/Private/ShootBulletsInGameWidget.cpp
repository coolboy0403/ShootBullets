// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootBulletsInGameWidget.h"
#include "ShootBulletsCharacter.h"
#include "ShootBulletsGameInstance.h"
#include "ShootBulletsMaker.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void UShootBulletsInGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (nullptr != ChargeProgressBar)
	{
		ChargeProgressBar->SetPercent(0.0f);
		ChargeProgressBar->SetVisibility(ESlateVisibility::Hidden);
	}

	if (nullptr != ChargeBorder)
	{
		ChargeBorder->SetBrushColor(FLinearColor::White);
		ChargeBorder->SetVisibility(ESlateVisibility::Hidden);
	}

	if (nullptr != ResetCntButton)
		ResetCntButton->OnClicked.AddDynamic(this, &UShootBulletsInGameWidget::OnResetButtonClicked);

	auto GameInstance = Cast<UShootBulletsGameInstance>(GetGameInstance());
	if (nullptr != GameInstance)
	{
		auto BulletsInfo = GameInstance->GetBulletInfo();
		if (nullptr != BulletsInfo)
		{
			BulletsInfo->OnBulletCountAdded.BindUObject(this, &UShootBulletsInGameWidget::UpdateCountText);
		}
	}

	UpdateCountText();
}

void UShootBulletsInGameWidget::SetupChargeGaugeDelegate(class AShootBulletsCharacter* Character)
{
	if (nullptr == Character || nullptr == ChargeProgressBar || nullptr == ChargeBorder)
		return;

	Character->OnChargeBulletTimeUpdated.AddLambda([&](const float& ChargeTime)
	{
		ChargeProgressBar->SetPercent(ChargeTime / AShootBulletsCharacter::ChargeTimeMax);

		FLinearColor ContentColor = FLinearColor::White;
		if (FMath::IsNearlyEqual(ChargeTime, AShootBulletsCharacter::ChargeTimeMax))
			ContentColor = FLinearColor::Yellow;

		ChargeBorder->SetBrushColor(ContentColor);

		FLinearColor BarColor = FLinearColor::Red;
		if (ChargeTime < 1.0f)
			BarColor = FLinearColor::Yellow;

		ChargeProgressBar->SetFillColorAndOpacity(BarColor);

		ESlateVisibility Visibility = ESlateVisibility::Visible;
		if (FMath::IsNearlyEqual(ChargeTime, 0.0f))
			Visibility = ESlateVisibility::Hidden;

		ChargeBorder->SetVisibility(Visibility);
		ChargeProgressBar->SetVisibility(Visibility);
	});
}

void UShootBulletsInGameWidget::OnResetButtonClicked()
{
	auto GameInstance = Cast<UShootBulletsGameInstance>(GetGameInstance());
	if (nullptr == GameInstance)
		return;

	auto BulletsInfo = GameInstance->GetBulletInfo();
	if (nullptr == BulletsInfo)
		return;

	BulletsInfo->ResetCount();
	UpdateCountText();
}

void UShootBulletsInGameWidget::UpdateCountText()
{
	UTextBlock* ArrTextBlock[(int)UShootBulletsMaker::EBulletType::BT_MAX] =
	{ 
		NormalCntText,
		ChargeCntText,
		SplitCntText,
		ReflectCntText
	};
	
	FString ArrStrings[(int)UShootBulletsMaker::EBulletType::BT_MAX] =
	{
		FString(TEXT("Normal : ")),
		FString(TEXT("Charge : ")),
		FString(TEXT("Split : ")),
		FString(TEXT("Reflect : "))
	};

	auto UpdateEachText = [&](UShootBulletsMaker::EBulletType Type)
	{
		auto TextBlock = ArrTextBlock[(int)Type];
		if (nullptr == TextBlock)
			return;

		int Cnt = 0;
		auto GameInstance = Cast<UShootBulletsGameInstance>(GetGameInstance());
		if (nullptr != GameInstance)
		{
			auto BulletsInfo = GameInstance->GetBulletInfo();
			if (nullptr != BulletsInfo)
			{
				Cnt = BulletsInfo->GetBulletCount(Type);
			}
		}

		FString Temp = ArrStrings[(int)Type] + FString::FromInt(Cnt);
		TextBlock->SetText(FText::FromString(Temp));
	};

	for (int i = 0; i < (int)UShootBulletsMaker::EBulletType::BT_MAX; ++i)
	{
		UpdateEachText((UShootBulletsMaker::EBulletType)i);
	}
}