#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "../include/olcPixelGameEngine.h"
#include "Entity.h"
#include "World.h"
#include <algorithm>
#include <memory>
#include <vector>

class BreakOut : public olc::PixelGameEngine {
public:
	BreakOut();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
private:
	std::unique_ptr<World> world;
	std::unique_ptr<Entity> bat;
	std::unique_ptr<Entity> ball;
	void renderGraphics();
	bool playing{false};
};
#endif /* ifndef BREAKOUT_H */
