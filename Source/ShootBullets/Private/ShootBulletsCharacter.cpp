// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootBulletsCharacter.h"
#include "ShootBulletsCharacterWidget.h"
#include "ShootBulletsMaker.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


const float AShootBulletsCharacter::ChargeTimeMax = 3.0f;

AShootBulletsCharacter::AShootBulletsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	if (nullptr == CameraBoom)
		return;

	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	if (nullptr == SideViewCameraComponent)
		return;

	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	ChargeGaugeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BulletChargeWidget"));
	if (nullptr == ChargeGaugeWidget)
		return;

	ChargeGaugeWidget->SetupAttachment(GetMesh());
	ChargeGaugeWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	ChargeGaugeWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UShootBulletsCharacterWidget> ConstructorGaugeWidget(TEXT("/Game/UI/BulletChargeGauge"));
	if (ConstructorGaugeWidget.Succeeded())
	{
		ChargeGaugeWidgetClass = ConstructorGaugeWidget.Class;
	}

	IsFireDefaultPressed = false;
	IsFireSpecialPressed = false;
	FireDefaultPressTime = 0.0f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AShootBulletsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShootBulletsCharacter::MoveRight);

	PlayerInputComponent->BindAction("FireDefault", IE_Pressed, this, &AShootBulletsCharacter::FireDefaultPressed);
	PlayerInputComponent->BindAction("FireDefault", IE_Released, this, &AShootBulletsCharacter::FireDefaultReleased);
	
	PlayerInputComponent->BindAction("FireSpecial", IE_Pressed, this, &AShootBulletsCharacter::FireSpecialPressed);
	PlayerInputComponent->BindAction("FireSpecial", IE_Released, this, &AShootBulletsCharacter::FireSpecialReleased);
}

void AShootBulletsCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AShootBulletsCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsFireDefaultPressed)
	{
		FireDefaultPressTime += DeltaSeconds;
		FireDefaultPressTime = FMath::Min(FireDefaultPressTime, ChargeTimeMax);

		if (OnChargeBulletTimeUpdated.IsBound())
			OnChargeBulletTimeUpdated.Broadcast(FireDefaultPressTime);
	}
}

void AShootBulletsCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr == ChargeGaugeWidgetClass)
		return;

	if (nullptr == ChargeGaugeWidgetInstance)
	{
		ChargeGaugeWidgetInstance = CreateWidget<UShootBulletsCharacterWidget>(GetWorld(), ChargeGaugeWidgetClass);
		ChargeGaugeWidget->SetWidget(ChargeGaugeWidgetInstance);
		ChargeGaugeWidget->SetDrawSize(FVector2D(200.0f, 50.0f));
		ChargeGaugeWidget->SetVisibility(false);

		ChargeGaugeWidgetInstance->SetupDelegate(this);
	}
}

void AShootBulletsCharacter::FireDefaultPressed()
{
	if (IsFireSpecialPressed)
		return;

	IsFireDefaultPressed = true;
	ChargeGaugeWidget->SetVisibility(true);
}

void AShootBulletsCharacter::FireDefaultReleased()
{
	if (false == IsFireDefaultPressed)
		return;
	
	if (FMath::IsNearlyEqual(FireDefaultPressTime, ChargeTimeMax))
	{
		FireBullet((int)UShootBulletsMaker::EBulletType::BT_CHARGE);
	}
	else
	{
		FireBullet((int)UShootBulletsMaker::EBulletType::BT_NORMAL);
	}
}

void AShootBulletsCharacter::FireSpecialPressed()
{
	IsFireSpecialPressed = true;

	if (IsFireDefaultPressed && FireDefaultPressTime < 1.0f)
	{
		FireBullet((int)UShootBulletsMaker::EBulletType::BT_SPLIT);
	}
}

void AShootBulletsCharacter::FireSpecialReleased()
{
	if (false == IsFireSpecialPressed || IsFireDefaultPressed)
		return;

	FireBullet((int)UShootBulletsMaker::EBulletType::BT_REFLECT);
}

void AShootBulletsCharacter::FireBullet(int BulletType)
{
	const float DirOffset = 20.0f;
	const float Zoffset = 50.0f;

	auto MeshLocation = GetMesh()->GetRelativeLocation();
	float BulletOffsetZ = MeshLocation.Z + Zoffset;

	UShootBulletsMaker::MakeBullets(this, (UShootBulletsMaker::EBulletType)BulletType, DirOffset, BulletOffsetZ);
	ResetFireStates();
}

void AShootBulletsCharacter::ResetFireStates()
{
	IsFireDefaultPressed = false;
	IsFireSpecialPressed = false;

	FireDefaultPressTime = 0.0f;

	if (OnChargeBulletTimeUpdated.IsBound())
		OnChargeBulletTimeUpdated.Broadcast(0.0f);

	ChargeGaugeWidget->SetVisibility(false);
}