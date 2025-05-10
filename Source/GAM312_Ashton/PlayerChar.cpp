// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initial setup of camera component
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam"));

	//Attach camera to  character mesh, on head
	PlayerCamComp->SetupAttachment(GetMesh(), "head");


	//Enables turning character with camera
	PlayerCamComp->bUsePawnControlRotation = true;


}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Calls moveforward function when W is pressed, reverse axis when S is pressed
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward);

	//Calls moveright function when D is pressed, reverse axis when A is pressed
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight);

	//Moves camera up and down with mouse
	PlayerInputComponent->BindAxis("LookUP", this, &APlayerChar::AddControllerPitchInput);

	//turns camera left and right with mouse
	PlayerInputComponent->BindAxis("Turn", this, &APlayerChar::AddControllerYawInput);

	//Calls jumpevent to start when spacebar is pressed
	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &APlayerChar::StartJump);

	//Calls jumpevent to stop when spacebar is released
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &APlayerChar::StopJump);


}
//Called when player presses W/A
void APlayerChar::MoveForward(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axisValue);
}

//Called when player presses A/D
void APlayerChar::MoveRight(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, axisValue);
}

//Called when player presses Spacebar
void APlayerChar::StartJump()
{
	bPressedJump = true;
}

//Called when player releases Spacebar
void APlayerChar::StopJump()
{
	bPressedJump = false;
}

//Called when player clicks LMB
void APlayerChar::FindObject()
{
}

