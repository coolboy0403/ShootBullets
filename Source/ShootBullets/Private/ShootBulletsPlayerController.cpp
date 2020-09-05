// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootBulletsPlayerController.h"
#include "ShootBulletsInGameWidget.h"
#include "ShootBulletsCharacter.h"

AShootBulletsPlayerController::AShootBulletsPlayerController(const FObjectInitializer& ObjectInitializer)
	:APlayerController(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UShootBulletsInGameWidget> ConstructWidgetClass(TEXT("/Game/UI/InGameUI"));
	if (ConstructWidgetClass.Succeeded())
	{
		InGameWidgetClass = ConstructWidgetClass.Class;
	}
}

void AShootBulletsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);

	bShowMouseCursor = true;

	if (nullptr == InGameWidgetClass)
		return;

	if (nullptr == InGameWidgetInstance)
	{
		InGameWidgetInstance = CreateWidget<UShootBulletsInGameWidget>(this, InGameWidgetClass);
		InGameWidgetInstance->AddToViewport();

		auto CurrCharacter = Cast<AShootBulletsCharacter>(GetCharacter());
		InGameWidgetInstance->SetupChargeGaugeDelegate(CurrCharacter);
	}
}