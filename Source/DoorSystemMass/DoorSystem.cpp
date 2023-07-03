#include "DoorSystem.h"
#include "DoorSystemMassCharacter.h"

ADoorSystem::ADoorSystem()
{
	PrimaryActorTick.bCanEverTick = true;

	IsDoorClosedStatus = true;
	CanHittedStatus = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	DoorWay = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorWay"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

	DoorWay->SetupAttachment(Root);
	Door->SetupAttachment(Root);
}

void ADoorSystem::BeginPlay()
{
	Super::BeginPlay();
	Door->OnComponentHit.AddDynamic(this, &ADoorSystem::PingAboutHitting);
}

void ADoorSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoorSystem::PingAboutHitting(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (CanHittedStatus)
	{
		UE_LOG(LogTemp, Warning, TEXT("To open the door, you must put some objects in the trigger (Avaliable mass = 50 kg)"));
		CanHittedStatus = false;
	}
}

bool ADoorSystem::GetIsDoorClosed()
{
	return IsDoorClosedStatus;
}

void ADoorSystem::SetIsDoorClosed(bool IsDoorClosed)
{
	this->IsDoorClosedStatus = IsDoorClosed;
}

void ADoorSystem::SetCanHitted(bool CanHitted)
{
	this->CanHittedStatus = CanHitted;
}

void ADoorSystem::SetDoorZAngleByAlphaToOpen(float Alpha)
{
	SetDoorZAngle(EAngle::RIGHT_ANGLE, Alpha);
}

void ADoorSystem::SetDoorZAngleByAlphaToClose(float Alpha)
{
	SetDoorZAngle(EAngle::ZERO_ANGLE, Alpha);
}

void ADoorSystem::SetDoorZAngle(EAngle angle, float Alpha)
{
	float CurrentYawAngle = Door->GetComponentRotation().Yaw;
	float UpdatedAngle;
	switch (angle)
	{
	case EAngle::ZERO_ANGLE:
		UpdatedAngle = FMath::Lerp(CurrentYawAngle, 0.f, Alpha);
		break;
	case EAngle::RIGHT_ANGLE:
		UpdatedAngle = FMath::Lerp(CurrentYawAngle, 90.f, Alpha);
		break;
	}
	Door->SetWorldRotation(FRotator(0.f, UpdatedAngle, 0.f));
}

