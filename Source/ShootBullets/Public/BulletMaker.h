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

		BT_MAX
	};

public:
	static void MakeBullets(class AShootBulletsCharacter* Character, eBulletType Type);

	BulletMaker();
	~BulletMaker();

	void ResetCount();

private:
	int arrBulletCounter[(int)eBulletType::BT_MAX];
};
