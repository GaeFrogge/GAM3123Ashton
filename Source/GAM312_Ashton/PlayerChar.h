//Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Resource_M.h"
#include "Kismet/GameplayStatics.h"
#include "BuildingPart.h"
#include "PlayerWidget.h"
#include "ObjectiveWidget.h"
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

	//initialize health variable as float
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health = 100.0f;

	//initialize hunger variable as float
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Hunger = 100.0f;

	//initialize stamina variable as float
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina = 100.0f;

	//initialize wood variable as int
	UPROPERTY(EditAnywhere, Category = "Resources")
	int Wood;

	//initialize stone variable as int
	UPROPERTY(EditAnywhere, Category = "Resources")
	int Stone;

	//initialize berry variable as int
	UPROPERTY(EditAnywhere, Category = "Resources")
	int Berry;

	//initialize resources integer array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TArray<int> ResourcesArray;

	//initialize FString array for resource names
	UPROPERTY(EditAnywhere, Category = "Resources")
	TArray<FString> ResourcesNameArray;

	//initialize hitDecal
	UPROPERTY(EditAnywhere, Category = "HitMarker")
	UMaterialInterface* hitDecal;

	//store building info
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Supplies")
	TArray<int> BuildingArray;

	//is player crafting
	UPROPERTY()
	bool isBuilding;

	//select children of building placement
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ABuildingPart> BuildPartClass;

	//spawned object
	UPROPERTY()
	ABuildingPart* spawnedPart;

	//variable playerui
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerWidget* playerUI;

	//Variable obj widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObjectiveWidget* objWidget;

	//Variable objects built
	UPROPERTY()
	float objectsBuilt;

	//variable materials collected
	UPROPERTY()
	float matsCollected;

	//initialize function to change health
	UFUNCTION(BlueprintCallable)
	void SetHealth(float amount);

	//initialize function to change hunger
	UFUNCTION(BlueprintCallable)
	void SetHunger(float amount);

	//initialize function to change stamina
	UFUNCTION(BlueprintCallable)
	void SetStamina(float amount);

	//initialize function to decrease stats
	UFUNCTION()
	void DecreaseStats();

	//give materials
	UFUNCTION()
	void GiveResource(float amount, FString resourceType);

	//determine which object is being built
	UFUNCTION(BlueprintCallable)
	void UpdateResources(float woodAmount, float stoneAmount, FString buildingObject);

	//spawns building mat
	UFUNCTION(BlueprintCallable)
	void SpawnBuilding(int buildingID, bool& isSuccess);

	//rotates build
	UFUNCTION()
	void RotateBuilding();

};
