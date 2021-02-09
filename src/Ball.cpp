#include "Ball.h"
#include "Bat.h"
#include "BreakOut.h"

Ball::Ball(olc::PixelGameEngine &game, World &blocks, Bat &bat)
		  : game_(game), blocks_(blocks), bat_(bat)
{
	sprBall = std::make_unique<olc::Sprite>("../assets/gfx/ballGrey_16x16.png");
	radius_ = sprBall->width / 2.0f; // NOTE: unit is in screen space
	reset(blocks_.width() / 2.0f, blocks_.height()/ 2.0f);
} 

void
Ball::update(float fElapsedTime)
{
	if (game_.GetKey(olc::Key::R).bPressed)
		reset(blocks_.width() / 2.0f, blocks_.height()/ 2.0f);

	olc::vf2d tileRadialDimensions_{ radius_ / blocks_.blockSize().x, radius_ / blocks_.blockSize().y };
	auto potentialPos = position_ + velocity_ * fElapsedTime;
	hasHitTile = false;
	hasHitTile |= testResolveCollision(potentialPos, olc::vf2d(0,-1)); // northern
	hasHitTile |= testResolveCollision(potentialPos, olc::vf2d(0,+1)); // southern
	hasHitTile |= testResolveCollision(potentialPos, olc::vf2d(-1,0)); // western
	hasHitTile |= testResolveCollision(potentialPos, olc::vf2d(+1,0)); // eastern

	// bat collision (circle vs rectangle collision)
	if (potentialPos.y >= bat_.position().y) {
		// clamp ball position to bat's size
		float nx{std::max(bat_.position().x, std::min(bat_.position().x + bat_.width(), potentialPos.x))};
		float ny{std::max(bat_.position().y, std::min(bat_.position().y + bat_.height(), potentialPos.y))};
		olc::vf2d rNearestPnt{nx, ny};
		// check for collision
		if ((potentialPos - rNearestPnt).mag() <= radius_ / blocks_.blockSize().x) {
			// dynamic collision resolution
			auto &reverseAxis = (velocity_.x > velocity_.y) ? velocity_.x : velocity_.y; 
			reverseAxis *= -1;
		}
	}

	// ball position is out of bound  *** this is buggy ***
	isOutOfBounds = position_.y > blocks_.height();
	if (isOutOfBounds && game_.GetKey(olc::Key::SPACE).bPressed) {
		reset(blocks_.width() / 2.0f, blocks_.height() / 2.0f);
		isOutOfBounds = false;
	}
	position_ += velocity_ * fElapsedTime; // delta x = delta v * delta t
}

void
Ball::draw()
{
	if (isOutOfBounds) {
		auto msg = std::string("PRESS SPACE BAR");
		game_.DrawString(olc::vi2d((blocks_.width() - msg.size() / 2) / 2, blocks_.height() / 2) * blocks_.blockSize(), msg, olc::WHITE);
	} else {
		olc::vf2d tileRadialDimensions_{ radius_ / blocks_.blockSize().x, radius_ / blocks_.blockSize().y };
		game_.DrawSprite((position_ - tileRadialDimensions_) * blocks_.blockSize(), sprBall.get());
	}
}

void 
Ball::reset(const olc::vf2d &postion)
{
	reset(postion.x, postion.y);
}

void
Ball::reset(float x, float y)
{
	// change 1.0f to 2.0f to get an angle value between 0 and 2PI (360 degrees) as well.
	float angle_{randomf(0.1f, 0.9f) * 1.0f * float(M_PI)};
	olc::vf2d direction_{ cosf(angle_), sinf(angle_) };
	float speed_{20.0f};
	velocity_ = speed_ * direction_;
	position_ = { x, y };
}

bool
Ball::testResolveCollision(const olc::vf2d &position, const olc::vf2d &point)
{
	olc::vf2d tileRadialDimensions_{ radius_ / blocks_.blockSize().x, radius_ / blocks_.blockSize().y };
	// offset to center point of reference
	olc::vf2d offset = { radius_ / blocks_.blockSize().x, radius_ / blocks_.blockSize().y };
	olc::vi2d vTestPoint =  offset + position + tileRadialDimensions_ * point;
	auto index = vTestPoint.y * blocks_.width() + vTestPoint.x;
	auto &tile = blocks_[index];
	if (tile == 0 || index > blocks_.size())
		return false;
	bool bTileHit = tile < 10;
	if (bTileHit) {
		hitID = tile;
		hitpos = { float(vTestPoint.x), float(vTestPoint.y) }; 
		--tile;
	}
	// collision response
	if (point.x == 0.0f) velocity_.y *= -1.0f;
	if (point.y == 0.0f) velocity_.x *= -1.0f;
	return true;
}
