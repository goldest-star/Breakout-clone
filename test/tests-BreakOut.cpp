#include <catch2/catch.hpp>
#include "../src/BreakOut.h"

TEST_CASE ("New game default values tests", "[BreakOut]") {
	BreakOut game;
	//game.Construct(800, 600, 2, 2);
	game.OnUserCreate();
	auto &tmap = game.tileMap;
	static constexpr size_t width = 24;
	static constexpr size_t height = 30;

	SECTION("has a tile map of size height * width") {
		REQUIRE(tmap->width() == width);
		REQUIRE(tmap->height() == height);
		REQUIRE(tmap->size() == height * width);
	}

	SECTION("has left wall from (0,0) to (0, height - 1)") {
		game.OnUserCreate();
		for (size_t y = 0, x = 0; y < tmap->height(); ++y) {
			REQUIRE(tmap->blocks[y * tmap->width() + x] == 10);
		}
	}

	SECTION("has top wall from (0, 0) to (width - 1, 0)") {
		for (size_t x = 0, y = 0; x < tmap->width(); ++x) {
			REQUIRE(tmap->blocks[y * tmap->width() + x] == 10);
		}
	}

	SECTION("has right wall from (width - 1, 0) to (width - 1, height - 1)") {
		for (size_t x = 0, y = 0; x < tmap->width(); ++x) {
			REQUIRE(tmap->blocks[y * tmap->width() + x] == 10);
		}
	}

	SECTION("has breakable bricks") {
		for (size_t y = 0; y < tmap->height(); ++y) {
			for (size_t x = 0; x < tmap->width(); ++x) {
				if (x > 2 && x < tmap->width() - 3 && y > 3 && y <= 5)
					REQUIRE(tmap->blocks[y * tmap->width() + x] == 1);
				if (x > 2 && x < tmap->width() - 3 && y > 5 && y <= 7)
					REQUIRE(tmap->blocks[y * tmap->width() + x] == 2);
				if (x > 2 && x < tmap->width() - 3 && y > 7 && y <= 9)
					REQUIRE(tmap->blocks[y * tmap->width() + x] == 3);
				if (x > 2 && x < tmap->width() - 3 && y > 9 && y <= 11)
					REQUIRE(tmap->blocks[y * tmap->width() + x] == 4);
			}
		}
	}

//	SECTION("All other Blocks are filled with 0's") {
//		for (size_t y = 0; y < tmap->height(); ++y) {
//			for (size_t x = 0; x < tmap->width(); ++x) {
//				if (x == 0 || y == 0 || x == tmap->width() - 1)
//					continue;
//				if (x > 2 && x < tmap->width() - 3 && y > 3 && y <= 5)
//					continue;
//				if (x > 2 && x < tmap->width() - 3 && y > 5 && y <= 7)
//					continue;
//				if (x > 2 && x < tmap->width() - 3 && y > 7 && y <= 9)
//					continue;
//				if (x > 2 && x < tmap->width() - 3 && y > 9 && y <= 11)
//					continue;
//				REQUIRE(tmap->blocks[y * tmap->width() + x] == 0);
//			}
//		}
//	}
}

TEST_CASE("Bat methods assertions") {
	BreakOut game;
	game.OnUserCreate();
	auto center_x = 10;
	auto bottom_y = 29;
	auto &map = game.tileMap;
	auto &bat = game.bat;


	SECTION("Default width is 4") {
		REQUIRE(game.bat->width() == 4.0f);
	}

	SECTION("Default bat position is bottom centre") {
		REQUIRE(bat->position().x == center_x);
		REQUIRE(bat->position().y == bottom_y);
		for (auto x = bat->position().x; x < bat->position().x + bat->width(); ++x)
			REQUIRE(game.tileMap->blocks[bottom_y * map->width() + x] == 11);
	}

	SECTION("Move Bat to the left decrements x position and updates map") {
		auto prevX = bat->position().x;
		--bat->position().x;
		bat->update();
		REQUIRE(bat->position().x == prevX - 1);
		for (auto x = bat->position().x; x < bat->position().x + bat->width(); ++x)
			REQUIRE(map->blocks[bottom_y * map->width() + x] == 11);
		REQUIRE(map->blocks[bat->position().y * map->width() + prevX + bat->width() - 1 ] == 0);
	}

	SECTION("Move Bat to the right increments x position and updates map") {
		auto prevX = bat->position().x;
		++bat->position().x;
		bat->update();
		REQUIRE(bat->position().x == prevX + 1);
		for (auto x = bat->position().x; x < bat->position().x + bat->width(); ++x)
			REQUIRE(map->blocks[bottom_y * map->width() + x] == 11);
		REQUIRE(map->blocks[bat->position().y * map->width() + prevX] == 0);
	}
//	SECTION("Bat Cannot move beyond left wall limits") {
//		bat->position().x = 0;
//		REQUIRE(bat->position().x == 1.0f);
//	}
}

TEST_CASE("Ball Class Assertions") {
	BreakOut game;
	game.OnUserCreate();
	auto &ball = game.ball;
	SECTION("Default position at (0,0)") {
		REQUIRE(ball->position() == olc::vf2d(0.0f, 0.0f));
	}
	SECTION("Default direction is (0,0) vector") {
		REQUIRE(ball->dir() == olc::vf2d(0.0f, 0.0f));
	}
	SECTION("Default radius is 5.5") {
		REQUIRE(ball->radius() == 5.5f);
	}
	SECTION("Default speed is 20") {
		REQUIRE(ball->speed() == 20.0f);
	}

}
