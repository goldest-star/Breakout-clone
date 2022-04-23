#include "BreakOut.h"
#include "BatInputComponent.h"
#include "BatPhysicsComponent.h"
#include "BatGraphicsComponent.h"
#include "BallInputComponent.h"
#include "BallPhysicsComponenet.h"
#include "BallGraphicsComponent.h"

BreakOut::BreakOut() { sAppName = "BreakOut"; }

bool
BreakOut::OnUserCreate()
{
	world = std::make_unique<World>(*this);
	bat = std::make_unique<GameObject>(new BatInputComponent(),
			new BatPhysicsComponent(), new BatGraphicsComponent());
	ball = std::make_unique<GameObject>(new BallInputComponent(),
			new BallPhysicsComponent(), new BallGraphicsComponent());
	bat->position() = { world->width() / 2.0f , world->height() - 1.0f };
	bat->size() = { 4, 1 };
	bat->velocity() = { 20.0f, 0.0f };

	ball->position() = { world->width() / 2.0f , world->height() / 2.0f };
	roll(*ball);

	return true;
}

bool
BreakOut::OnUserUpdate([[maybe_unused]]float fElapsedTime)
{
	// Quit game
	if (GetKey(olc::Key::Q).bPressed)
		return false;

	bat->update(this, world.get());
	ball->update(this, world.get());

	SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
	Clear(olc::Pixel(31, 144, 255)); // blue
	world->draw();
	bat->draw(this);
	ball->draw(this);
	SetPixelMode(olc::Pixel::NORMAL); // Draw all pixels

	return true;
}
