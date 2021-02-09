#include "BreakOut.h"
#include "Bat.h"
#include "Ball.h"
#include <memory>

BreakOut::BreakOut() { sAppName = "BreakOut"; }

bool
BreakOut::OnUserCreate()
{
	blocks_ = std::make_unique<World>();
	bat = std::make_unique<Bat>(*this, *blocks_);
	ball = std::make_unique<Ball>(*this, *blocks_, *bat );
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
		DrawString(olc::vi2d((blocks_->width() - msg.size() / 2) / 2, blocks_->height() / 2) * blocks_->blockSize(), msg, olc::WHITE);
	}
	blocks_->drawMap(this);
	bat->draw();
	ball->draw();
	SetPixelMode(olc::Pixel::NORMAL); // Draw all pixels
}
