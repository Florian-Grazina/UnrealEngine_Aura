


#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include <AbilitySystem\AuraAttributeSet.h>
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	//Replicating means the server will change the value of the variable on the clients
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AAuraEnemy::HighlightActor()
{
	SetHighlight(true);
}

void AAuraEnemy::UnHighlightActor()
{
	SetHighlight(false);
}

void AAuraEnemy::SetHighlight(bool value)
{
	USkeletalMeshComponent* MeshComp = GetMesh();

	int stencilValue = value? CUSTOM_DEPTH_RED : 0;

	MeshComp->SetRenderCustomDepth(value);
	MeshComp->SetCustomDepthStencilValue(stencilValue);
	Weapon->SetRenderCustomDepth(value);
	Weapon->SetCustomDepthStencilValue(stencilValue);
}
