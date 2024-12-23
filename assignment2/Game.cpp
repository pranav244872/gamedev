#include "Game.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

Game::Game(const std::string &config) { init(config); }

void Game::init(const std::string &path) {
  // TODO: read in config file here
  // use the premade PlayerConfig, EnemyConfig, BulletConfig variables
  // set up default window parameters
  m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
  m_window.setFramerateLimit(60);

  spawnPlayer();
}

void Game::setPaused(bool paused) {
  // TODO
}

void Game::sMovement() {
  //  TODO: implement all entity movement in this function
  //  you should read the m_player->cInput component to determine if the player
  //  is moving

  // Sample movement speed update
  m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
  m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
}

void Game::sUserInput() {
  // TODO:: handle user input here
  // note that you should only be setting the player's input component variable
  // here you should not implement the player;rs movement logic here the
  // movement system will read the variables you set in this function

  sf::Event event;
  while (m_window.pollEvent(event)) {
    // this event triggers when the window is closed
    if (event.type == sf::Event::Closed) {
      m_running = false;
    }

    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
      case sf::Keyboard::W:
        std::cout << "W key pressed" << std::endl;
        // TODO : set player's input component "up" variable to true
        break;
      default:
        break;
      }
    }

    // this event is triggered when a key is released
    if (event.type == sf::Event::KeyReleased) {
      switch (event.key.code) {
      case sf::Keyboard::W:
        std::cout << "W key Released" << std::endl;
        // TODO : set player's input component "up" variable to true
        break;
      default:
        break;
      }
    }

    if (event.type == sf::Event::KeyReleased) {
      switch (event.key.code) {
      case sf::Keyboard::W:
        std::cout << "W key Released" << std::endl;
        // TODO : set player's input component "up" variable to true
        break;
      default:
        break;
      }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
      switch (event.mouseButton.button) {
      case sf::Mouse::Left:
        std::cout << "Left Mouse Button Pressed at" << event.mouseButton.x
                  << "," << event.mouseButton.y << std::endl;
        spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
        break;
      default:
        break;
      }
    }
  }
}

void Game::sLifespan() {
  // TODO: implement all lifespan functionality
}

void Game::sRender() {
  // TODO:: change the code below to draw ALL of the entiteis
  // sample drawing of the player Entity tthat we have created
  m_window.clear();

  // set the position of the shape based on the entity's transform->pos
  m_player->cShape->circle.setPosition(m_player->cTransform->pos.x,
                                       m_player->cTransform->pos.y);
  // set the rotation of the shape based on the entity's transform->angle
  m_player->cTransform->angle += 1.0f;
  m_player->cShape->circle.setRotation(m_player->cTransform->angle);

  // draw the entity's sf::CircleShape
  m_window.draw(m_player->cShape->circle);

  m_window.display();
}

void Game::sEnemySpawner() {
  // TODO: code which implements enemy spawning should go here
  //
  // (use m_currentFrame - m_lastEnemySpawnTime) to determine
  // how long it has been since the last enemy spawned
}

void Game::sCollision() {
  // TODO: implement all proper collisions between entities
  // be sure to use the collision radius, Not the shape radius
}

// respawn the player in the middle of the screen
void Game::spawnPlayer() {
  // TODO: Finish adding all properties of the player with the correct values
  // from the config

  // We create every entity by calling EntityManager.addEntity(tag)
  // This returns a std::shared_ptr<Entity>, so we use 'auto' to save typing
  auto entity = m_entities.addEntity("player");

  // Give this entity a Transform so it spawns at 200,00 with velocity (1, 1)
  // and angle 0
  entity->cTransform =
      std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0);

  // The entities shape will have radius 32, 8 sides, dark gray fill and red
  // outline of thickness 4
  entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10),
                                            sf::Color(255, 0, 0), 4.0f);

  // Add an input component to the player so that we can use inputs
  entity->cInput = std::make_shared<CInput>();

  // Since we want this Entity to be our player, set our Game's player
  // variable to be this Entity This goes slightly against the EntityManager
  // paradigm,, but we use to player so much its worth it
  m_player = entity;
}

// spawn an enemy at a random location on the screen
void Game::spawnEnemy() {
  // TODO: make sure the enemy is spawned properly with the m_enemyConfig
  // variables
  //  the enemy must be spawned completely within the bounds of the window
  //

  // record when the most recent enemy was spawned
  m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity) {
  // TODO: spawn small enemies at the location of the input enemy else {
  // when we create the smaller enemy, we have to read the values of the
  // original enemy
  // - spawn a number of small enemies equal to the vertices of the original
  // enemy
  // - set each small enemy to the same color as the original, half the size
  // - small enemies are worth double points of the original enemy
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &target) {
  // TODO: implement the spawning of a bullet which travels towards target
  // - bullet speed is given as a scalar speed
  // - you must set the velocity using formula in notes
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) {
  // TODO: implement your onw special weapon spawning here
}
void Game::run() {
  // TODO: add pause functionality in here
  // some systems should function while paused(rendering)
  // some systems shouldn't (movement/input)
  while (m_running) {
    m_entities.update();

    sEnemySpawner();
    sMovement();
    sCollision();
    sUserInput();
    sRender();

    // increment the current frame
    // may need to be moved when pause implemented
    m_currentFrame++;
  }
}
