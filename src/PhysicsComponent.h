#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "../include/olcPixelGameEngine.h"

class GameObject;
class World;

class PhysicsComponent {
public:
	virtual ~PhysicsComponent() = default;
	virtual void update(GameObject &obj, const olc::PixelGameEngine &pge, World &world) = 0;
};
#endif /* ifndef PHYSICS_COMPONENT_H */
