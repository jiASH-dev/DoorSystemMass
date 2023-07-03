#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorSystem.generated.h"

UCLASS()
class DOORSYSTEMMASS_API ADoorSystem : public AActor
{
	GENERATED_BODY()

private:
	enum class EAngle
	{
		ZERO_ANGLE,
		RIGHT_ANGLE
	};

protected:
	UPROPERTY(EditDefaultsOnly)
		USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* DoorWay;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Door;

private:
	bool IsDoorClosedStatus;
	bool CanHittedStatus;

private:
	void SetDoorZAngle(EAngle angle, float Alpha);

public:
	ADoorSystem();
	UFUNCTION()
		void PingAboutHitting(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool GetIsDoorClosed();
	UFUNCTION(BlueprintCallable)
		void SetIsDoorClosed(bool IsDoorClosed);
	UFUNCTION(BlueprintCallable)
		void SetCanHitted(bool CanHitted);
	UFUNCTION(BlueprintCallable)
		void SetDoorZAngleByAlphaToOpen(float Alpha);
	UFUNCTION(BlueprintCallable)
		void SetDoorZAngleByAlphaToClose(float Alpha);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
