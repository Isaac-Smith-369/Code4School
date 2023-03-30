#include <iostream>

void generateSalesTable() {
  // Create rows
  int S[11][11];
  // Set position (0, 0) to 9
  S[0][0] = 9;

  for (int r = 0; r < 11; r++) {
    for (int c = 0; c < 11; c++) {
      if ((r == 0 && c > 0 || (c == 0 && r > 0))) {
        S[r][c] = 2;
      }
      std::cout << S[r][c] << "\t";
    }
    std::cout << std::endl;
  }
}

int main() { generateSalesTable(); }