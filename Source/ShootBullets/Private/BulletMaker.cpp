// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletMaker.h"
#include "ShootBulletsCharacter.h"
#include "BulletActorNormal.h"
#include "BulletActorCharge.h"
#include "BulletActorSplit.h"
#include "BulletActorReflect.h"

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

// Bullet Make Helper
void BulletMaker::MakeBullets(AShootBulletsCharacter* Character, eBulletType Type)
{
	if (nullptr == Character)
		return;

	auto World = Character->GetWorld();
	if (nullptr == World)
		return;
	
	const float BulletPosGap = 20.0f;
	const float BulletPosZ = 50.0f;

	auto CharLocation = Character->GetActorLocation();
	auto CharRotaion = Character->GetActorRotation();

	FVector SpawnPos = CharLocation;

	/* 
	// Only Two Dirrection
	FVector Direction = FVector(1.0f, 0.0f, 0.0f);
	FRotator SpawnRot = FRotator(0.0f, 90.0f, 0.0f);
	
	// Only Two Dir;
	if (CharRotaion.Yaw < 0.0f)
	{
		Direction = FVector(-1.0f, 0.0f, 0.0f);
		SpawnRot = FRotator(0.0f, -90.0f, 0.0f);
	}
	*/

	// All Direction
	FVector Direction = FRotationMatrix(CharRotaion).GetUnitAxis(EAxis::X);
	FRotator SpawnRot = CharRotaion;

	Direction *= BulletPosGap;
	SpawnPos += Direction;
	SpawnPos.Z += BulletPosZ;

	switch (Type)
	{
	case BulletMaker::eBulletType::BT_NORMAL:
		UE_LOG(LogTemp, Warning, TEXT("BT_NORMAL"));
		World->SpawnActor<ABulletActorNormal>(SpawnPos, SpawnRot);
		break;
	case BulletMaker::eBulletType::BT_CHARGE:
		UE_LOG(LogTemp, Warning, TEXT("BT_CHARGE"));
		World->SpawnActor<ABulletActorCharge>(SpawnPos, SpawnRot);
		break;
	case BulletMaker::eBulletType::BT_SPLIT:
		UE_LOG(LogTemp, Warning, TEXT("BT_SPLIT"));
		World->SpawnActor<ABulletActorSplit>(SpawnPos, SpawnRot);
		break;
	case BulletMaker::eBulletType::BT_REFLECT:
		UE_LOG(LogTemp, Warning, TEXT("BT_REFLECT"));
		World->SpawnActor<ABulletActorReflect>(SpawnPos, SpawnRot);
		break;
	default:
		break;
	}
}