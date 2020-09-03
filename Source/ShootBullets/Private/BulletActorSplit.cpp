// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActorSplit.h"
#include "Components/ArrowComponent.h"
#include "BulletMaker.h"

ABulletActorSplit::ABulletActorSplit()
	: IsCollisionDetected(false)
{
	PositiveArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("PositiveArrow"));
	if (nullptr != PositiveArrowComp)
	{
		PositiveArrowComp->SetupAttachment(ArrowComp);
		PositiveArrowComp->SetHiddenInGame(false);
		PositiveArrowComp->SetRelativeRotation(FRotator(0.0f, 45.0f, 0.0f));
	}

	NegativeArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("NegativeArrow"));
	if (nullptr != NegativeArrowComp)
	{
		NegativeArrowComp->SetupAttachment(ArrowComp);
		NegativeArrowComp->SetHiddenInGame(false);
		NegativeArrowComp->SetRelativeRotation(FRotator(0.0f, -45.0f, 0.0f));
	}
}

ABulletActorSplit::~ABulletActorSplit()
{

}

void ABulletActorSplit::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (false == IsCollisionDetected)
	{
		auto MakeSubBullet = [&](UArrowComponent* Arrow)
		{
			if (nullptr == Arrow)
				return;

			auto ActorRotation = Arrow->GetRelativeRotation();
			BulletMaker::MakeBullets(this, BulletMaker::eBulletType::BT_SUB_NORMAL, 0.0f, 0.0f, ActorRotation);
		};

		MakeSubBullet(PositiveArrowComp);
		MakeSubBullet(NegativeArrowComp);
	}
}

void ABulletActorSplit::OnCollisionDetected(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, __FUNCTIONW__);
	IsCollisionDetected = true;
	
	Super::OnCollisionDetected(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
}