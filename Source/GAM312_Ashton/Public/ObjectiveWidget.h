// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAM312_ASHTON_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//Function to update materials objective
	UFUNCTION(BlueprintImplementableEvent)
	void UpdatematOBJ(float matsCollected);

	//Function to update objects built objective
	UFUNCTION(BlueprintImplementableEvent)
	void UpdatebuildOBJ(float objectsBuilt);

	
};
