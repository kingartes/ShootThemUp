// Shoot them up Game, All right Reserved


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon() {
	if (!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);

}

void USTUWeaponComponent::Fire() {
	if (!CurrentWeapon) return;

	CurrentWeapon->Fire();
}

