#ifndef ENTITY_H
#define ENTITY_H

#include "../include/olcPixelGameEngine.h"
#include "TileMap.h"

class Entity {
public:
	virtual ~Entity() = default;
	virtual void update() = 0;
	virtual void draw(olc::PixelGameEngine *game) = 0;
	olc::vf2d& position() { return position_; } 
private:
	olc::vf2d position_ = { 0, 0 };
};
#endif /* ifndef ENTITY_H */
