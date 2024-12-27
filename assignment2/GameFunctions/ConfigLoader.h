#pragma once
#include "../Game.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Function declarations
void loadWindowConfig(std::stringstream &ss, int &resolution_x,
                      int &resolution_y, int &framerate);
void loadPlayerConfig(std::stringstream &ss, PlayerConfig &playerConfig);
void loadFontConfig(std::stringstream &ss, sf::Font &font, sf::Text &text);
void loadEnemyConfig(std::stringstream &ss, EnemyConfig &enemyConfig);
void loadBulletConfig(std::stringstream &ss, BulletConfig &bulletConfig);
