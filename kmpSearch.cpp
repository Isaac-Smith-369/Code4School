#include <iostream>
#include <string>
#include <vector>

std::string arr[5] = {
    "Ghana (/ˈɡɑːnə/ (listen); Twi: Gaana, Ewe: Gana), officially the Republic of\
Ghana, is a country in West Africa.[9] It abuts the Gulf of Guinea and the\
Atlantic Ocean to the south, sharing borders with Ivory Coast in the west,\
Burkina Faso in the north, and Togo in the east.[10] Ghana covers an area of\
238,535 km2 (92,099 sq mi), spanning diverse biomes that range from coastal\
savannas to tropical rainforests. With nearly 31 million inhabitants(according\
to 2021 census), Ghana is the second-most populous country in West Africa, after Nigeria.[11]",
    "The first permanent state in present-day Ghana was the Bono state of the 11th\
century.[12] Numerous kingdoms and empires emerged over the centuries, of which\
the most powerful were the Kingdom of Dagbon in the north[13] and the Ashanti\
Empire in the south.[14] Beginning in the 15th century, the Portuguese Empire,\
followed by numerous other European powers, contested the area for trading\
rights, until the British ultimately established control of the coast by the\
late 19th century. Following over a century of colonisation, Ghana's current\
borders took shape, encompassing four separate British colonial territories:\
Gold Coast, Ashanti, the Northern",
    "Burkina Faso (UK: /bɜːrˌkiːnə ˈfæsoʊ/, US: /- ˈfɑːsoʊ/ (listen);[11]French:\
[buʁkina faso], Fula: 𞤄𞤵𞤪𞤳𞤭𞤲𞤢 𞤊𞤢𞤧𞤮) is a landlocked country in West Africa with\
an area of 274,200 km2 (105,900 sq mi), bordered by Mali to the northwest, Niger\
to the northeast, Benin to the southeast, Togo and Ghana to the south, and the\
Ivory Coast to the southwest. It has a population of 20,321,378.[12]Previously\
called Republic of Upper Volta (1958–1984), it was renamed Burkina Faso by\
President Thomas Sankara. Its citizens are known as Burkinabè (/bɜːrˈkiːnəbeɪ/\
bur-KEE-nə-beh), and its capital and largest city is Ouagadougou.",
    "The largest ethnic group in Burkina Faso is the Mossi people, who settled the\
area in the 11th and 13th centuries. They established powerful kingdoms such as\
the Ouagadougou, Tenkodogo, and Yatenga. In 1896, it was colonized by the French\
as part of French West Africa; in 1958, Upper Volta became a self-governing\
colony within the French Community. In 1960, it gained full independence with\
Maurice Yaméogo as president. Throughout the decades post independence, the\
country was subject to instability,",
    "Togo (/ˈtoʊɡoʊ/ (listen)), officially the Togolese Republic (French: République\
togolaise), is a country in West Africa. It is bordered by Ghana to the west,\
Benin to the east and Burkina Faso to the north.[8] It extends south to the Gulf\
of Guinea, where its capital, Lomé, is located.[9] It covers about 57,000 square\
kilometres (22,000 square miles) with a population of approximately 8\
million,[10] and has a width of less than 115 km (71 mi) between Ghana andits\
eastern neighbor Benin.[11][12]"};

// Returns a vector of integers that represents the prefix function
std::vector<int> compute_prefix_function(const std::string &pattern) {
  int n = pattern.size();
  std::vector<int> pi(n, 0);
  int j = 0;

  for (int i = 1; i < n; i++) {
    while (j > 0 && pattern[i] != pattern[j]) {
      j = pi[j - 1];
    }
    if (pattern[i] == pattern[j]) {
      j++;
    }
    pi[i] = j;
  }
  return pi;
}

std::vector<int> kmpSearch(const std::string &text,
                           const std::string &pattern) {
  std::vector<int> matches;
  std::vector<int> pi = compute_prefix_function(pattern);
  int n = text.size();
  int m = pattern.size();
  int j = 0;

  for (int i = 0; i < n; i++) {
    while (j > 0 && text[i] != pattern[j]) {
      j = pi[j - 1];
    }
    if (text[i] == pattern[j]) {
      j++;
    }
    if (j == m) {
      matches.push_back(i - m + 1);
      j = pi[j - 1];
    }
  }
  return matches;
}

// Search for a term
std::vector<int> search(std::string text, std::string term) {
  return kmpSearch(text, term);
}

int main() {
  std::string text = "The quick brown fox jumps over the lazy dog";

  // Get suser input
  std::string term;
  std::cout << "Enter a word or a phrase: ";
  getline(std::cin, term);

  // Search for the user's term
  std::vector<int> matches = search(text, term);

  std::cout << "Matches for term " << term << ": " << std::endl;
  for (int i = 0; i < matches.size(); i++) {
    int start = matches[i];
    int end = start + term.length();
    std::cout << matches[i] << " " << std::endl;
    std::string sentence = text.substr(0, start) + "[" +
                           text.substr(start, end - start) + "]" +
                           text.substr(end);
    std::cout << sentence << " " << std::endl;
  }
  std::cout << std::endl;
}
