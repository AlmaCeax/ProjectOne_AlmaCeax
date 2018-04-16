#ifndef __MODULEPOWERUPS_H__
#define __MODULEPOWERUPS_H__

#include "Module.h"

#define MAX_POWERUPS 20

enum pu_type 
{	LASER,
	MISSILE, 
	SHADOW, 
	BOMB, 
	SPEED_BOOST, 
	SPEED_DOWN, 
	LIFE 
};

struct PowerUP 
{
	bool enabled;
	Animation anim;
	iPoint position;
	pu_type type;
	int h, w = 0;
	Collider* collider = nullptr;

	PowerUP() {}
	PowerUP(iPoint _position):
		position(_position) 
	{}
	~PowerUP() {}
	bool Update() {}
	bool isEnabled() { return enabled; }
	void setEnabled(bool _enable) { enabled = _enable; }
};

class ModulePowerUPS :  public Module
{
public:
	ModulePowerUPS();
	~ModulePowerUPS();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

private:
	SDL_Texture * graphics = nullptr;
	PowerUP* poweUps[MAX_POWERUPS];

public:
	PowerUP life;
	PowerUP speedBoost;
	PowerUP speedDown;
	PowerUP bomb;
	PowerUP tentacles;
};

#endif
