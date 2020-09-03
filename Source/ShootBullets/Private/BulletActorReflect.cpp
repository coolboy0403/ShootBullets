// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActorReflect.h"

ABulletActorReflect::ABulletActorReflect()
{
	ArrowColor = FLinearColor::Blue;
}

ABulletActorReflect::~ABulletActorReflect()
{

}

void ABulletActorReflect::OnCollisionDetected(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, __FUNCTIONW__);
}