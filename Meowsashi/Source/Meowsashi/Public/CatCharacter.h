// All rights reserved © 2019 Ivan Carl Engelbrecht

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CatCharacter.generated.h"

class UPawnNoiseEmitterComponent;
class UCapsuleComponent;

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

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	bool bIsAttacking = false;

	UPROPERTY(VisibleAnywhere, Category="Setup")
	UCapsuleComponent* DamageCapsuleCollision;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Setup")
	void DamageSwingOn();
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void DamageSwingOff();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void DealDamage();



};
