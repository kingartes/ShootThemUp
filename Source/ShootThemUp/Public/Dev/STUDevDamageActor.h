// Shoot them up Game, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditANywhere, BluePrintReadWrite)
	float Radius = 300.f;

	UPROPERTY(EditANywhere, BluePrintReadWrite)
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditANywhere, BluePrintReadWrite)
	float Damage = 10.f;

	UPROPERTY(EditANywhere, BluePrintReadWrite)
	bool DoFullDamage = false;

	UPROPERTY(EditANywhere, BluePrintReadWrite)
	TSubclassOf<UDamageType> DamageType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
