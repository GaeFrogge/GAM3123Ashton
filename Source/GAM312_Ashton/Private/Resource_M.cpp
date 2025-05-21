// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_M.h"

// Sets default values
AResource_M::AResource_M()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//sets subobjects
	ResourceNameTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	//sets mesh to root component
	RootComponent = Mesh;

	//attaches text component to mesh component
	ResourceNameTxt->SetupAttachment(Mesh);


}

// Called when the game starts or when spawned
void AResource_M::BeginPlay()
{
	Super::BeginPlay();
	
//sets temptext from resourceName
	tempText = tempText.FromString(resourceName);

//Renders text of resource
	ResourceNameTxt->SetText(tempText);
}

// Called every frame
void AResource_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

