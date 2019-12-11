// All rights reserved © 2019 Ivan Carl Engelbrecht

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CatCharacter.generated.h"

class UPawnNoiseEmitterComponent;
class UCapsuleComponent;
class USphereComponent;
class UAnimMontage;

UCLASS()
class MEOWSASHI_API ACatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACatCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Amount);
	void RotateCharacter();
	void MoveRight(float Amount);

	// Noise Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPawnNoiseEmitterComponent* NoiseEmitterComp;

	UPROPERTY(VisibleAnywhere, Category="Setup")
	UCapsuleComponent* DamageCapsuleCollision;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USphereComponent* AttackSphere;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float AttackRange = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float AttackCooldownTime = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* MyAttackAnimation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void AttackIfInRange();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlayMyAttackAnimation();
	
	UFUNCTION(BlueprintCallable, Category="Setup") /// Used on Animation Blueprint
	void DamageSwingOn();
	
	UFUNCTION(BlueprintCallable, Category = "Setup") /// Used on Animation Blueprint
	void DamageSwingOff();

	UFUNCTION(BlueprintCallable, Category = "Setup") /// Used on Cat Blueprint
	void DealDamage();

private:
	bool bIsAttacking;

	int32 EnemyiesInRange = 0;

	bool bAttackReady = true;

	FTimerHandle TimerCurrentAttackCooldown;

	void Handle_TimerCurrentAttackCooldown();


};
