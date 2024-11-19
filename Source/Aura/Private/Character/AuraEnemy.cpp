


#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include <AbilitySystem\AuraAttributeSet.h>
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
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
