#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "Enemy.h"

Enemy::Enemy(int x, int y) : position(x, y)
{}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	if(collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr) {
		if(!hit)App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
		else {
			hitAnimation->setCurrentFrameIndex(animation->GetCurrentFrameIndex());
			App->render->Blit(sprites, position.x, position.y, &(hitAnimation->GetCurrentFrame()));
			hit = false;
		}
	}
}

void Enemy::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemyExplosion, position.x, position.y);
	App->ui->AddScore(points);
}
void Enemy::Shine(Collider* collider, SDL_Texture* sprites)
{
	hit = true;
}