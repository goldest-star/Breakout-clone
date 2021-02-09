#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "../include/olcPixelGameEngine.h"
#include "World.h"
#include <algorithm>
#include <memory>
#include "Ball.h"
#include "Bat.h"

class BreakOut : public olc::PixelGameEngine {
public:
	BreakOut();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
private:
	std::unique_ptr<World> blocks_;
	std::unique_ptr<Bat> bat;
	std::unique_ptr<Ball> ball;
	void renderGraphics();
	bool playing{false};
};
#endif /* ifndef BREAKOUT_H */
