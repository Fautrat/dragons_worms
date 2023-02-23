#pragma once

#include "../../Game/InputHandler.hpp"
#include <sfml/Graphics.hpp>
#include "Component.h"
#include "Entity.h"
#include "RigidBody.h"
#include "SpriteRenderer.h"

class Input : public Component{
public:
	Input(InputHandler* input)
	{
		input->connect(sf::Keyboard::D, [this] {rigidbody->moveHorizontal(1); });
		input->connect(sf::Keyboard::Q, [this] {rigidbody->moveHorizontal(-1);});
		input->connect(sf::Keyboard::N, [this] {entity->shoot(sf::Mouse::getPosition()); });
		input->connect(sf::Keyboard::Space, [this] {rigidbody->Jump(); });
	}

	bool init() override final {
		
		transform = &entity->getComponent<Transform>();
		rigidbody = &entity->getComponent<Rigidbody>();
		if (nullptr != transform && nullptr != rigidbody)
		{
			return true;
		}
		return false;
	}


	~Input()
	{
		delete transform;
		delete rigidbody;
	}

private:
	Transform* transform = nullptr;
	Rigidbody* rigidbody = nullptr;
	//float m_speed = 5.0f;
};