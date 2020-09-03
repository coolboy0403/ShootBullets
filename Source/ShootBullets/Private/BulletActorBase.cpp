// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActorBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABulletActorBase::ABulletActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 3.0f;

	ArrowScale = 1.0f;
	ArrowColor = FLinearColor::Red;

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrowComp"));
	if (nullptr == ArrowComp)
		return;
	
	ArrowComp->SetHiddenInGame(false);
	RootComponent = ArrowComp;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComp"));
	if (nullptr == CapsuleComp)
		return;
	
	CapsuleComp->SetCapsuleSize(5.0f, 40.0f);
	CapsuleComp->SetRelativeLocationAndRotation(FVector(40.0f, 0.0f, 0.0f), FRotator(90.0f, 0.0f, 0.0f));
	CapsuleComp->SetupAttachment(ArrowComp);
	CapsuleComp->BodyInstance.SetCollisionProfileName(TEXT("Bullets"));
	CapsuleComp->OnComponentHit.AddDynamic(this, &ABulletActorBase::OnCollisionDetected);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	if (nullptr == MovementComp)
		return;

	MovementComp->SetUpdatedComponent(ArrowComp);
	MovementComp->InitialSpeed = 100.0f;
	MovementComp->MaxSpeed = 100.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ABulletActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (nullptr == ArrowComp)
		return;

	ArrowComp->SetRelativeScale3D(FVector(ArrowScale, ArrowScale, ArrowScale));
	ArrowComp->SetArrowColor(ArrowColor);

	if (nullptr == MovementComp)
		return;

	FVector Direction = FRotationMatrix(GetActorRotation()).GetUnitAxis(EAxis::X);
	MovementComp->Velocity = Direction * MovementComp->InitialSpeed;
}

void ABulletActorBase::OnCollisionDetected(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, __FUNCTIONW__);
	Destroy();
}