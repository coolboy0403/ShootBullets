// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ShootBulletsMaker.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(FOnBulletCountAddDelegate);

UCLASS()
class SHOOTBULLETS_API UShootBulletsMaker : public UObject
{
	GENERATED_BODY()
	
public:
	enum class EBulletType : int
	{
		BT_NORMAL = 0,
		BT_CHARGE,
		BT_SPLIT,
		BT_REFLECT,
		BT_MAX,

		BT_SUB_NORMAL,
		BT_SUB_END,
	};
	
public:
	UShootBulletsMaker();
	virtual ~UShootBulletsMaker();

public:
	static void MakeBullets(class AActor* Actor, EBulletType Type, float BulletPosGap = 20.0f, float BulletPosZ = 50.0f, const FRotator& AdditionRot = FRotator::ZeroRotator, class AActor* Owner = nullptr);
	void ResetCount();

	void AddBulletCount(EBulletType Type);
	int GetBulletCount(EBulletType Type);

public:
	FOnBulletCountAddDelegate OnBulletCountAdded;

private:
	UPROPERTY(VisibleAnywhere, Category = BulletInfo)
	int NormalCnt;
	
	UPROPERTY(VisibleAnywhere, Category = BulletInfo)
	int ChargeCnt;

	UPROPERTY(VisibleAnywhere, Category = BulletInfo)
	int SplitCnt;

	UPROPERTY(VisibleAnywhere, Category = BulletInfo)
	int ReflectCnt;
};
