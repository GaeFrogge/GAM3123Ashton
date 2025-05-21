// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Resource_M.generated.h"



UCLASS()
class GAM312_ASHTON_API AResource_M : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource_M();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//initializing FString for resource name, defaulting to wood
	UPROPERTY(EditAnywhere)
		FString resourceName = "Wood";

	//Initializing amount of resource given for collecting resource
	UPROPERTY(EditAnywhere)
		int resourceAmount = 5;

	//total amount of resources in resource until depleted
	UPROPERTY(EditAnywhere)
		int totalResource = 100;

	//sets up text rendering
	UPROPERTY()
		FText tempText;
	
	//text render component
	UPROPERTY(EditAnywhere)
		UTextRenderComponent* ResourceNameTxt;

	//mesh component
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

};
