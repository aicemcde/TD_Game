#include "AIDeath.h"
#include "Actor.h"
#include "AIComponent.h"

AIDeath::AIDeath(class AIComponent* owner)
	:AIState(owner)
{
}

void AIDeath::Update(float deltaTime)
{
	// 死亡状態では何もしない
}

void AIDeath::OnExit()
{

}

void AIDeath::OnEnter()
{
	// 死亡時の処理をここに追加（例：アニメーションの再生、当たり判定の無効化など）
	mOwner->GetOwner()->SetState(Actor::EDead);
}