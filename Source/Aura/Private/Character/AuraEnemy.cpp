


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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

	int stencilValue = 0;
	if(value)
		stencilValue = CUSTOM_DEPTH_RED;

	MeshComp->SetRenderCustomDepth(value);
	MeshComp->SetCustomDepthStencilValue(stencilValue);
	Weapon->SetRenderCustomDepth(value);
	Weapon->SetCustomDepthStencilValue(stencilValue);
}
