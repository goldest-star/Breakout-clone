#ifndef BAT_PHYSICS_COMPONENT
#define BAT_PHYSICS_COMPONENT

#include "PhysicsComponent.h"
#include "GameObject.h"
#include "World.h"

class BatPhysicsComponent : public PhysicsComponent {
	void update(GameObject &bat, const olc::PixelGameEngine & pge, World &world) override;
};
#endif /* ifndef BAT_PHYSICS_COMPONENT */
