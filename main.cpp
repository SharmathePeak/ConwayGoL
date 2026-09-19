#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>
using namespace std;

const int x = 50;
const int y = 50;
int grid[y][x];
int buffergrid[y][x];

void init() {
  int r = 5, c = 5; // top-left offset — needs room to fly, place near a corner
  int cells[][2] = {{0, 24}, {1, 22}, {1, 24}, {2, 12}, {2, 13}, {2, 20},
                    {2, 21}, {2, 34}, {2, 35}, {3, 11}, {3, 15}, {3, 20},
                    {3, 21}, {3, 34}, {3, 35}, {4, 0},  {4, 1},  {4, 10},
                    {4, 16}, {4, 20}, {4, 21}, {5, 0},  {5, 1},  {5, 10},
                    {5, 14}, {5, 16}, {5, 17}, {5, 22}, {5, 24}, {6, 10},
                    {6, 16}, {6, 24}, {7, 11}, {7, 15}, {8, 12}, {8, 13}};
  for (auto &p : cells)
    grid[r + p[0]][c + p[1]] = 1;
}

void draw() {
  for (int i = 0; i < y; i++) {
    for (int j = 0; j < x; j++) {
      std::cout << grid[i][j];
    }
    std::cout << endl;
  }
}

int bncells(int i, int j) {
  int nibr = 0;
  if (i < y - 1) {
    if (buffergrid[i + 1][j] == 0)
      nibr += 0;
    else
      nibr += 1;
    // 2
    if (j < x - 1) {
      if (buffergrid[i + 1][j + 1] == 0)
        nibr += 0;
      else
        nibr += 1;
    }
    // 3
    if (j > 0) {
      if (buffergrid[i + 1][j - 1] == 0)
        nibr += 0;
      else
        nibr += 1;
    }
  }
  // 4
  if (j < x - 1) {
    if (buffergrid[i][j + 1] == 0)
      nibr += 0;
    else
      nibr += 1;
  }
  // 5
  if (j > 0) {
    if (buffergrid[i][j - 1] == 0)
      nibr += 0;
    else
      nibr += 1;
  }
  // 6
  if (i > 0) {
    if (buffergrid[i - 1][j] == 0)
      nibr += 0;
    else
      nibr += 1;
    // 7
    if (j < x - 1) {
      if (buffergrid[i - 1][j + 1] == 0)
        nibr += 0;
      else
        nibr += 1;
    }
    // 8
    if (j > 0) {
      if (buffergrid[i - 1][j - 1] == 0)
        nibr += 0;
      else
        nibr += 1;
    }
  }
  return nibr;
}

// Rule 1 revive a cell if 3 neighbours
void revive(int i, int j, int n) {
  if (n == 3) {
    grid[i][j] = 1;
  }
}

// Rule 2 kill a cell if more than 3 or less than 2 neighbours
void kill(int i, int j, int n) {
  if (n > 3 || n < 2) {
    grid[i][j] = 0;
  }
}

// Rule 3 cell will pass to next gen if it has 2 or 3 neighbours
// currently no code
// Total check
void logic() {
  for (int i = 0; i < y; i++) {
    for (int j = 0; j < x; j++) {
      revive(i, j, bncells(i, j));
      kill(i, j, bncells(i, j));
    }
  }
}

int main(void) {
  memset(grid, 0, sizeof(grid));
  init();
  while (true) {
    draw();
    cout << "---" << endl;
    memcpy(buffergrid, grid, sizeof(grid));
    logic();
    this_thread::sleep_for(chrono::milliseconds(100));
  }
  return 0;
}
