#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleSceneStart.h"
#include "ModuleTopScore.h"
#include "ModuleSceneContinue.h"
#include "ModuleSceneStage1.h"
#include "ModuleSceneStage2.h"
#include "ModuleSceneStage3.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"
#include "ModulePowerUPS.h"
#include "ModuleFonts.h"


Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = start = new ModuleSceneStart();
	modules[i++] = scene_continue = new ModuleSceneContinue();
	modules[i++] = top_score = new ModuleTopScore();
	modules[i++] = stage1 = new ModuleSceneStage1();
	modules[i++] = stage2 = new ModuleSceneStage2();
	modules[i++] = stage3 = new ModuleSceneStage3();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = powerups = new ModulePowerUPS();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = fonts = new ModuleFonts();
	modules[i++] = ui = new ModuleUI();
	modules[i++] = fade = new ModuleFadeToBlack();

}	

Application::~Application()
{
	for (int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	player->Disable();
	stage1->Disable();
	stage2->Disable();
	stage3->Disable();
	enemies->Disable();
	collision->Disable();
	powerups->Disable();
	particles->Disable();
	scene_continue->Disable();
	top_score->Disable();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}


bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}

