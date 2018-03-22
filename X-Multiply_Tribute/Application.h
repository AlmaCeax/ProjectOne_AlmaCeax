#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 6

class ModuleWindow;
class ModuleInput;
class ModuleAudios;
class ModuleTextures;
class ModuleRender;
class Module;
class ModuleAudio;
class ModuleMap;

class Application
{
public:

	Module* modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* texture = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleMap* map = nullptr;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__