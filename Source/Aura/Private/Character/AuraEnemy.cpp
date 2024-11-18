


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	USkeletalMeshComponent* MeshComp = GetMesh();

	MeshComp->SetRenderCustomDepth(true);
	MeshComp->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(stencilValue);
}

void AAuraEnemy::UnHighlightActor()
{
	USkeletalMeshComponent* MeshComp = GetMesh();

	MeshComp->SetRenderCustomDepth(value);
	MeshComp->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(value);
	Weapon->SetCustomDepthStencilValue(stencilValue);
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
