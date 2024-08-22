#pragma once
#include<array>

//bool map_collision(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, Cell i_map[MAP_WIDTH][MAP_HEIGHT]);
bool map_collision(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);
