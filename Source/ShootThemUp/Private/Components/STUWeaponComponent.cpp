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

	CurrentWeaponIndex = 0;
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}

	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons() {


	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!GetWorld() || !Character) return;

	for (auto WeaponClass : WeaponClasses) {
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
		if (!Weapon) return;

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttacWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void USTUWeaponComponent::AttacWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName SocketName) 
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttacWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttacWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
}

void USTUWeaponComponent::StartFire() {
	if (!CurrentWeapon) return;

	CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire() {
	if (!CurrentWeapon) return;

	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon() 
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

