// Shoot them up Game, All right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BluePrintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal", meta = (EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal", meta = (EditCondition = "AutoHeal"))
	float HealAmount = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal", meta = (EditCondition = "AutoHeal"))
	float HealTickRate = 1.0f;
	
	virtual void BeginPlay() override;

private:
	float Health = 0.0f;

	FTimerHandle HealTimerHandle;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
		
	void HealUpdate();
	void SetHealth(float NewHealth);
};
