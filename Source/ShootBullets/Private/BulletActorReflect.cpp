// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActorReflect.h"

ABulletActorReflect::ABulletActorReflect()
{
	InitialLifeSpan = 5.0f;
	ArrowColor = FLinearColor::Blue;
}

ABulletActorReflect::~ABulletActorReflect()
{

}

void ABulletActorReflect::OnCollisionDetected()
{
	if (nullptr == MovementComp)
		return;

	FVector Direction = FRotationMatrix(GetActorRotation()).GetUnitAxis(EAxis::X);
	auto ReverseRot = FRotator(0.0f, 180.0f, 0.0f);
	Direction = ReverseRot.RotateVector(Direction);

	ChangeDirection(Direction);
}