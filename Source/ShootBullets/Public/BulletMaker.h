// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SHOOTBULLETS_API BulletMaker
{
public:
	enum class eBulletType : int
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
	static void MakeBullets(class AActor* Actor, eBulletType Type, float BulletPosGap = 20.0f, float BulletPosZ = 50.0f, const FRotator& AdditionRot = FRotator::ZeroRotator, class AActor* Owner = nullptr);

	BulletMaker();
	~BulletMaker();

	void ResetCount();

private:
	int arrBulletCounter[(int)eBulletType::BT_MAX];
};
