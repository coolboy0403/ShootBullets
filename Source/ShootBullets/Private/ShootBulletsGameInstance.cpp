// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootBulletsGameInstance.h"
#include "ShootBulletsMaker.h"

UShootBulletsGameInstance::UShootBulletsGameInstance()
{
	ShootBulletsInfo = CreateDefaultSubobject<UShootBulletsMaker>(TEXT("BulletsInfo"));
}

void UShootBulletsGameInstance::Init()
{
	Super::Init();
}

UShootBulletsMaker* UShootBulletsGameInstance::GetBulletInfo() const
{
	return ShootBulletsInfo;
}