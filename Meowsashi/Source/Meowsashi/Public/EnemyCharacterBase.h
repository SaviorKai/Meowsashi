// All rights reserved © 2019 Ivan Carl Engelbrecht

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacterBase.generated.h"

class UPawnSensingComponent;


UCLASS()
class MEOWSASHI_API AEnemyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* SensingComponent;                    // NOTE: Remember to always add the "AIModule" to the game.Build.cs file (see Meowsashi.Build.cs), before you use this.

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MovementSpeed = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float AttackRange = 300.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sensing Component
	UFUNCTION()
	void HandleOnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void HandleOnHearNoise(APawn* HeardPawn, const FVector& Location, float Volume);

private:
	void MoveToTarget();

	bool bHasTargetInSight = false;

	AActor* MyTarget = nullptr;
};
