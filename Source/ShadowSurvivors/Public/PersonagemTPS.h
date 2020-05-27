// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PersonagemTPS.generated.h"

UCLASS()
class SHADOWSURVIVORS_API APersonagemTPS : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APersonagemTPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveUpDown(float Value);

	void MoveLeftRight(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraPersonagem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmCamera;

	UPROPERTY(EditAnywhere, Category = "Movimentacao")
	float Velocidade;

	UPROPERTY(EditAnywhere, Category = "Movimentacao")
	float AirControl;

	UPROPERTY(EditAnywhere, Category = "Movimentacao")
	float JumpZVelocity;

	UPROPERTY(EditAnywhere, Category = "Movimentacao")
	float GravityScale;

	UPROPERTY(EditAnywhere, Category = "Movimentacao")
	float CrouchedHalfHeight;

	UPROPERTY(EditAnywhere, Category = "Arma")
	TSubclassOf<class AArma> BP_ArmaTipoRifle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
	bool bJumpOn;

	void CrouchTPS();

	void UnCrouchTPS();

	void StartJump();

	void StopJump();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
