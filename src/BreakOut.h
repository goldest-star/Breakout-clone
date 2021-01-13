#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "../include/olcPixelGameEngine.h"
#include "TileMap.h"
#include "Bat.h"
#include "Ball.h"
#include <memory>


class BreakOut : public olc::PixelGameEngine {
public:
	BreakOut();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	void handleUserInput(float fElapsedTime);
	void drawScreen();
	std::unique_ptr<TileMap> tileMap;
	std::unique_ptr<Bat> bat;
	std::unique_ptr<Ball> ball;
};

#endif /* ifndef BREAKOUT_H */
