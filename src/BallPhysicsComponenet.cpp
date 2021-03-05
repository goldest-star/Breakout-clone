#include "BallPhysicsComponenet.h"
#include "World.h"

void
BallPhysicsComponent::update(GameObject &ball, const olc::PixelGameEngine &pge, World &world)
{
	if (pge.GetKey(olc::Key::R).bPressed) {
		reset(ball, world.width() / 2.0f, world.height()/ 2.0f);
		isOutOfBounds = true;
	}

	auto fElapsedTime = pge.GetElapsedTime();
	auto potentialPos = ball.position() +ball.velocity() * fElapsedTime;

	// area of detection
	olc::vi2d currentCell = ball.position().floor();
	olc::vi2d targetCell = potentialPos;
	olc::vi2d worldSize{ int(world.width()), int(world.height()) };
	olc::vi2d areaTopleft = (currentCell.min(targetCell) - olc::vi2d(1, 1)).max({ 0, 0 });
	olc::vi2d areBottomRight = (currentCell.max(targetCell) + olc::vi2d(1, 1)).min(worldSize - olc::vi2d(1, 1));
	// iterate through the cells in the limited area
	olc::vi2d cell;
	olc::vi2d cellSize{ 1, 1 };
	for (cell.y = areaTopleft.y; cell.y <= areBottomRight.y; ++cell.y)
		for (cell.x = areaTopleft.x; cell.x <= areBottomRight.x; ++cell.x) {
			auto &tile{world[cell.y * world.width() + cell.x]};
			olc::vf2d contactPnt;
			if (tile > 0 && circleVsRect(potentialPos, cell, cellSize, contactPnt)) {
				olc::vf2d normal{contactNormal(contactPnt, cell, cellSize)};
				// reflection ray equation: r = d - 2n(d * n)
				auto incedentRay{ball.velocity().norm()};
				auto reflectedRay{incedentRay - 2 * normal * incedentRay.dot(normal)};
				ball.velocity() = reflectedRay * ball.velocity().mag();
				if (tile < 10) --tile;
			}
		}
	ball.position() += ball.velocity() * fElapsedTime;

	// TODO: should use state pattern instead
	if (ball.position().y > world.height()) {
		reset(ball, world.width() / 2.0f, world.height() / 2.0f);
		isOutOfBounds = true;
	}

	if (isOutOfBounds && pge.GetKey(olc::Key::SPACE).bPressed) {
		roll(ball);
		isOutOfBounds = false;
	}
}

bool
BallPhysicsComponent::circleVsRect(const olc::vf2d &pos, const olc::vf2d &rectPos,
		                           const olc::vf2d &rSize, olc::vf2d &contactPnt)
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
