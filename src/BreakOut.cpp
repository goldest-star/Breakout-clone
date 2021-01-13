#include "BreakOut.h"
#include "TileMap.h"
#include <memory>

BreakOut::BreakOut() { sAppName = "BreakOut"; }

bool
BreakOut::OnUserCreate()
{
	
	tileMap = std::make_unique<TileMap>();
	bat = std::make_unique<Bat>(tileMap.get());
	ball = std::make_unique<Ball>();
	return true;
}

bool
BreakOut::OnUserUpdate(float fElapsedTime)
{
	handleUserInput(fElapsedTime);
	bat->update();
	drawScreen();
	return true;
}

void
BreakOut::handleUserInput(float fElapsedTime)
{
	// Quit key
	if (GetKey(olc::Key::Q).bPressed)
		exit(0);

	// Bat movements
	if (GetKey(olc::Key::LEFT).bHeld || GetKey(olc::Key::A).bHeld) {
		bat->position().x -= bat->speed() * fElapsedTime;
	}
	if (GetKey(olc::Key::RIGHT).bHeld || GetKey(olc::Key::D).bHeld) {
		bat->position().x += bat->speed() * fElapsedTime;
	}
	if (auto leftWallEdge = 1; bat->position().x < leftWallEdge) {
		bat->position().x = leftWallEdge;
	}
	if (auto rightWallEdge = tileMap->width() - 1;
			bat->position().x + bat->width() > rightWallEdge) {
		bat->position().x = rightWallEdge - bat->width();
	}
}

void
BreakOut::drawScreen()
{
	SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
	Clear(olc::Pixel(31, 144, 255));
	tileMap->drawMap(this);
	ball->draw(this);
	bat->draw(this);
	SetPixelMode(olc::Pixel::NORMAL); // Draw all pixels
}
