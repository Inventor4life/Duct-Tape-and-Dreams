#pragma once
class Physics
{
public:

	Physics() {
		ground = 700.0f;
		gravity = (981.0f * 3);
		velocity = 0.f;
	}

	const float getGround() { return ground; }
	const float getGravity() { return gravity; }
	const float getVelocity() { return velocity; }

	void setGround(float n) { ground = n; }
	void setGravity(float n) { gravity = n; }
	void setVelocity(float n) { velocity = n; }

private:
	double ground;
	double gravity;
	float velocity;
};

