#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer()
{
	position.x = 10;
	position.y = 50;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 100, 1, 36, 14 });
	idle.PushBack({ 100, 1, 36, 14 });
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	up.PushBack({ 53, 2, 36, 14 });
	up.PushBack({ 5, 2, 36, 14 });
	up.speed = 0.1f;
	up.repeat = false;

	down.PushBack({ 149, 1, 36, 14 });
	down.PushBack({ 198, 1, 36, 14 });
	down.speed = 0.1f;
	down.repeat = false;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Sprites/MainCharacter/spr_maincharacter.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;
	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &up;
		position.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		current_animation = &down;
		position.y += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &idle;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &idle;
		position.x -= speed;
	}
	if (last_animation != current_animation) {
		current_animation->ResetAnimation();
	}
	last_animation = current_animation;
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}