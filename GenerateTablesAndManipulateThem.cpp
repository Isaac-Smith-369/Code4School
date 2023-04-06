#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

typedef std::vector<std::vector<int>> SalesTable;

template <typename T1, typename T2, typename T3> struct Row {
  T1 c1;
  T2 c2;
  T3 c3;

  Row(T1 cell1, T2 cell2, T3 cell3) {
    c1 = cell1;
    c2 = cell2;
    c3 = cell3;
  }

  int size() { return 3; }

  int getId() { return c1; }
};

template <typename T1, typename T2, typename T3> struct Table {
  std::string name = "Untitled";
  std::vector<Row<T1, T2, T3>> table;

  Table(std::string tName) { name = tName; }

  void addRow(Row<T1, T2, T3> row) { table.emplace_back(row); }

  Row<T1, T2, T3> getRow(int index) { return table[index]; }

  std::string toString() {
    std::stringstream out;
    out << "-------------------- [ " << name << " ] --------------------"
        << "\n";
    for (Row<T1, T2, T3> row : table) {
      out << "|\t" << row.c1 << "\t";
      out << "|\t" << row.c2 << "\t";
      out << "|\t" << row.c3 << "\n";
    }
    out << "\n";
    std::string res = out.str();
    return res;
  }

  void print() {
    std::string str = toString();
    std::cout << str << std::endl;
  }

  std::string toCSV() {
    std::stringstream out;
    out << "col 1, col 2, col 3"
        << "\n";
    for (Row<T1, T2, T3> row : table) {
      out << row.c1 << ", ";
      out << row.c2 << ", ";
      out << row.c3;
      out << "\n";
    }
    out << "\n";
    std::string res = out.str();
    return res;
  }

  // Write tables to a file
  bool save(std::string fName = "tables", bool csv = false,
            bool append = false) {
    std::ofstream doc;
    std::string file;
    if (csv) {
      file = fName + ".csv";
    } else {
      file = fName + ".txt";
    }

    // Append the table to an existing file or create a new file and add the
    // table
    if (append) {
      doc.open(file, std::ios::app);
    } else {
      doc.open(file);
    }

    if (doc.fail()) {
      std::cout << "Failed to open file\n";
      return false;
    }

    if (csv) {
      doc << toCSV();
    } else {
      doc << toString();
    }
    doc.close();
    return true;
  }
};

// Aliases for convenience
typedef Table<int, int, int> STable;
typedef Table<int, std::string, int> PTable;
typedef Table<int, std::string, int> ITable;

struct Sales {
  SalesTable salesTable;

  void generateSalesTable(STable &store) {
    for (int r = 0; r < 11; r++) {
      salesTable.emplace_back(std::vector<int>());
      for (int c = 0; c < 11; c++) {
        salesTable[r].push_back(0);
        if (r == 0 && c > 0) {
          // Get item ids from the store
          salesTable[r][c] = store.getRow(c - 1).c3;
        }
        if (c == 0 && r > 0) {
          // Get user ids from the store
          salesTable[r][c] = store.getRow(r - 1).c2;
        }
      }
    }
    salesTable[0][0] = 99;
  }

  void simulatePurchase(STable &store) {
    for (int r = 0; r < 11; r++) {
      for (int c = 0; c < 11; c++) {
        if (r > 0 && c > 0) {
          auto item = store.getRow(c - 1);
          if (salesTable[r][0] == item.c2 && salesTable[0][c] == item.c3) {
            salesTable[r][c] = 1;
          }
        }
      }
    }
  }

  void getMoneySpentInShop(STable &store, PTable &customer, ITable &items) {
    int total = 0;
    for (int i = 0; i < 10; i++) {
      auto row = store.getRow(i);
      for (int j = 0; j < 10; j++) {
        auto cus = customer.getRow(j);
        if (row.c2 == cus.c1) {
          for (int k = 0; k < 10; k++) {
            auto item = items.getRow(k);
            if (row.c3 == item.c1) {
              total += item.c3;
            }
          }
        }
      }
    }
    std::cout << "Total: "
              << "GHC " << total << std::endl;
  }

  void getTotalSales(STable &store, ITable &items) {
    int total = 0;
    for (int i = 0; i < 10; i++) {
      auto row = store.getRow(i);
      for (int j = 0; j < 10; j++) {
        auto item = items.getRow(j);
        if (row.c3 == item.c1) {
          total += item.c3;
        }
      }
    }
    std::cout << "Total sales: "
              << "GHC " << total << std::endl;
  }

  void getSalesPerItem(STable &store, ITable &items) {
    std::vector<std::pair<int, int>> itemSales;
    for (int i = 0; i < 10; i++) {
      auto row = store.getRow(i);
      for (int j = 0; j < 10; j++) {
        auto item = items.getRow(j);
        if (row.c3 == item.c1) {
          itemSales.emplace_back(std::make_pair(item.c1, item.c3));
        }
      }
    }

    for (auto it : itemSales) {
      std::cout << "Total sales for " << it.first << ": "
                << "GHC " << it.second << std::endl;
    }
  }

  void printSalesTable() {
    for (auto sales : salesTable) {
      for (int i = 0; i < sales.size(); i++) {
        std::cout << sales[i] << "\t";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
};

std::string readFile(std::string fName) {
  std::stringstream out;
  std::string file = fName + ".txt";
  std::ifstream doc(file);
  std::string line;

  if (!doc.is_open()) {
    std::cout << "Error opening file\n";
    return "";
  }

  // Push all lines intp the string stream
  while (getline(doc, line)) {
    out << line << "\n";
  }
  doc.close();

  return out.str();
}

int getRandomNumber(int range) { return (rand() % range) + 1; }

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

int main() {
  srand(time(0));

  // Create first table (int, string, int)
  Table<int, std::string, int> customers("Customers");
  int genNums[10] = {0};
  for (int i = 0; i < 10; i++) {
    // Get unique random number
    int rnum = getRandomNumber(10);
    while (genNums[rnum] == 1) {
      rnum = getRandomNumber(10);
    }
    genNums[rnum] = 1;
    int rnd = rand() % (30 - 20) + 20;
    customers.addRow(Row<int, std::string, int>(
        rnum, getRandomLetters(std::make_tuple(6, 10)), rnd));
  }

  // Create 3 tables (int, int, int)
  std::vector<STable> stores;
  for (int i = 0; i < 3; i++) {
    std::stringstream name;
    name << "Store " << i + 1;
    STable store(name.str());
    for (int i = 0; i < 10; i++) {
      store.addRow(Row<int, int, int>(getRandomNumber(10), getRandomNumber(10),
                                      getRandomNumber(10)));
    }
    stores.emplace_back(store);
  }

  // Create last table (int, string, int)
  Table<int, std::string, int> items("Items");
  std::string fruits[10] = {
      "Apple", "Banana", "Cherry", "Durian", "Ephidra",
      "Fig",   "Grape",  "Hazel",  "Kiwi",   "Lychee",
  };
  for (int i = 0; i < 10; i++) {
    items.addRow(Row<int, std::string, int>(getRandomNumber(10), fruits[i],
                                            getRandomNumber(10)));
  }

  // Generate sales tables for s1, s2, and s3
  STable store1 = stores[0];
  STable store2 = stores[1];
  STable store3 = stores[2];
  Sales sales1;
  Sales sales2;
  Sales sales3;
  sales1.generateSalesTable(store2);
  sales2.generateSalesTable(store2);
  sales3.generateSalesTable(store3);

  bool exit = false;
  while (!exit) {
    std::cout << "Welcome!\n";
    std::cout << "1. View Table\n";
    std::cout << "2. View All Tables\n";
    std::cout << "3. Save Table\n";
    std::cout << "4. Save All Tables\n";
    std::cout << "5. Load File\n";
    std::cout << "6. Simulate a Purchase\n";
    std::cout << "7. Simulate All Purchases\n";
    std::cout << "8. Show Money Spent in a Shop\n";
    std::cout << "9. Show Money Spent in All Shops\n";
    std::cout << "10. Show Sales Per Item\n";
    std::cout << "11. Show Total Sales For a Store\n";
    std::cout << "12. Show Total Sales For All Stores\n";
    std::cout << "99. Exit\n";

    // Get user's choice
    int choice;
    std::cout << ">> ";
    std::cin >> choice;
    std::cout << std::endl;

    switch (choice) {
    case 1:
      std::cout << "Which table do you wish to view? (p, s, or i): ";
      char choice1;
      std::cin >> choice1;
      if (choice1 == 'p') {
        customers.print();
      } else if (choice1 == 's') {
        for (auto store : stores) {
          store.print();
        }
      } else if (choice1 == 'i') {
        items.print();
      } else {
        std::cout << "Please select either p, s, or i to view.\n";
      }
      break;
    case 2:
      std::cout << "Displaying all tables...\n\n";
      customers.print();
      for (auto store : stores) {
        store.print();
      }
      items.print();
      break;
    case 3: {
      std::cout << "Which table do you wish to save? (p, s, or i): ";
      char choice2;
      std::cin >> choice2;
      std::cout << std::endl;

      std::string name;
      std::cout << "Please provide a name for your file: ";
      std::cin >> name;

      std::cout << "Saving table in " << name << ".txt\n";
      if (choice2 == 'p') {
        customers.save(name, true);
      } else if (choice2 == 's') {
        for (auto store : stores) {
          store.save(name, true, true);
        }
      } else if (choice2 == 'i') {
        items.save(name, true);
      } else {
        std::cout << "Please select either p, s, or i to save.\n";
      }
      break;
    }
    case 4: {
      std::string name;
      std::cout << "Please provide a name for your file: ";
      std::cin >> name;
      std::cout << "Saving all tables in " << name << ".txt\n";
      customers.save(name, true, true);
      for (auto store : stores) {
        store.save(name, true, true);
      }
      items.save(name, true, true);
      break;
    }
    case 5: {
      std::string fName;
      std::cout << "Please provide the name of the file to load: ";
      std::cin >> fName;
      std::cout << "Loading file...\n";
      std::string file = readFile(fName);
      if (file == "") {
        std::cout << "File with mame " << file << ".txt "
                  << "is empty or is not avalable.";
      } else {
        std::cout << "File has been read successfully. Displaying file...\n ";
        std::cout << file << std::endl;
      }
      break;
    }
    case 6:
      std::cout
          << "Which store do you wish to simulate a purchase? (1, 2, or 3): ";
      int choice3;
      std::cin >> choice3;
      std::cout << std::endl;
      if (choice3 == 1) {
        sales1.simulatePurchase(store1);
        std::cout << "Done\n\n";
      } else if (choice3 == 2) {
        sales2.simulatePurchase(store2);
        std::cout << "Done\n\n";
      } else if (choice3 == 3) {
        sales3.simulatePurchase(store3);
        std::cout << "Done\n\n";
      } else {
        std::cout
            << "Please select either 1, 2, or 3 to simulate a purchase.\n";
      }
      break;
    case 7:
      std::cout << "Simulating purchaces in all stores...\n\n";
      sales1.simulatePurchase(store1);
      sales2.simulatePurchase(store2);
      sales3.simulatePurchase(store3);
      std::cout << "Done. Enter 11 or 12 to view the sales table.\n\n";
      break;
    case 8:
      std::cout << "Please select a store.? (1, 2, or 3): ";
      int choice4;
      std::cin >> choice4;
      std::cout << std::endl;
      if (choice4 == 1) {
        sales1.getMoneySpentInShop(store1, customers, items);
      } else if (choice4 == 2) {
        sales2.getMoneySpentInShop(store2, customers, items);
      } else if (choice4 == 3) {
        sales3.getMoneySpentInShop(store3, customers, items);
      } else {
        std::cout << "Please select either 1, 2, or 3 to show money spent in "
                     "shop.\n ";
      }
      break;
    case 9:
      std::cout << "Displaying money spent in all stores...\n\n";
      std::cout << "Store 1\n\n";
      sales1.getMoneySpentInShop(store1, customers, items);
      std::cout << std::endl;
      std::cout << "Store 2\n\n";
      sales2.getMoneySpentInShop(store2, customers, items);
      std::cout << std::endl;
      std::cout << "Store 3\n\n";
      sales3.getMoneySpentInShop(store3, customers, items);
      std::cout << std::endl;

      break;
    case 10:
      std::cout << "Displaying sales per item in all stores...\n\n";
      sales1.getSalesPerItem(store1, items);
      sales2.getSalesPerItem(store2, items);
      sales3.getSalesPerItem(store3, items);
      break;
    case 11:
      std::cout << "Please select a store.? (1, 2, or 3): ";
      int choice6;
      std::cin >> choice6;
      std::cout << std::endl;
      if (choice6 == 1) {
        std::cout << "Displaying all sales...\n\n";
        sales1.printSalesTable();
        sales1.getTotalSales(store1, items);
      } else if (choice6 == 2) {
        std::cout << "Displaying all sales...\n\n";
        sales2.printSalesTable();
        sales2.getTotalSales(store2, items);
      } else if (choice6 == 3) {
        std::cout << "Displaying all sales...\n\n";
        sales3.printSalesTable();
        sales3.getTotalSales(store3, items);
      } else {
        std::cout << "Please select either 1, 2, or 3 to display sales.\n";
      }
      break;
    case 12:
      std::cout << "Displaying all sales for all stores.\n\n";
      // Store 1
      sales1.printSalesTable();
      sales1.getTotalSales(store1, items);
      std::cout << std::endl;

      // Store 2
      sales2.printSalesTable();
      sales2.getTotalSales(store2, items);
      std::cout << std::endl;

      // store 3
      sales2.printSalesTable();
      sales3.getTotalSales(store3, items);
      std::cout << std::endl;
      break;
    case 99:
      std::cout << "Goodbye!";
      exit = true;
      break;
    default:
      std::cout << "Invalid Choice\n";
      break;
    }
  }

  return 0;
}