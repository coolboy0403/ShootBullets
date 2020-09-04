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

	if (GetOwner() == OtherActor)
		return;
	
	if (nullptr == MovementComp)
		return;

	FVector Direction = FRotationMatrix(GetActorRotation()).GetUnitAxis(EAxis::X);
	auto ReverseRot = FRotator(0.0f, 180.0f, 0.0f);
	Direction = ReverseRot.RotateVector(Direction);
	
	ChangeDirection(Direction);
}