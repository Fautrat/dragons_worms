#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "../../Game/InputHandler.hpp"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "Fireball.h"
#include "PlayerInterface.h"
#include "SFML/Graphics.hpp"
#include <functional>

enum Team
{
    FirstTeam,
    SecondTeam
};

struct Dragon : public Entity
{    
    Dragon()
    {
        AssetManager::get().loadTexture("Player", "assets/Dragon/dragon.png");
        AssetManager::get().loadTexture("Player2", "assets/Dragon/SecondDragon.png");
       

        turnEnding = false;
        hasShoot = false;
        fragmentedShoot = false;
    }

    ~Dragon() = default;

    void initPlayer(Team team) {

        getComponent<Transform>()->scale = sf::Vector2f(0.7f, 0.7f);
        
        addComponent<PlayerInterface>();

        if (team == FirstTeam)
        {
            addComponent<SpriteRenderer>("Player");
		}
        else if(team == SecondTeam)
        {
            addComponent<SpriteRenderer>("Player2");
		}
        addComponent<Rigidbody>(1, false, 0, 2);
        addComponent<Collider2D>(BOX, std::string("Player"));
        initialIndicatorColor = getComponent<SpriteRenderer>()->getSprite()->getColor();
    }

    const int getLife()
    {
        return getComponent<PlayerInterface>()->life;
    }

 

    void takeDamage(int damage)
    {
        getComponent<PlayerInterface>()->applyDamageInterface(damage);
    }

    void connectInput(InputHandler* input)
    {
        input->connect(EInput::MoveRight, [this] {getComponent<Rigidbody>()->moveHorizontal(1); getComponent<SpriteRenderer>()->flipTextureRight(); });
        input->connect(EInput::MoveLeft, [this] {getComponent<Rigidbody>()->moveHorizontal(-1); getComponent<SpriteRenderer>()->flipTextureLeft(); });
        input->connect(EInput::Action, [this]
            {
                const auto fireball = shoot();
                if (fireball)
                    EntityManager::getInstance()->addEntity(fireball);
            });
        input->connect(EInput::Jump, [this] {getComponent<Rigidbody>()->Jump(); });
        input->connect(EInput::SelectWeapon1, [this] {selectWeapon1(); });
        input->connect(EInput::SelectWeapon2, [this] {selectWeapon2(); });
    }

    void setWindLevel(int level)
    {
        windForce.x = level;
    }

    Fireball* shoot()
    {
        if (hasShoot)
            return nullptr;

        /* calcul de direction */
        sf::Vector2f direction = static_cast<sf::Vector2f>(sf::Mouse::getPosition()) - getComponent<Transform>()->position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;
        direction *= 15.f;

        sf::Vector2f newPos (getComponent<Transform>()->position.x, getComponent<Transform>()->position.y );
        if (direction.x <= 0)
            newPos.x -= getComponent<SpriteRenderer>()->getSprite()->getGlobalBounds().width - 1.f;
        else
            newPos.x += getComponent<SpriteRenderer>()->getSprite()->getGlobalBounds().width + 1.f;
        std::function<void()> callback = [this] {endTurn();};
        Fireball* fireball = new Fireball(callback, fragmentedShoot, 20);
        if (direction.x <= 0)
        {
            fireball->getComponent<SpriteRenderer>()->flipTextureLeft();
        }

        fireball->getComponent<Transform>()->moveTo(newPos);
        fireball->getComponent<Rigidbody>()->setVelocity(direction + windForce);
        hasShoot = true;

        return fireball;
    }

    void startTurn()
    {
        getComponent<PlayerInterface>()->setIsPlaying(true);
    }

    void endTurn()
    {
        turnEnding = true;
        getComponent<PlayerInterface>()->setIsPlaying(false);
       
    }

    void selectWeapon1()
    {
        getComponent<PlayerInterface>()->getSpriteIndicator()->setColor(initialIndicatorColor);
        fragmentedShoot = false;
    }

    void selectWeapon2()
    {
        getComponent<PlayerInterface>()->getSpriteIndicator()->setColor(sf::Color::Blue);
        fragmentedShoot = true;
    }

    bool turnEnding;
    sf::Color initialIndicatorColor;
    bool fragmentedShoot;
    bool hasShoot;
    sf::Vector2f windForce = sf::Vector2f(1, 0);
};
