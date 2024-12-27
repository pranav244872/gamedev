#include "Game.h"
#include "Component.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cmath>
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
    return;
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
      std::cerr << "Window Config: " << "Resolution: " << resolution_x << "x"
                << resolution_y << ", Framerate: " << framerate << std::endl;

      // When the first word is Player fill the player Config
    } else if (firstWord == "Player") {
      ss >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >>
          m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB >>
          m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >>
          m_playerConfig.OT >> m_playerConfig.V;

      std::cerr << "Player Config: "
                << "SR: " << m_playerConfig.SR << ", "
                << "CR: " << m_playerConfig.CR << ", "
                << "Speed: " << m_playerConfig.S << ", "
                << "Fill Color: (" << m_playerConfig.FR << ", "
                << m_playerConfig.FG << ", " << m_playerConfig.FB << "), "
                << "Outline Color: (" << m_playerConfig.OR << ", "
                << m_playerConfig.OG << ", " << m_playerConfig.OB << ", "
                << m_playerConfig.OT << "), "
                << "Vertices: " << m_playerConfig.V << std::endl;

      // When the first word is Font set font to read
    } else if (firstWord == "Font") {
      std::string font;
      ss >> font;
      m_font.loadFromFile(font);
      m_text.setFont(m_font);
      m_text.setFillColor(sf::Color::White);
      m_text.setPosition(10, 10);
      m_text.setCharacterSize(20);
      std::cerr << "Font Config: " << font << std::endl;

      // When the first word is Enemy fill the player Config;
    } else if (firstWord == "Enemy") {
      ss >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >>
          m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG >>
          m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >>
          m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;

      std::cerr << "Enemy Config: "
                << "SR: " << m_enemyConfig.SR << ", "
                << "CR: " << m_enemyConfig.CR << ", "
                << "Speed Range: (" << m_enemyConfig.SMIN << ", "
                << m_enemyConfig.SMAX << "), "
                << "Outline Color: (" << m_enemyConfig.OR << ", "
                << m_enemyConfig.OG << ", " << m_enemyConfig.OB << ", "
                << m_enemyConfig.OT << "), "
                << "Vertices Range: (" << m_enemyConfig.VMIN << ", "
                << m_enemyConfig.VMAX << "), "
                << "Lifespan: " << m_enemyConfig.L << ", "
                << "Spawn Interval: " << m_enemyConfig.SI << std::endl;

    } else if (firstWord == "Bullet") {
      ss >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >>
          m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB >>
          m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >>
          m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;

      std::cerr << "Bullet Config: "
                << "SR: " << m_bulletConfig.SR << ", "
                << "CR: " << m_bulletConfig.CR << ", "
                << "Speed: " << m_bulletConfig.S << ", "
                << "Fill Color: (" << m_bulletConfig.FR << ", "
                << m_bulletConfig.FG << ", " << m_bulletConfig.FB << "), "
                << "Outline Color: (" << m_bulletConfig.OR << ", "
                << m_bulletConfig.OG << ", " << m_bulletConfig.OB << ", "
                << m_bulletConfig.OT << "), "
                << "Vertices: " << m_bulletConfig.V << ", "
                << "Lifespan: " << m_bulletConfig.L << std::endl;
    }
  }

  m_window.create(sf::VideoMode(resolution_x, resolution_y), "SFML");
  m_window.setFramerateLimit(framerate);

  spawnPlayer();
}

void Game::sMovement() {
  for (auto e : m_entities.getEntities()) {
    if (e->tag() == "player") {
      if (e->cInput->up && e->cInput->left) {
        e->cTransform->pos += Vec2(-m_playerConfig.S, -m_playerConfig.S);
      } else if (e->cInput->up && e->cInput->right) {
        e->cTransform->pos += Vec2(m_playerConfig.S, -m_playerConfig.S);
      } else if (e->cInput->down && e->cInput->left) {
        e->cTransform->pos += Vec2(-m_playerConfig.S, m_playerConfig.S);
      } else if (e->cInput->down && e->cInput->right) {
        e->cTransform->pos += Vec2(m_playerConfig.S, m_playerConfig.S);
      } else if (e->cInput->up) {
        e->cTransform->pos.y -= m_playerConfig.S;
      } else if (e->cInput->down) {
        e->cTransform->pos.y += m_playerConfig.S;
      } else if (e->cInput->left) {
        e->cTransform->pos.x -= m_playerConfig.S;
      } else if (e->cInput->right) {
        e->cTransform->pos.x += m_playerConfig.S;
      }
    } else {
      e->cTransform->pos += e->cTransform->velocity;
    }
  }
}

void Game::sUserInput() {
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
      case sf::Keyboard::P:   // "P" key to pause/unpause
        m_paused = !m_paused; // Toggle the paused state
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
  for (auto e : m_entities.getEntities()) {
    if (e->cLifespan) {
      if (e->cLifespan->remaining == 0) {
        e->destroy();
      } else {
        e->cLifespan->remaining -= 1;
      }
    }
  }
}

void Game::sRender() {
  m_window.clear();

  for (auto e : m_entities.getEntities()) {
    // Set the position of the shape
    e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

    // Update rotation based on angle
    e->cTransform->angle += 1.0f;

    // If the entity has a lifespan component, handle transparency
    if (e->cLifespan) {
      // Calculate the remaining lifespan
      float remainingLifespan = static_cast<float>(e->cLifespan->remaining);
      float totalLifespan = static_cast<float>(e->cLifespan->total);

      // Calculate alpha based on the remaining lifespan (fade out)
      float alpha = std::max(0.0f, remainingLifespan / totalLifespan) * 255;

      // Set the alpha value for transparency on the fill color
      e->cShape->fillColor.a = static_cast<sf::Uint8>(alpha);
      e->cShape->circle.setFillColor(e->cShape->fillColor);

      // Set the alpha value for transparency on the outline color
      e->cShape->outlineColor.a = static_cast<sf::Uint8>(alpha);
      e->cShape->circle.setOutlineColor(e->cShape->outlineColor);
    }

    // Apply rotation to the shape
    e->cShape->circle.setRotation(e->cTransform->angle);

    // Draw the shape to the window
    m_window.draw(e->cShape->circle);
  }
  m_text.setString(std::to_string(m_score));
  if (m_paused) {
    sf::Text paused("Paused", m_font, 50);
    paused.setStyle(sf::Text::Bold);
    paused.setFillColor(sf::Color::White);
    paused.setPosition((float)m_window.getSize().x / 2 - 50,
                       (float)m_window.getSize().y / 2 - 50);
    m_window.draw(paused);
  }

  m_window.draw(m_text);
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
  // Check for border collisions
  for (auto e : m_entities.getEntities()) {
    const auto &pos = e->cTransform->pos;
    const float radius = e->cCollision->radius;
    const sf::Vector2u &windowSize = m_window.getSize();

    // Handle player border collisions
    if (e->tag() == "player") {
      // Check right border
      if ((pos.x + radius) > windowSize.x) {
        e->cInput->right = false;
      }
      // Check bottom border
      if ((pos.y + radius) > windowSize.y) {
        e->cInput->down = false;
      }
      // Check left border
      if ((pos.x - radius) < 0) {
        e->cInput->left = false;
      }
      // Check top border
      if ((pos.y - radius) < 0) {
        e->cInput->up = false;
      }
    } else {
      // Handle border collisions for other entities (e.g., bullets, enemies)
      // Check right/left borders
      if ((pos.x + radius) > windowSize.x || (pos.x - radius) < 0) {
        e->cTransform->velocity.x = -e->cTransform->velocity.x;
      }

      // Check bottom/top borders
      if ((pos.y + radius) > windowSize.y || (pos.y - radius) < 0) {
        e->cTransform->velocity.y = -e->cTransform->velocity.y;
      }
    }
  }

  // Check for entity collisions (bullet vs. enemy)
  for (auto e : m_entities.getEntitiesByTag("enemy")) {
    const auto &ePos = e->cTransform->pos;
    for (auto b : m_entities.getEntitiesByTag("bullet")) {
      const auto &bPos = b->cTransform->pos;

      // Check if the bullet and enemy collide using distance squared to avoid
      // sqrt calculation
      float dx = bPos.x - ePos.x;
      float dy = bPos.y - ePos.y;
      float distanceSquared = dx * dx + dy * dy;

      float combinedRadius = b->cCollision->radius + e->cCollision->radius;
      if (distanceSquared <= combinedRadius * combinedRadius) {
        b->destroy();
        spawnSmallEnemies(e);
        m_score += e->cScore->score;
        e->destroy();
      }
    }
    // Check if the enemy collides with the player
    const auto &playerPos = m_player->cTransform->pos;
    float playerDx = ePos.x - playerPos.x;
    float playerDy = ePos.y - playerPos.y;
    float playerDistanceSquared = playerDx * playerDx + playerDy * playerDy;

    float playerCombinedRadius =
        e->cCollision->radius + m_player->cCollision->radius;
    if (playerDistanceSquared <= playerCombinedRadius * playerCombinedRadius) {
      // Handle the collision between the player and the enemy
      m_player
          ->destroy(); // Example of player destruction, you can customize it
      spawnPlayer();
    }
  }
  // Repeat for "smallEnemy"
  for (auto e : m_entities.getEntitiesByTag("smallEnemy")) {
    // Process small enemy (similar to "enemy")
    const auto &ePos = e->cTransform->pos;
    // Check for bullet collision (bullet vs. small enemy)
    for (auto b : m_entities.getEntitiesByTag("bullet")) {
      const auto &bPos = b->cTransform->pos;

      // Check if the bullet and small enemy collide
      float dx = bPos.x - ePos.x;
      float dy = bPos.y - ePos.y;
      float distanceSquared = dx * dx + dy * dy;

      float combinedRadius = b->cCollision->radius + e->cCollision->radius;
      if (distanceSquared <= combinedRadius * combinedRadius) {
        b->destroy();
        m_score += e->cScore->score;
        e->destroy();
      }
    }
  }
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
  entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);
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

  enemy->cScore = std::make_shared<CScore>(randomSides);
  enemy->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
  // Record the spawn time of the most recent enemy
  m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity) {
  const auto &mainPos = entity->cTransform->pos;
  float mainAngle = entity->cTransform->angle;
  const auto &mainVelocity = entity->cTransform->velocity;

  // Get the number of vertices (used as the number of smaller enemies to spawn)
  int numVertices = entity->cShape->circle.getPointCount();

  // Size of the smaller enemies (smaller than the main enemy)
  float smallerEnemySize = 0.50 * m_enemyConfig.SR;

  // Spawn each smaller enemy
  for (int i = 0; i < numVertices; i++) {
    // Calculate the direction of angle for each smaller enemy
    float angleOffset = mainAngle + (i * 360.0f / numVertices);

    // Calculate the direction based on the angle of the smaller enemy
    Vec2 direction;
    direction.x = std::cos(angleOffset * M_PI / 180.0f);
    direction.y = std::sin(angleOffset * M_PI / 180.0f);

    // Normalize the direction vector
    direction.normalize();

    // Now, scale the direction of the magitude of the main entity's velocity
    direction *= mainVelocity.length();

    // Create the smaller enemy entity
    auto smallerEnemy = m_entities.addEntity("smallEnemy");

    // Initialize the smaller enemy's transform component
    smallerEnemy->cTransform =
        std::make_shared<CTransform>(mainPos, direction, 0);

    // Initialize the smaller enemy's shape with smaller size
    smallerEnemy->cShape = std::make_shared<CShape>(
        smallerEnemySize, numVertices, entity->cShape->fillColor,
        entity->cShape->outlineColor, m_enemyConfig.OT);

    // Initialize the Lifespan component
    smallerEnemy->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);

    // Initialize the cScore component
    smallerEnemy->cScore = std::make_shared<CScore>(numVertices * 2);

    smallerEnemy->cCollision = std::make_shared<CCollision>(m_enemyConfig.SR);
  }
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &target) {
  // Create a new bullet entity
  auto bullet = m_entities.addEntity("bullet");

  // Calculate the velocity vector from the player to the target
  Vec2 direction = entity->cTransform->pos - target;
  direction.normalize();
  Vec2 velocity = direction * m_bulletConfig.S;

  // Initialize the bullet's transform component with the player's position
  bullet->cTransform = std::make_shared<CTransform>(
      Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y), velocity, 0);

  bullet->cShape = std::make_shared<CShape>(
      m_bulletConfig.SR, m_bulletConfig.V,
      sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
      sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
      m_bulletConfig.OT);

  bullet->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
  bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);
}

void Game::run() {
  // TODO: add pause functionality in here
  // some systems should function while paused(rendering)
  // some systems shouldn't (movement/input)
  while (m_running) {

    sLifespan();
    sEnemySpawner();
    sUserInput();
    sRender();

    if (m_paused) {
      continue;
    }

    sCollision();
    m_entities.update();
    sMovement();

    // increment the current frame
    // may need to be moved when pause implemented
    m_currentFrame++;
  }
}
