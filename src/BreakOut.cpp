#include "BreakOut.h"
#include "Bat.h"
#include "Ball.h"
#include <memory>

BreakOut::BreakOut() { sAppName = "BreakOut"; }

bool
BreakOut::OnUserCreate()
{
	world = std::make_unique<World>(*this);
	bat = std::make_unique<Bat>(*this, *world);
	ball = std::make_unique<Ball>(*this, *world, *bat );
	return true;
}

bool
BreakOut::OnUserUpdate(float fElapsedTime)
{
	// Quit game
	if (GetKey(olc::Key::Q).bPressed)
		exit(0);

	// start game
	if (GetKey(olc::Key::SPACE).bPressed)
		playing = true;
		
	if (playing) {
		bat->update(fElapsedTime);
		ball->update(fElapsedTime);
	}
	renderGraphics();
	return true;
}

void
BreakOut::renderGraphics()
{
	SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
	Clear(olc::Pixel(31, 144, 255)); // blue
	if (!playing) {
		auto msg = std::string("PRESS SPACE BAR");
		DrawString(olc::vi2d((world->width() - msg.size() / 2) / 2, world->height() / 2) * world->blockSize(), msg, olc::WHITE);
	}
	world->draw();
	bat->draw();
	ball->draw();
	SetPixelMode(olc::Pixel::NORMAL); // Draw all pixels
}
