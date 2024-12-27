#include "ConfigLoader.h"

// Function definitions
void loadWindowConfig(std::stringstream &ss, int &resolution_x,
                      int &resolution_y, int &framerate) {
  ss >> resolution_x >> resolution_y >> framerate;
  std::cerr << "Window Config: Resolution: " << resolution_x << "x"
            << resolution_y << ", Framerate: " << framerate << std::endl;
}

void loadPlayerConfig(std::stringstream &ss, PlayerConfig &playerConfig) {
  ss >> playerConfig.SR >> playerConfig.CR >> playerConfig.S >>
      playerConfig.FR >> playerConfig.FG >> playerConfig.FB >>
      playerConfig.OR >> playerConfig.OG >> playerConfig.OB >>
      playerConfig.OT >> playerConfig.V;

  std::cerr << "Player Config: "
            << "SR: " << playerConfig.SR << ", "
            << "CR: " << playerConfig.CR << ", "
            << "Speed: " << playerConfig.S << ", "
            << "Fill Color: (" << playerConfig.FR << ", " << playerConfig.FG
            << ", " << playerConfig.FB << "), "
            << "Outline Color: (" << playerConfig.OR << ", " << playerConfig.OG
            << ", " << playerConfig.OB << ", " << playerConfig.OT << "), "
            << "Vertices: " << playerConfig.V << std::endl;
}

void loadFontConfig(std::stringstream &ss, sf::Font &font, sf::Text &text) {
  std::string fontPath;
  ss >> fontPath;

  if (!font.loadFromFile(fontPath)) {
    std::cerr << "Failed to load font: " << fontPath << std::endl;
    return;
  }

  text.setFont(font);
  text.setFillColor(sf::Color::White);
  text.setPosition(10, 10);
  text.setCharacterSize(20);

  std::cerr << "Font Config: " << fontPath << std::endl;
}

void loadEnemyConfig(std::stringstream &ss, EnemyConfig &enemyConfig) {
  ss >> enemyConfig.SR >> enemyConfig.CR >> enemyConfig.SMIN >>
      enemyConfig.SMAX >> enemyConfig.OR >> enemyConfig.OG >> enemyConfig.OB >>
      enemyConfig.OT >> enemyConfig.VMIN >> enemyConfig.VMAX >> enemyConfig.L >>
      enemyConfig.SI;

  std::cerr << "Enemy Config: "
            << "SR: " << enemyConfig.SR << ", "
            << "CR: " << enemyConfig.CR << ", "
            << "Speed Range: (" << enemyConfig.SMIN << ", " << enemyConfig.SMAX
            << "), "
            << "Outline Color: (" << enemyConfig.OR << ", " << enemyConfig.OG
            << ", " << enemyConfig.OB << ", " << enemyConfig.OT << "), "
            << "Vertices Range: (" << enemyConfig.VMIN << ", "
            << enemyConfig.VMAX << "), "
            << "Lifespan: " << enemyConfig.L << ", "
            << "Spawn Interval: " << enemyConfig.SI << std::endl;
}

void loadBulletConfig(std::stringstream &ss, BulletConfig &bulletConfig) {
  ss >> bulletConfig.SR >> bulletConfig.CR >> bulletConfig.S >>
      bulletConfig.FR >> bulletConfig.FG >> bulletConfig.FB >>
      bulletConfig.OR >> bulletConfig.OG >> bulletConfig.OB >>
      bulletConfig.OT >> bulletConfig.V >> bulletConfig.L;

  std::cerr << "Bullet Config: "
            << "SR: " << bulletConfig.SR << ", "
            << "CR: " << bulletConfig.CR << ", "
            << "Speed: " << bulletConfig.S << ", "
            << "Fill Color: (" << bulletConfig.FR << ", " << bulletConfig.FG
            << ", " << bulletConfig.FB << "), "
            << "Outline Color: (" << bulletConfig.OR << ", " << bulletConfig.OG
            << ", " << bulletConfig.OB << ", " << bulletConfig.OT << "), "
            << "Vertices: " << bulletConfig.V << ", "
            << "Lifespan: " << bulletConfig.L << std::endl;
}
