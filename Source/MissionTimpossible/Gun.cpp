// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h" // IMPORTANT buat DamageEvent, ngedebug lama disini :(

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	// Initialize ammo values
	CurrentClipAmmo = MaxClipAmmo;
	bIsReloading = false;
}

void AGun::PullTrigger()
{
	// Check if reloading or out of ammo
	if (bIsReloading)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reloading..."));
		return;
	}

	if (CurrentClipAmmo <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Out of ammo in clip! Reload needed."));
		// Optionally, play a "dry fire" sound or trigger reload here
		return;
	}

	// Fire the gun (reduce clip ammo)
	CurrentClipAmmo--;

	// Muzzle flash
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	// Impact Effect
	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		//DrawDebugPoint(GetWorld(), Hit.Location, 10, FColor::Red, true);

		// Damage
        AActor* HitActor = Hit.GetActor();
        if (HitActor != nullptr) 
        {
            // Initialize FPointDamageEvent with damage information
            FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);

            // Apply damage to the hit actor
			AController* OwnerController = GetOwnerController();
            HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
        }
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	// Impact Effect
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
		return false;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = Rotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	FVector End = Location + Rotation.Vector() * MaxRange;

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;
	
	return OwnerPawn->GetController();
}

void AGun::Reload()
{
	// Check if already reloading or full clip ammo
	if (bIsReloading || CurrentClipAmmo == MaxClipAmmo || ReserveAmmo <= 0)
	{
		return;
	}

	bIsReloading = true;
	UE_LOG(LogTemp, Warning, TEXT("Reloading..."));

	// Set timer for reload process
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AGun::FinishReloading, ReloadTime, false);
}

FText AGun::GetAmmoText() const
{
	return FText::FromString(FString::Printf(TEXT("%d/%d"), CurrentClipAmmo, ReserveAmmo));
}

void AGun::FinishReloading()
{
	bIsReloading = false;

	// Calculate ammo needed to refill the clip
	int32 AmmoNeeded = MaxClipAmmo - CurrentClipAmmo;

	// Refill the clip with available reserve ammo
	if (ReserveAmmo >= AmmoNeeded)
	{
		CurrentClipAmmo = MaxClipAmmo;
		ReserveAmmo -= AmmoNeeded;
	}
	else
	{
		CurrentClipAmmo += ReserveAmmo;
		ReserveAmmo = 0;
	}

	UE_LOG(LogTemp, Warning, TEXT("Reload complete. Clip: %d/%d, Reserve: %d"), CurrentClipAmmo, MaxClipAmmo, ReserveAmmo);
}
