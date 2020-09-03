// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootBulletsCharacter.generated.h"

UCLASS(config=Game)
class AShootBulletsCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void Tick(float DeltaSeconds) override;

	// Fire Default
	void FireDefaultPressed();
	void FireDefaultReleased();

	// Fire Special
	void FireSpecialPressed();
	void FireSpecialReleased();

	void FireBullet(int BulletType);
	void ResetFireStates();

public:
	AShootBulletsCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	const static float ChargeTimeMax;

	UPROPERTY(VisibleAnywhere, Category = Fire)
	bool IsFireDefaultPressed;

	UPROPERTY(VisibleAnywhere, Category = Fire)
	float FireDefaultPressTime = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = Fire)
	bool IsFireSpecialPressed;
};
