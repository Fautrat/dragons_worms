#pragma once

#include "Entity.h"
#include <sfml/Graphics.hpp>
#include "Component.h"
#include <iostream>
#include "../Utils/Vectormath.h"
#include <vector>
#include "SpriteRenderer.h"

constexpr float PI = 3.14f;


class Rigidbody : public Component
{
public:

	Rigidbody() = default;
	Rigidbody(float density, bool isStatic, float restitution, float gravity_scale) : restitution(restitution), density(density), isStatic(isStatic), m_gravity_scale(gravity_scale) {};
	~Rigidbody() = default;

	bool init() override final;

	void update(const float& deltaTime) override final;

	void AddForce(sf::Vector2f amount);
	void setGravity(float newGravity);

	void setMovementSpeed(const float speed);
	void moveHorizontal(int direction);

	void moveTo(sf::Vector2f newPosition);

	void Rotate(float amount);

	void translate(sf::Vector2f v, float rotation);

	void setVelocity(sf::Vector2f value);

	void Jump();

	void landing() { isOnGround = true; }
	sf::Vector2f getVelocity() { return m_velocity; };
	void InitValues(sf::Vector2f position,float mass,float restitution,float area);
	float getInvMass() {return invMass;}
private:
	float gravity =9.81f;
	float invMass = 0;
	sf::Vector2f acceleration;
	sf::Vector2f force;
	float m_gravity_scale = 1.0f;
	float m_speed = 200;
	float forceMagnitude = 25;
	float m_jumpForce = 8.0f;
	float mass = 0;
	float area = 0;
	float radius = 0;
	float width = 0;
	float height = 0;
	float m_rotation = 0;
	sf::Vector2f m_velocity = sf::Vector2f();
	sf::Vector2f position;
	bool isOnGround = true;
	bool isInputMovement = false;
	float tempGravityScale = 0.0f;

public:
	bool onCollision = false;
	bool transformUpdateRequired;
	float density;
	bool isStatic = true;
	float restitution;
	float getDensity() { return density; };
	float getMass() { return mass; };
	float getRestitution() { return restitution;};
	float getArea() { return area; };
	bool getIsStatic() { return isStatic; };
	float getRadius() { return radius; };
	float getWidth() { return width; };
	float getHeight() { return height; };
};