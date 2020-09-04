// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletMaker.h"
#include "GameFramework/Actor.h"
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
void BulletMaker::MakeBullets(AActor* Actor, eBulletType Type, float BulletPosGap, float BulletPosZ, const FRotator& AdditionRot, AActor* Owner)
{
	if (nullptr == Actor)
		return;

	auto World = Actor->GetWorld();
	if (nullptr == World)
		return;

	auto CharLocation = Actor->GetActorLocation();
	auto CharRotaion = Actor->GetActorRotation();

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
	FRotator CalcRotation = CharRotaion + AdditionRot;
	FVector Direction = FRotationMatrix(CalcRotation).GetUnitAxis(EAxis::X);
	FRotator SpawnRot = CalcRotation;

	Direction *= BulletPosGap;
	SpawnPos += Direction;
	SpawnPos.Z += BulletPosZ;
	
	FActorSpawnParameters Params;
	Params.Owner = (Owner == nullptr) ? Actor : Owner;

	switch (Type)
	{
	case BulletMaker::eBulletType::BT_NORMAL:
		World->SpawnActor<ABulletActorNormal>(SpawnPos, SpawnRot, Params);
		break;
	case BulletMaker::eBulletType::BT_CHARGE:
		World->SpawnActor<ABulletActorCharge>(SpawnPos, SpawnRot, Params);
		break;
	case BulletMaker::eBulletType::BT_SPLIT:
		World->SpawnActor<ABulletActorSplit>(SpawnPos, SpawnRot, Params);
		break;
	case BulletMaker::eBulletType::BT_REFLECT:
		World->SpawnActor<ABulletActorReflect>(SpawnPos, SpawnRot, Params);
		break;
	case BulletMaker::eBulletType::BT_SUB_NORMAL:
		World->SpawnActor<ABulletActorNormal>(SpawnPos, SpawnRot, Params);
		break;
	default:
		break;
	}
}