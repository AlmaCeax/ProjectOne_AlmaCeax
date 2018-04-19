#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"
#include "SDL_mixer/include/SDL_mixer.h"


ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	// BaseShot particle

	baseShotExp.anim.PushBack({ 33, 36, 7, 6 });
	baseShotExp.anim.PushBack({ 49, 34, 12, 12 });
	baseShotExp.anim.loop = false;
	baseShotExp.anim.speed = 0.5f;
	baseShotExp.life = 100;
	baseShotExp.speed = { 1,0 };
	baseShotExp.isPlayerAttached = true;
	baseShotExp.offsetx = 30;
	baseShotExp.offsety = 1;

	baseShotColExp.anim.PushBack({ 81, 34, 12, 12 });
	baseShotColExp.anim.PushBack({ 101, 36, 8, 9 });
	baseShotColExp.anim.loop = false;
	baseShotColExp.anim.speed = 0.3f;
	baseShotColExp.life = 100;
	baseShotColExp.speed = { 0,0 };

	baseShot.w = 17;
	baseShot.h = 4;
	baseShot.anim.PushBack({ 63, 38, 17, 4 });
	baseShot.anim.loop = false;
	baseShot.anim.speed = 0.3f;
	baseShot.life = 1000;
	baseShot.speed = { 10,0 };
	baseShot.id = 1;

	playerBoost.h = 4;
	playerBoost.anim.PushBack({ 251, 208, 42, 14 });
	playerBoost.anim.PushBack({ 295, 208, 42, 13 });
	playerBoost.anim.PushBack({ 342, 208, 42, 11 });
	playerBoost.anim.loop = true;
	playerBoost.anim.speed = 0.2f;
	playerBoost.life = 425;
	playerBoost.speed = { 0,0 };
	playerBoost.id = 3;

	bombExplosion.anim.PushBack({ 97, 171, 16, 16 });
	bombExplosion.anim.PushBack({ 122, 166, 26, 26 });
	bombExplosion.anim.PushBack({ 156, 166, 26, 26 });
	bombExplosion.anim.PushBack({ 188, 166, 26, 26 });
	bombExplosion.anim.PushBack({ 220, 166, 26, 26 });
	bombExplosion.anim.loop = false;
	bombExplosion.anim.speed = 0.7f;
	bombExplosion.life = 200;
	bombExplosion.speed = { 0, 0 };


	bombshot.anim.PushBack({ 4, 170, 15, 4 });
	bombshot.anim.PushBack({ 22, 170, 14, 8 });
	bombshot.anim.PushBack({ 38, 166, 12, 12 });
	bombshot.anim.PushBack({ 58, 165, 9, 14 });
	bombshot.anim.PushBack({ 78, 164, 4, 15 });
	bombshot.anim.loop = false;
	bombshot.anim.speed = 0.03f;
	bombshot.life = 1500;
	bombshot.speed = { 4, 1 };
	bombshot.id = 2;

	blueBall.anim.PushBack({ 10,217,8,8 });
	blueBall.anim.PushBack({ 26,217,8,8 });
	blueBall.anim.PushBack({ 42,217,8,8 });
	blueBall.anim.PushBack({ 58,217,8,8 });
	blueBall.anim.speed = 0.1f;
	blueBall.life = 1500;
	blueBall.speed = { 0,0 };

	enemyExplosion.anim.PushBack({ 103, 284, 26, 22 });
	enemyExplosion.anim.PushBack({ 135, 284, 26, 22 });
	enemyExplosion.anim.PushBack({ 166, 279, 44, 32 });
	enemyExplosion.anim.PushBack({ 217, 280, 37, 28 });
	enemyExplosion.anim.PushBack({ 262, 280, 42, 31 });
	enemyExplosion.anim.PushBack({ 106, 325, 39, 36 });
	enemyExplosion.anim.PushBack({ 155, 324, 36, 35 });
	enemyExplosion.anim.PushBack({ 202, 326, 36, 32 });
	enemyExplosion.anim.PushBack({ 250, 324, 37, 40 });
	enemyExplosion.anim.loop = false;
	enemyExplosion.anim.speed = 0.5f;
	enemyExplosion.life = 200;
	enemyExplosion.speed = { 0, 0 };
	enemyExplosion.id = 2;

	enemyBossExplosion.anim.PushBack({ 254, 11, 46, 40 });
	enemyBossExplosion.anim.PushBack({ 302, 11, 46, 40 });
	enemyBossExplosion.anim.PushBack({ 352, 4, 60, 56 });
	enemyBossExplosion.anim.PushBack({ 413, 5, 26, 26 });
	enemyBossExplosion.anim.PushBack({ 254, 63, 63, 63 });
	enemyBossExplosion.anim.PushBack({ 318, 68, 62, 54 });
	enemyBossExplosion.anim.PushBack({ 382, 64, 61, 63 });
	enemyBossExplosion.anim.PushBack({ 449, 70, 60, 50 });
	enemyBossExplosion.anim.PushBack({ 258, 132, 58, 56 });
	enemyBossExplosion.anim.loop = false;
	enemyBossExplosion.anim.speed = 0.5f;
	enemyBossExplosion.life = 200;
	enemyBossExplosion.speed = { 0, 0 };
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Sprites/MainCharacter/spr_maincharacter.png");

	baseShotExp.sfx = App->audio->LoadFx("Assets/Audio/SFX/xmultipl-083.wav");
	playerBoost.sfx = App->audio->LoadFx("Assets/Audio/SFX/xmultipl-023.wav");
	enemyExplosion.sfx = App->audio->LoadFx("Assets/Audio/SFX/xmultipl-066.wav");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	App->audio->UnloadSFX(baseShotExp.sfx);
	baseShot.sfx = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			App->audio->UnloadSFX(active[i]->sfx);
			active[i]->sfx = nullptr;
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;			
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				if(p->id != 3)Mix_PlayChannel(-1, p->sfx, 0);
			}
		}
	}
	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, fPoint speed, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (!speed.IsZero()) p->speed = speed;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			switch (active[i]->id) {
			case 1: AddParticle(baseShotColExp, active[i]->position.x, active[i]->position.y); break;
			case 2: AddParticle(bombExplosion, active[i]->position.x, active[i]->position.y); break;
			}
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life), isPlayerAttached(p.isPlayerAttached), offsetx(p.offsetx), offsety(p.offsety), sfx(p.sfx), id(p.id)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;


	switch (id)
	{
	case 1:
		position.x += speed.x;
		position.y += speed.y; break;
	case 2: 
		position.x += speed.x;
		position.y += speed.y;
		if (speed.x > 1.55f)speed.x -= 0.1f;
		if (speed.y < 2.0f)speed.y += 0.1f;
		break;
	case 3: 
		position.x = App->player->position.x-42;
		position.y = App->player->position.y;
		break;
	default:
		position.x += speed.x;
		position.y += speed.y;
	}


	if (isPlayerAttached) {

		if (App->player->state == App->player->idl)	offsety = 1;
		else if (App->player->state == App->player->top) offsety = -1;
		else if (App->player->state == App->player->bot) offsety = 2;
		position.y = App->player->position.y + offsety;
		position.x = App->player->position.x + offsetx;
	}

	if (collider != nullptr) {
		collider->SetPos(position.x, position.y);
		collider->SetShape(anim.GetCurrentFrame().w, anim.GetCurrentFrame().h);
	}
		

	return ret;
}