#ifndef ENTITY_H
#define ENTITY_H

class BreakOut;
class Entity {
public:
	virtual ~Entity() = default;
	virtual void update(BreakOut *) = 0;
	virtual void draw(BreakOut *) = 0;
	float x() const { return x_; };
	float y() const { return y_; };
	void setX(float x) { x_ = x; }
	void setY(float y) { y_ = y; }
private:
	float x_ = 0.0f;
	float y_ = 0.0f;
};
#endif /* ifndef ENTITY_H */
