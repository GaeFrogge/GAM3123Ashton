// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"
#include "Resource_M.h"


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

	//Sets number of elements in resources array
	BuildingArray.SetNum(3);
	ResourcesArray.SetNum(3);

	//setting names array
	ResourcesNameArray.Add(TEXT("Wood"));
	ResourcesNameArray.Add(TEXT("Stone"));
	ResourcesNameArray.Add(TEXT("Berry"));


}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle StatsTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &APlayerChar::DecreaseStats, 2.0f, true);
	
	//set initial values for objectives to 0
	if (objWidget)
	{
		objWidget->UpdatebuildOBJ(0.0f);
		objWidget->UpdatematOBJ(0.0f);
	}


}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	playerUI->UpdateBars(Health, Hunger, Stamina);

	//if isbuilding is true
	if (isBuilding)
	{
		//if spawned part is a valid object
		if (spawnedPart)
		{
			//set point 400 units from character to spawn building part
			FVector StartLocation = PlayerCamComp->GetComponentLocation();
			FVector Direction = PlayerCamComp->GetForwardVector() * 400.0f;
			FVector EndLocation = StartLocation + Direction;
			spawnedPart->SetActorLocation(EndLocation);
		}
	}

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

	//Calls Interact function when LMB is clicked
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerChar::FindObject);

	//calls rotation function when E is pressed
	PlayerInputComponent->BindAction("RotPart", IE_Pressed, this, &APlayerChar::RotateBuilding);


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
	//initialize hittrace variable
	FHitResult HitResult;
	
	//Start location of hit trace at camera component
	FVector StartLocation = PlayerCamComp->GetComponentLocation();

	//sets direction of hit trace in direction camera is facing 800 units
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f;

	//sets end of hit trace
	FVector EndLocation = StartLocation + Direction;


	FCollisionQueryParams QueryParams;

	//Line trace ignores player
	QueryParams.AddIgnoredActor(this);

	//allows complex collisions
	QueryParams.bTraceComplex = true;

	//allows return of normals of object
	QueryParams.bReturnFaceIndex = true;

	//if isbuilding is not active, do trace
	if (!isBuilding)
	{
		//passing  hitresult, startlocation, endlocation, and queryparams into if statement, setting channel to visibility
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
		{
			AResource_M* HitResource = Cast<AResource_M>(HitResult.GetActor());

			if (Stamina > 5.0f)
			{

				if (HitResource)
				{

					FString hitName = HitResource->resourceName;
					int resourceValue = HitResource->resourceAmount;

					//subtracts resource value from toal when interacted with
					HitResource->totalResource = HitResource->totalResource - resourceValue;

					//Gives resource hit by line trace
					if (HitResource->totalResource > resourceValue)
					{
						GiveResource(resourceValue, hitName);

						//adds mats to objective
						matsCollected = matsCollected + resourceValue;

						objWidget->UpdatematOBJ(matsCollected);

						//debug prints if resource collected
						check(GEngine != nullptr);
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Collected"));

						//getting function from ugameplay lib, setting attributes of decal
						UGameplayStatics::SpawnDecalAtLocation(GetWorld(), hitDecal, FVector(10.0f, 10.0f, 10.0f), HitResult.Location, FRotator(-90, 0, 0), 2.0f);

						//Decrease stamina on collection
						SetStamina(-5.0f);
					}

					//destory resource if nothing left
					else
					{
						HitResource->Destroy();
						check(GEngine != nullptr);
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted"));
					}

				}
			}
		}
	}

	else
	{
		isBuilding = false;

		//updates objects built
		objectsBuilt = objectsBuilt + 1.0f;

		objWidget->UpdatebuildOBJ(objectsBuilt);
	}


}

//Defines SetHealth function 
void APlayerChar::SetHealth(float amount)
{
	if (Health + amount < 100)
	{
		Health = Health + amount;
	}
}

//Defines StHunger function
void APlayerChar::SetHunger(float amount)
{
	if (Hunger + amount < 100)
	{
		Hunger = Hunger + amount;
	}
}

//Defines SetStamina function
void APlayerChar::SetStamina(float amount)
{
	if (Stamina + amount < 100)
	{
		Stamina = Stamina + amount;
	}
}

//Defines DecreaseSats function, when hunger is 0, health begins to decrease
void APlayerChar::DecreaseStats()
{
	if (Hunger > 0)
	{
		SetHunger(-1.0f);
	}

	SetStamina(10.0f);

	if (Hunger <= 0)
	{
		SetHealth(-3.0f);
	}
}

void APlayerChar::GiveResource(float amount, FString resourceType)
{
	//Adds Wood
	if (resourceType == "Wood")
	{
		ResourcesArray[0] = ResourcesArray[0] + amount;
	}

	//Adds Stone
	if (resourceType == "Stone")
	{
		ResourcesArray[1] = ResourcesArray[1] + amount;
	}

	//Adds Berry
	if (resourceType == "Berry")
	{
		ResourcesArray[2] = ResourcesArray[2] + amount;
	}
}

void APlayerChar::UpdateResources(float woodAmount, float stoneAmount, FString buildingObject)
{
	if (woodAmount <= ResourcesArray[0])
	{
		if (stoneAmount <= ResourcesArray[1])
		{
			//subtracting resources used
			ResourcesArray[0] = ResourcesArray[0] - woodAmount;
			ResourcesArray[1] = ResourcesArray[1] - stoneAmount;

			//adds 1 to built object
			if (buildingObject == "Wall")
			{ 
				BuildingArray[0] = BuildingArray[0] + 1;
			}

			if (buildingObject == "Floor")
			{
				BuildingArray[1] = BuildingArray[1] + 1;
			}

			if (buildingObject == "Ceiling")
			{
				BuildingArray[2] = BuildingArray[2] + 1;
			}

		}
	}
}

void APlayerChar::SpawnBuilding(int buildingID, bool& isSuccess)
{
	//if is not building
	if (!isBuilding)
	{
		//check if building array has object
		if (BuildingArray[buildingID] >= 1)
		{
			//set is building true
			isBuilding = true;

			//setup direction vector
			FActorSpawnParameters SpawnParams;
			FVector StartLocation = PlayerCamComp->GetComponentLocation();
			FVector Direction = PlayerCamComp->GetForwardVector() * 400.0f;
			FVector EndLocation = StartLocation + Direction;
			FRotator myRot(0, 0, 0);

			//subtracting from building array, because built
			BuildingArray[buildingID] = BuildingArray[buildingID] - 1;

			//sets spawned part
			spawnedPart = GetWorld()->SpawnActor<ABuildingPart>(BuildPartClass, EndLocation, myRot, SpawnParams);

			//sets success to true
			isSuccess = true;

		}
	}
}

void APlayerChar::RotateBuilding()
{
	//if is building
	if (isBuilding)
	{
		//object rotation
		spawnedPart->AddActorWorldRotation(FRotator(0, 90, 0));
	}
}

