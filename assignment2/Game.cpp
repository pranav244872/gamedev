#include "Game.h"
#include "Component.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <fstream>
#include <memory>
#include <random>
#include <sstream>

int generateRandom(int A, int B) {
  // Create a random device and random number generator
  std::random_device rd;
  std::mt19937 gen(rd()); // Mersenne Twister generator
  std::uniform_int_distribution<> dis(
      A, B); // Uniform distribution in range [A, B]

  // Return a random number
  return dis(gen);
}

Game::Game(const std::string &config) { init(config); }

void Game::init(const std::string &path) {
  // read in config file here
  // use the premade PlayerConfig, EnemyConfig, BulletConfig variables
  // set up default window parameters
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "Could not open the config files" << std::endl;
  }

  std::string line;
  int resolution_x, resolution_y, framerate;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string firstWord;

    // Skip empty lines or lines that fail to provide the firstWord
    if (!(ss >> firstWord))
      continue;

    // When the first word is Window assign resolutions;
    if (firstWord == "Window") {
      ss >> resolution_x >> resolution_y >> framerate;
      // When the first word is Player fill the player Config
    } else if (firstWord == "Player") {
      ss >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >>
          m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB >>
          m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >>
          m_playerConfig.OT >> m_playerConfig.V;
      // When the first word is Font set font to read
    } else if (firstWord == "Font") {
      std::string font;
      ss >> font;
      m_font.loadFromFile(font);
      // When the first word is Enemy fill the player Config;
    } else if (firstWord == "Enemy") {
      ss >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >>
          m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG >>
          m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >>
          m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;
    }
  }

  m_window.create(sf::VideoMode(resolution_x, resolution_y), "SFML");
  m_window.setFramerateLimit(framerate);

  spawnPlayer();
}

void Game::setPaused(bool paused) {
  // TODO
}

void Game::sMovement() {
  //  TODO: implement all entity movement in this function
  //  you should read the m_player->cInput component to determine if the player
  //  is moving
  if (m_player->cInput->up && m_player->cInput->left) {
    // Move diagonally up-left
    m_player->cTransform->pos += Vec2(-m_playerConfig.S, -m_playerConfig.S);
  } else if (m_player->cInput->up && m_player->cInput->right) {
    // Move diagonally up-right
    m_player->cTransform->pos += Vec2(m_playerConfig.S, -m_playerConfig.S);
  } else if (m_player->cInput->down && m_player->cInput->left) {
    // Move diagonally down-left
    m_player->cTransform->pos += Vec2(-m_playerConfig.S, m_playerConfig.S);
  } else if (m_player->cInput->down && m_player->cInput->right) {
    // Move diagonally down-right
    m_player->cTransform->pos += Vec2(m_playerConfig.S, m_playerConfig.S);
  } else if (m_player->cInput->up) {
    // Move up
    m_player->cTransform->pos.y -= m_playerConfig.S;
  } else if (m_player->cInput->down) {
    // Move down
    m_player->cTransform->pos.y += m_playerConfig.S;
  } else if (m_player->cInput->left) {
    // Move left
    m_player->cTransform->pos.x -= m_playerConfig.S;
  } else if (m_player->cInput->right) {
    // Move right
    m_player->cTransform->pos.x += m_playerConfig.S;
  } else {
    // Do nothing
  }
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

    // this event is triggered when a key is pressed
    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
      case sf::Keyboard::W:
        m_player->cInput->up = true;
        break;
      case sf::Keyboard::S:
        m_player->cInput->down = true;
        break;
      case sf::Keyboard::A:
        m_player->cInput->left = true;
        break;
      case sf::Keyboard::D:
        m_player->cInput->right = true;
        break;
      default:
        break;
      }
    }

    // this event is triggered when a key is released
    if (event.type == sf::Event::KeyReleased) {
      switch (event.key.code) {
      case sf::Keyboard::W:
        m_player->cInput->up = false;
        break;
      case sf::Keyboard::S:
        m_player->cInput->down = false;
        break;
      case sf::Keyboard::A:
        m_player->cInput->left = false;
        break;
      case sf::Keyboard::D:
        m_player->cInput->right = false;
        break;
      default:
        break;
      }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
      switch (event.mouseButton.button) {
      case sf::Mouse::Left:
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
  if ((m_currentFrame - m_lastEnemySpawnTime) == 120) {
    spawnEnemy();
  } else {
    return;
  }
}

void Game::sCollision() {
  // TODO: implement all proper collisions between entities
  // be sure to use the collision radius, Not the shape radius
}

void Game::spawnPlayer() {
  // Create the player entity
  auto entity = m_entities.addEntity("player");

  // Calculate the spawn position (center of the window)
  Vec2 spawnPosition = Vec2(static_cast<float>(m_window.getSize().x) / 2,
                            static_cast<float>(m_window.getSize().y) / 2);

  // Set up the transform (position, velocity, angle)
  Vec2 velocity = Vec2(m_playerConfig.S, m_playerConfig.S);
  entity->cTransform = std::make_shared<CTransform>(spawnPosition, velocity, 0);

  // Set up the shape (radius, sides, fill color, outline color, outline
  // thickness)
  sf::Color fillColor(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB);
  sf::Color outlineColor(m_playerConfig.OR, m_playerConfig.OG,
                         m_playerConfig.OB);
  entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, 8, fillColor,
                                            outlineColor, m_playerConfig.OT);

  // Add the input component
  entity->cInput = std::make_shared<CInput>();

  // Set this entity as the player in the game
  m_player = entity;
}

// spawn an enemy at a random location on the screen
void Game::spawnEnemy() {
  // Generate random position and speed values
  float randomPosX =
      generateRandom(m_enemyConfig.SR, m_window.getSize().x - m_enemyConfig.SR);
  float randomPosY =
      generateRandom(m_enemyConfig.SR, m_window.getSize().y - m_enemyConfig.SR);
  float randomSpeedX = generateRandom(m_enemyConfig.VMIN, m_enemyConfig.VMAX);
  float randomSpeedY = generateRandom(m_enemyConfig.VMIN, m_enemyConfig.VMAX);
  float randomSides = generateRandom(m_enemyConfig.VMIN, m_enemyConfig.VMAX);

  // Generate random RGB values for the enemy's fill color and outline color
  int randomFillR = generateRandom(0, 255);
  int randomFillG = generateRandom(0, 255);
  int randomFillB = generateRandom(0, 255);

  // Create a new enemy entity
  auto enemy = m_entities.addEntity("enemy");

  // Set the enemy's transformation (position, speed, and rotation)
  Vec2 position(randomPosX, randomPosY);
  Vec2 speed(randomSpeedX, randomSpeedY);
  enemy->cTransform = std::make_shared<CTransform>(position, speed, 0);

  // Set the enemy's shape with randomized properties
  enemy->cShape = std::make_shared<CShape>(
      m_enemyConfig.SR, // radius
      randomSides,      // random number of sides
      sf::Color(randomFillR, randomFillG, randomFillB), // random fill color
      sf::Color(m_enemyConfig.OR, m_enemyConfig.OG,
                m_enemyConfig.OB), // random outline color
      m_enemyConfig.OT             // outline thickness
  );

  // Record the spawn time of the most recent enemy
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
  auto bullet = m_entities.addEntity("bullet");
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
