#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"


#define MAX_ENEMIES 100

struct Mix_Chunk;

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y, powerUpid;
	bool going_up;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(ENEMY_TYPES type, int x, int y, bool going_up = false, int powerUPid = -1);
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;

protected:

	Mix_Chunk * pushipDeadsfx;
	Mix_Chunk * nemonaDeadsfx;
	Mix_Chunk * hellballDeadsfx;
	Mix_Chunk * flyerDeadsfx;

};

#endif // __ModuleEnemies_H__