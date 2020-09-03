// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletMaker.h"
#include "ShootBulletsCharacter.h"

BulletMaker::BulletMaker()
{
	ResetCount();
}

BulletMaker::~BulletMaker()
{
}

void BulletMaker::ResetCount()
{
	for (int i = 0; i < (int)eBulletType::BT_MAX; ++i)
		arrBulletCounter[i] = 0;
}

void BulletMaker::MakeBullets(AShootBulletsCharacter* Character, eBulletType Type)
{
	if (nullptr == Character)
		return;

	switch (Type)
	{
	case BulletMaker::eBulletType::BT_NORMAL:
		UE_LOG(LogTemp, Warning, TEXT("BT_NORMAL"));
		break;
	case BulletMaker::eBulletType::BT_CHARGE:
		UE_LOG(LogTemp, Warning, TEXT("BT_CHARGE"));
		break;
	case BulletMaker::eBulletType::BT_SPLIT:
		UE_LOG(LogTemp, Warning, TEXT("BT_SPLIT"));
		break;
	case BulletMaker::eBulletType::BT_REFLECT:
		UE_LOG(LogTemp, Warning, TEXT("BT_REFLECT"));
		break;
	default:
		break;
	}

	auto pWorld = Character->GetWorld();
	//pWorld->SpawnActor()
}