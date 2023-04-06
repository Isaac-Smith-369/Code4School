#include <bits/utility.h>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

int getRandomNumber(int range) { return rand() % range; }

std::string getRandomLetters(std::tuple<int, int> range, bool upCase = true) {
  std::string str = "";
  int rlen =
      rand() % (std::get<1>(range) - std::get<0>(range)) + std::get<0>(range);
  if (upCase) {
    for (int i = 0; i <= rlen; i++) {
      str += (char)(rand() % 26 + 65);
    }
  } else {
    for (int i = 0; i <= rlen; i++) {
      str += (char)(rand() % 26 + 97);
    }
  }

  return str;
}

template <typename T> int get_tuple_size(const T &tuple) {
  return std::tuple_size<T>::value;
}

void printMainTable() {
  // First column: unique random numbers
  // Second column: random alphabets
  // Third column: random numbers
  std::vector<std::tuple<int, std::string, int>> P;

  int genNums[10] = {0};

  for (int i = 0; i < P.size(); i++) {
    if (i % 2 == 0) {
      int rnum = getRandomNumber(10);
      while (genNums[rnum] == 1) {
        rnum = getRandomNumber(10);
      }
      genNums[rnum] = 1;
      P.emplace_back(std::make_tuple(
          rnum, getRandomLetters(std::make_tuple(6, 10)), getRandomNumber(10)));
    } else {
      P.emplace_back(std::make_tuple(getRandomNumber(10),
                                     getRandomLetters(std::make_tuple(6, 10)),
                                     getRandomNumber(10)));
    }
  }

  std::cout << "----------"
            << " P "
            << "----------" << std::endl;

  auto lo = P[0];
  std::cout << get_tuple_size(lo) << std::endl;

  // for (int k = 0; k < P.size(); k++) {
  //   for (std::size_t i = 0; i < std::tuple_size<int, int,>::value; ) {
  //   std::cout << " | " << P[k] << "\t";
  //   }
  // }
  // std::cout << std::endl;
}

void printAuxTable(int tableNum) {
  // First column: unique random numbers
  // Second column: random alphabets
  // Third column: random numbers
  int S[10][3];

  // compute the size of the parent and child arrays
  int sizeP = (sizeof(S) / sizeof(int)) / (sizeof(S[0]) / sizeof(int));
  int sizeC = (sizeof(S[0]) / sizeof(int));

  for (int i = 0; i < sizeP; i++) {
    for (int j = 0; j < sizeC; j++) {
      S[i][j] = getRandomNumber(10);
    }
  }

  std::cout << "----------"
            << " S " << tableNum << " "
            << "----------" << std::endl;

  for (int k = 0; k < sizeP; k++) {
    for (int l = 0; l < sizeC; l++) {
      std::cout << " | " << S[k][l] << "\t";
    }

    std::cout << std::endl;
  }
}

void printLastTable() {
  // First column: unique random numbers
  // Second column: random alphabets
  // Third column: random numbers
  std::vector<std::pair<int, std::string>> vec;

  std::string fruits[10] = {
      "Apple", "Banana", "Cherry",        "Durian", "Elderberry",
      "Fig",   "Grape",  "Juniper Berry", "Kiwi",   "Lychee",
  };

  for (int i = 0; i < 10; i++) {
    vec.push_back(std::make_pair(getRandomNumber(10), fruits[i]));
  }
  std::cout << "----------"
            << " I "
            << "----------" << std::endl;
  for (int j = 0; j < vec.size(); j++) {
    std::cout << " | " << vec[j].first << "    "
              << " | " << vec[j].second << std::endl;
  }
}

int main() {
  // Seed the RNG
  srand(time(0));
  printMainTable();
  // for (int i = 0; i < 3; i++) {
  //   printAuxTable(i + 2);
  //   std::cout << std::endl;
  // }
  // printLastTable();

  // std::string str = getRandomLetters(std::make_tuple(6, 10));
  // std::cout << str << std::endl;
  return 0;
}