#include <iostream>
#include <string>

int main() {
  std::string n = "ababbaabaaab";
  std::string m = "abaa";

  for (int j = 0; j <= n.size() - m.size(); j++) {
    for (int i = 0; i < m.size() && x[i] == y[i + j]; i++) {
      if (i <= m.size())
        return j;
    }
  }
}