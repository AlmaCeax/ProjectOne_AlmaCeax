#include "Enemy_Zarikasu.h"
#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include <stdlib.h> 



Enemy_Zarikasu::Enemy_Zarikasu(int x, int y, int id): Enemy(x, y)
{
	type = SNAKEBODY;

	myid = id;
	w = 64;
	h = 60;

	switch (id)
	{
	case 1: speed = { -1, -1 };  break;
	case 2: 
		speed = { +1, -1 };
		flipX = true; 
		break;
	case 3: 
		speed = { -1, 1 };
		flipY = true; 
		break;
	case 4: 
		speed = { +1, +1 };
		flipX = true; 
		flipY = true; 
		break;
	default:
		break;
	}

	preparation = true;

	background_position = { 5375, 96 };

	center = { 24, 15 };
	anim.PushBack({ 693, 1665, 64, 60 });
	anim.PushBack({ 760, 1665, 64, 60 });
	anim.PushBack({ 702, 1730, 64, 60 });
	anim.PushBack({ 771, 1730, 64, 60 });
	hitanim.PushBack({ 849, 1665, 64, 60 });
	hitanim.PushBack({ 916, 1665, 64, 60 });
	hitanim.PushBack({ 858, 1730, 64, 60 });
	hitanim.PushBack({ 927, 1730, 64, 60 });
	anim.speed = 0.f;

	animation = &anim;
	hitAnimation = &hitanim;

	bckg_texture = App->textures->Load("Assets/Sprites/Stages/Stage3/bossbackground.png");

	collider = App->collision->AddCollider({ 0, 0, 64, 60 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	points = 100000;
}

void Enemy_Zarikasu::Move()
{
	if (preparation) {
		position += speed;
	}
	switch (myid)
	{
	case 1:
		if (position.y == 247) {
			preparation = false;
			anim.setCurrentFrameIndex(1);
		}
		if (shootTimer == 70) {
			shooting = true;
		}/*AddParticle.. */break;
	case 2:
		if (position.y == 247) {
			preparation = false;
			anim.setCurrentFrameIndex(1);

		}
		if (shootTimer == 70) {
			shooting = true;
		}
		break;
	case 3:
		if (position.y == 110) {
			preparation = false;
			anim.setCurrentFrameIndex(1);
		}
		if (shootTimer == 240) {
			shooting = true;
		}
		break;
	case 4:
		if (position.y == 110) {
			preparation = false;
			anim.setCurrentFrameIndex(1);
		}
		if (shootTimer == 180){
			shooting = true;
		}
		break;
	default:
		break;
	}
	if (shooting)
	{
		anim.setCurrentFrameIndex(3);
	}
	shootTimer++;
}

void Enemy_Zarikasu::Draw(SDL_Texture* sprites)
{
	Enemy::Draw(sprites);
	App->render->Blit(bckg_texture, background_position.x, background_position.y, nullptr);
}
