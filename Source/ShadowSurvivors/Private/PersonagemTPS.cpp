// Fill out your copyright notice in the Description page of Project Settings.

#include "PersonagemTPS.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Arma.h"
#include "Engine/EngineTypes.h"

// Sets default values
APersonagemTPS::APersonagemTPS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArmCamera"));

	SpringArmCamera->TargetArmLength = 200.f;
	SpringArmCamera->bUsePawnControlRotation = true;
	SpringArmCamera->AddRelativeLocation(FVector(0.f, 40.f, 50.f));
	SpringArmCamera->bEnableCameraLag = true;
	SpringArmCamera->CameraLagSpeed = 40.f;
	SpringArmCamera->SetupAttachment(RootComponent);

	CameraPersonagem = CreateDefaultSubobject<UCameraComponent>(FName("CameraPersonagem"), false);

	CameraPersonagem->SetupAttachment(SpringArmCamera);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	AirControl = 0.05f;
	JumpZVelocity = 425.f;
	GravityScale = 1.5f;
	CrouchedHalfHeight = 60.f;
}

// Called when the game starts or when spawned
void APersonagemTPS::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->AirControl = AirControl;
	GetCharacterMovement()->JumpZVelocity = JumpZVelocity;
	GetCharacterMovement()->GravityScale = GravityScale;
	GetCharacterMovement()->CrouchedHalfHeight = CrouchedHalfHeight;

	FActorSpawnParameters Parametros;
	Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AArma* ArmaPlayer = GetWorld()->SpawnActor<AArma>(BP_ArmaTipoRifle, FTransform(), Parametros);

	ArmaPlayer->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SocketDaArma"));
	
}

void APersonagemTPS::MoveUpDown(float Value)
{
	//Realiza a Movimentação para Frente e Tras;
	AddMovementInput(GetActorForwardVector() * Value);
}

void APersonagemTPS::MoveLeftRight(float Value)
{
	//Realiza a Movimentação para Esquerda e Direita;
	AddMovementInput(GetActorRightVector() * Value);
}

void APersonagemTPS::CrouchTPS()
{
	Crouch();
}

void APersonagemTPS::UnCrouchTPS()
{
	UnCrouch();
}

void APersonagemTPS::StartJump()
{
	bJumpOn = true;
}

void APersonagemTPS::StopJump()
{
	bJumpOn = false;
}

// Called every frame
void APersonagemTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APersonagemTPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Atribui a chamada dos metodos de movimentação para serem
	//assionados quando houver o click do teclado.
	PlayerInputComponent->BindAxis("MoveUpDown",this,&APersonagemTPS::MoveUpDown);
	PlayerInputComponent->BindAxis("MoveLeftRight",this,&APersonagemTPS::MoveLeftRight);
	PlayerInputComponent->BindAxis("LookUpDown", this, &APersonagemTPS::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRightLeft", this, &APersonagemTPS::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &APersonagemTPS::CrouchTPS);
	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Released, this, &APersonagemTPS::UnCrouchTPS);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APersonagemTPS::StartJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &APersonagemTPS::StopJump);
}

