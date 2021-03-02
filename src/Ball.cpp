#include "Ball.h"
#include "Bat.h"
#include "BreakOut.h"

Ball::Ball(olc::PixelGameEngine &game, World &blocks, Bat &bat)
		  : game_(game), world_(blocks), bat_(bat)
{
	sprBall = std::make_unique<olc::Sprite>("../assets/gfx/ballGrey_16x16.png");
	radius_ = float(sprBall->width) / float(world_.blockSize().x) / 2.0f;
	reset(world_.width() / 2.0f, world_.height()/ 2.0f);
	roll();
} 

void
Ball::update(float fElapsedTime)
{
	if (game_.GetKey(olc::Key::R).bPressed)
		reset(world_.width() / 2.0f, world_.height()/ 2.0f);

	auto potentialPos = position_ + velocity_ * fElapsedTime;

	// area of detection
	olc::vi2d currentCell = position_.floor();
	olc::vi2d targetCell = potentialPos;
	olc::vi2d worldSize{ int(world_.width()), int(world_.height()) };
	olc::vi2d areaTopleft = (currentCell.min(targetCell) - olc::vi2d(1, 1)).max({ 0, 0 });
	olc::vi2d areBottomRight = (currentCell.max(targetCell) + olc::vi2d(1, 1)).min(worldSize - olc::vi2d(1, 1));
	// iterate through the cells in the limited area
	olc::vi2d cell;
	olc::vi2d cellSize{ 1, 1 };
	for (cell.y = areaTopleft.y; cell.y <= areBottomRight.y; ++cell.y)
		for (cell.x = areaTopleft.x; cell.x <= areBottomRight.x; ++cell.x) {
			auto &tile{world_[cell.y * world_.width() + cell.x]};
			olc::vf2d contactPnt;
			if (tile > 0 && circleVsRect(potentialPos, cell, cellSize, contactPnt)) {
				olc::vf2d normal{contactNormal(contactPnt, cell, cellSize)};
				// reflection ray equation: r = d - 2n(d * n)
				auto incedentRay{velocity_.norm()};
				auto reflectedRay{incedentRay - 2 * normal * incedentRay.dot(normal)};
				velocity_ = reflectedRay * velocity_.mag();
				if (tile < 10) --tile;
			}
		}
	position_ += velocity_ * fElapsedTime;

	// TODO: should use state pattern instead
	if (position_.y > world_.height()) {
		reset(world_.width() / 2.0f, world_.height() / 2.0f);
		isOutOfBounds = true;
	}

	if (isOutOfBounds && game_.GetKey(olc::Key::SPACE).bPressed) {
		roll();
		isOutOfBounds = false;
	}
}

void
Ball::draw()
{
	if (isOutOfBounds) {
		auto msg = std::string("PRESS SPACE BAR");
		game_.DrawString(olc::vi2d((world_.width() - msg.size() / 2) / 2, world_.height() / 2) * world_.blockSize(), msg, olc::WHITE);
	} else {
		olc::vf2d offset{ radius_, radius_ }; // to set origin at centre of sprite
		game_.DrawSprite((position_ - offset) * world_.blockSize(), sprBall.get());
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
	velocity_ = { 0.0f, 0.0f };
	position_ = { x, y };
}

void
Ball::roll()
{
	// change 1.0f to 2.0f to get an angle value between 0 and 2PI (360 degrees) as well.
	float angle_{randomf(0.1f, 0.9f) * 1.0f * float(M_PI)};
	olc::vf2d direction_{ cosf(angle_), sinf(angle_) };
	float speed_{20.0f};
	velocity_ = speed_ * direction_;
}

bool
Ball::circleVsRect(const olc::vf2d &pos, const olc::vf2d &rectPos, const olc::vf2d &rSize,
		           olc::vf2d &contactPnt)
{
	olc::vf2d nearestPnt;
	nearestPnt.x = std::max(rectPos.x, std::min(rectPos.x + rSize.x, pos.x));
	nearestPnt.y = std::max(rectPos.y, std::min(rectPos.y + rSize.y, pos.y));
	olc::vf2d nearestRay{nearestPnt - pos};
	float overlap{radius_ - nearestRay.mag()};
	if (std::isnan(overlap)) overlap = 0;
	if (overlap > 0) { // collision
		auto dir{nearestRay.norm()};
		contactPnt = (pos - dir * overlap) + dir * (radius_);; 
		return true;
	}
	return false;
}

olc::vf2d
Ball::contactNormal(const olc::vf2d &point, const olc::vf2d &rect, const olc::vf2d &rSize)
{
	auto [height, width]{rSize};
	olc::vf2d rectCentre{ rect.x + height / 2.0f, rect.y + width / 2.0f };
	auto ballPosition{ point - rectCentre };
	auto [a, b]{ballPosition};
	if (std::abs(a) < width / 2 && b == -height / 2) // top edge
		return { 0.0f, -1.0f };
	if (std::abs(a) < width / 2 && b == height / 2) // bottom edge
		return { 0.0f, 1.0f };
	if (a == -width / 2 && std::abs(b) < height / 2) // left edge
		return { -1.0f, 0.0f };
	if (a == width / 2 && std::abs(b) < height / 2) // right edge
		return { 1.0f, 0.0f };
	return ballPosition.norm(); // corners: left-top/right and bottom-left/right
}
