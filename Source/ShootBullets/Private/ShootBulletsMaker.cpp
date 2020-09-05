// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootBulletsMaker.h"
#include "GameFramework/Actor.h"
#include "ShootBulletsGameInstance.h"

#include "BulletActorNormal.h"
#include "BulletActorCharge.h"
#include "BulletActorSplit.h"
#include "BulletActorReflect.h"

UShootBulletsMaker::UShootBulletsMaker()
{
	ResetCount();
}

UShootBulletsMaker::~UShootBulletsMaker()
{
}

void UShootBulletsMaker::ResetCount()
{
	NormalCnt = 0;
	ChargeCnt = 0;
	SplitCnt = 0;
	ReflectCnt = 0;
}

void UShootBulletsMaker::AddBulletCount(EBulletType Type)
{
	switch (Type)
	{
	case UShootBulletsMaker::EBulletType::BT_NORMAL:	++NormalCnt;	break;
	case UShootBulletsMaker::EBulletType::BT_CHARGE:	++ChargeCnt;	break;
	case UShootBulletsMaker::EBulletType::BT_SPLIT:		++SplitCnt;		break;
	case UShootBulletsMaker::EBulletType::BT_REFLECT:	++ReflectCnt;	break;
	default:
		break;
	}

	if (Type < UShootBulletsMaker::EBulletType::BT_MAX)
		OnBulletCountAdded.ExecuteIfBound();
}

int UShootBulletsMaker::GetBulletCount(EBulletType Type)
{
	switch (Type)
	{
	case UShootBulletsMaker::EBulletType::BT_NORMAL:	return NormalCnt;
	case UShootBulletsMaker::EBulletType::BT_CHARGE:	return ChargeCnt;
	case UShootBulletsMaker::EBulletType::BT_SPLIT:		return SplitCnt;
	case UShootBulletsMaker::EBulletType::BT_REFLECT:	return ReflectCnt;
	default:
		return 0;
	}
}

// Bullet Make Helper
void UShootBulletsMaker::MakeBullets(AActor* Actor, EBulletType Type, const float& BulletDirOffset, const float& BulletOffsetZ, const FRotator& AdditionRot, AActor* Owner)
{
	if (nullptr == Actor)
		return;

	auto World = Actor->GetWorld();
	if (nullptr == World)
		return;

	auto CharLocation = Actor->GetActorLocation();
	auto CharRotaion = Actor->GetActorRotation();

	FVector SpawnPos = CharLocation;
	FRotator SpawnRot = CharRotaion + AdditionRot;
	FVector SpawnDirection = FRotationMatrix(SpawnRot).GetUnitAxis(EAxis::X);
	
	SpawnPos += SpawnDirection * BulletDirOffset;
	SpawnPos.Z += BulletOffsetZ;

	FActorSpawnParameters Params;
	Params.Owner = (Owner == nullptr) ? Actor : Owner;
	
	switch (Type)
	{
	case UShootBulletsMaker::EBulletType::BT_NORMAL:
	{
		World->SpawnActor<ABulletActorNormal>(SpawnPos, SpawnRot, Params);
	} break;

	case UShootBulletsMaker::EBulletType::BT_CHARGE:
	{
		World->SpawnActor<ABulletActorCharge>(SpawnPos, SpawnRot, Params);
	} break;

	case UShootBulletsMaker::EBulletType::BT_SPLIT:
	{
		World->SpawnActor<ABulletActorSplit>(SpawnPos, SpawnRot, Params);
	} break;

	case UShootBulletsMaker::EBulletType::BT_REFLECT:
	{
		World->SpawnActor<ABulletActorReflect>(SpawnPos, SpawnRot, Params);
	} break;

	case UShootBulletsMaker::EBulletType::BT_SUB_NORMAL:
	{
		FVector CharDirection = FRotationMatrix(CharRotaion).GetUnitAxis(EAxis::X);
		SpawnPos -= CharDirection * ABulletActorNormal::ArrowHalfLength;
		World->SpawnActor<ABulletActorNormal>(SpawnPos, SpawnRot, Params);
	} break;

	default:
		break;
	}

	auto GameInstance = Cast<UShootBulletsGameInstance>(World->GetGameInstance());
	if (nullptr == GameInstance)
		return;

	auto BulletInfo = GameInstance->GetBulletInfo();
	if (nullptr == BulletInfo)
		return;
	
	BulletInfo->AddBulletCount(Type);
}