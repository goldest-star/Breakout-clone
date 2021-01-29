#ifndef ENTITY_H
#define ENTITY_H

#include "../include/olcPixelGameEngine.h"

// Abstract class
class Entity {
public:
	Entity(olc::PixelGameEngine &game) : game_(game) {}
	virtual ~Entity() = default;
	virtual void update(float fElapsedTime) = 0;
	virtual void draw() = 0;
	olc::PixelGameEngine& getGameEngine() { return game_; }
protected:
	olc::PixelGameEngine &game_;
};
#endif /* ifndef ENTITY_H */
