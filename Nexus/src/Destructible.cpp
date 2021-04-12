#include <stdio.h>
#include "main.h"
#pragma warning(disable : 4996)
Destructible::Destructible(float maxHp, float defense, const char* corpseName, int xp) :
	maxHp(maxHp), hp(maxHp), defense(defense),xp(xp){
	this->corpseName = _strdup(corpseName);
}

Destructible::~Destructible() {
	free((char*)corpseName);
}

Destructible* Destructible::create(TCODZip& zip) {
	DestructibleType type = (DestructibleType)zip.getInt();
	Destructible* destructible = NULL;
	switch (type) {
	case MONSTER: destructible = new MonsterDestructible(0, 0, NULL, 0); break;
	case PLAYER: destructible = new PlayerDestructible(0, 0, NULL); break;
	}
	destructible->load(zip);
	return destructible;
}


float Destructible::takeDamage(Actor* owner, float damage) {
	damage -= defense;
	if (damage > 0) {
		hp -= damage;
		if (hp <= 0) {
			die(owner);
		}
	}
	else {
		damage = 0;
	}
	return damage;
}

float Destructible::heal(float amount) {
	hp += amount;
	if (hp > maxHp) {
		amount -= hp - maxHp;
		hp = maxHp;
	}
	return amount;
}

void Destructible::die(Actor* owner) {
	// transform the actor into a corpse!
	owner->ch = '%';
	owner->col = TCODColor::darkRed;
	owner->name = corpseName;
	owner->blocks = false;
	// make sure corpses are drawn before living actors
	engine.sendToBack(owner);
}

void Destructible::load(TCODZip& zip) {
	maxHp = zip.getFloat();
	hp = zip.getFloat();
	defense = zip.getFloat();
	corpseName = strdup(zip.getString());
	xp = zip.getInt();
}

void Destructible::save(TCODZip& zip) {
	zip.putFloat(maxHp);
	zip.putFloat(hp);
	zip.putFloat(defense);
	zip.putString(corpseName);
	zip.putInt(xp);
}
MonsterDestructible::MonsterDestructible(float maxHp, float defense, const char* corpseName,int xp) :
	Destructible(maxHp, defense, corpseName,xp) {
}

void MonsterDestructible::save(TCODZip& zip) {
	zip.putInt(MONSTER);
	Destructible::save(zip);
}

void MonsterDestructible::die(Actor* owner) {
	// transform it into a nasty corpse! it doesn't block, can't be
	// attacked and doesn't move
	engine.gui->message(TCODColor::lightGrey, "%s is dead. You gain %d xp", owner->name,xp);
	engine.player->destructible->xp += xp;
	Destructible::die(owner);
}

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char* corpseName) :
	Destructible(maxHp, defense, corpseName, 0) {
}

void PlayerDestructible::save(TCODZip& zip) {
	zip.putInt(PLAYER);
	Destructible::save(zip);
}

void PlayerDestructible::die(Actor* owner) {
	engine.gui->message(TCODColor::red, "You died!");
	Destructible::die(owner);
	engine.gameStatus = Engine::DEFEAT;
}
