#include <iostream>
#include <string>

const int map_h = 7;  // высота
const int map_w = 20; // ширина

void drawing_map(char map[map_h][map_w]);

class Charcher {
protected:
  int hp;
  int speed;
  short pos_x;
  short pos_y;
};

class Player : public Charcher {
private:
  char sim;

public:
  void moved(char map[map_h][map_w], char move) {
    int dx = 0, dy = 0;

    if (move == 'a')
      dx = -1;
    else if (move == 'd')
      dx = 1;
    else if (move == 'w')
      dy = -1;
    else if (move == 's')
      dy = 1;
    else
      return;

    int new_x = pos_x + dx;
    int new_y = pos_y + dy;

    if (map[new_y][new_x] == '|' || map[new_y][new_x] == '-') {
      return; // стена
    }

    map[new_y][new_x] = sim;
    map[pos_y][pos_x] = '.';
    pos_x = new_x;
    pos_y = new_y;
  }

  Player(char map[map_h][map_w]) : sim('?') {
    pos_x = 1;
    pos_y = 1;
    map[pos_y][pos_x] = sim;
  }
};

int main() {
  char map[map_h][map_w];
  for (int i = 0; i < map_h; i++) {
    for (int j = 0; j < map_w; j++) {
      if (j == 0 || j == map_w - 1) {
        map[i][j] = '|';
      } else if (i == 0 || i == map_h - 1) {
        map[i][j] = '-';
      } else {
        map[i][j] = '.';
      }
    }
  }

  Player sim(map);

  drawing_map(map);

  char buffer;
  while (true) {
    std::cin >> buffer;
    if (buffer == 'e')
      break;
    sim.moved(map, buffer);
    drawing_map(map);
  }
}

void drawing_map(char map[map_h][map_w]) {
  for (int y = 0; y < map_h; y++) {
    for (int x = 0; x < map_w; x++) {
      std::cout << map[y][x];
    }
    std::cout << std::endl;
  }
}
