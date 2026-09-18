#include <cstring>
#include <iostream>
using namespace std;

const int x = 5;
const int y = 5;
int grid[y][x];
void draw() {
  for (int i = 0; i < y; i++) {
    for (int j = 0; j < x; j++) {
      std::cout << grid[i][j];
      j++;
    }
    std::cout << endl;
    i++;
  }
}

int main(void) {
  memset(grid, 0, sizeof(grid));
  int i = 0;
  draw();
  return 0;
}
