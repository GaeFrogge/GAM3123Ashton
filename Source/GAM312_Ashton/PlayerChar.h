// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PlayerChar.generated.h"

UCLASS()
class GAM312_ASHTON_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Sets up UFUNCTION for inputs
	//W or A
	UFUNCTION()
	void MoveForward(float axisValue);

	//A or D
	UFUNCTION()
	void MoveRight(float axisValue);

	//Press Spacebar
	UFUNCTION()
	void StartJump();

	//Release Spacebar
	UFUNCTION()
	void StopJump();


	//LMB click
	UFUNCTION()
	void FindObject();

	//Calls cameracomponent
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamComp;
};
