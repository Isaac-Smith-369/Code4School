/*
1. Place the following above 5 paragraphs into an array of size 5.

2. Write a program to count a character occurrence in each paragraph if a person
enters that character. eg Number of A in each paraph etc.

3. Write a program to count the number of words in each paragraph if a person
searches it. e.g. number of times a word like Ghana occurs.

4. Write a program to rank the paragraphs if a person searches for a word and
that word occurs the most. Let it behaves like google search engine.
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string arr[5] = {
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

void countCharacterOccurence(string paragraphs[5], char character,
                             bool matchCase = true) {
  int count = 0;
  int paragraphNum = 0;

  for (int i = 0; i < 5; i++) {
    count = 0;
    paragraphNum = paragraphNum + 1;
    for (int j = 0; j < paragraphs[i].length(); j++) {

      if (!matchCase) {
        character = tolower(character);
        for (char &c : paragraphs[i]) {
          c = tolower(c);
        }
      }

      if (paragraphs[i][j] == character) {
        count++;
      }
    }
    cout << "The character " << character << " appears " << count
         << " times in paragraph " << paragraphNum << endl;
  }
}

map<int, int> countPhraseOccurence(string paragraphs[5], string phrase,
                                   bool matchCase = true) {
  int count = 0;
  int paragraphNum = 0;
  map<int, int> scores;

  cout << phrase << endl;

  for (int i = 0; i < 5; i++) {

    if (!matchCase) {
      for (char &a : phrase) {
        a = tolower(a);
      }
      for (char &c : paragraphs[i]) {
        c = tolower(c);
      }
    }

    count = 0;
    size_t position = paragraphs[i].find(phrase, 0);

    while (position != string::npos) {
      count++;
      position = paragraphs[i].find(phrase, position + 1);
    }

    scores[paragraphNum] = count;
    paragraphNum++;
    cout << "The word " << phrase << " occurs " << count
         << " times in paragraph " << paragraphNum << endl;
  }

  return scores;
}

void customSwap(pair<int, int> &a, pair<int, int> &b) {
  pair<int, int> temp = a;
  a = b;
  b = temp;
}

vector<pair<int, int>> rankParagraphs(string paragraphs[5], string word) {
  map<int, int> result = countPhraseOccurence(paragraphs, word, false);
  vector<pair<int, int>> vec;

  for (map<int, int>::iterator it = result.begin(); it != result.end(); it++) {
    vec.push_back(make_pair(it->first, it->second));
  }

  // sorting the vector in descending order using insertion sort
  int i, j;
  for (int i = 1; i < vec.size(); i++) {
    j = i;
    while ((j > 0) && (vec[j].second > vec[j - 1].second)) {
      customSwap(vec[j], vec[j - 1]);
      j--;
    }
  }

  return vec;
}

int main() {
  // char ch;
  // cout << "Enter a character: ";
  // cin >> ch;

  string wd;
  cout << "Enter a word or a phrase: ";
  getline(cin, wd);
  // cin >> wd;

  // countCharacterOccurence(arr, ch, false);
  map<int, int> result = countPhraseOccurence(arr, wd, false);

  for (map<int, int>::iterator it = result.begin(); it != result.end(); it++) {
    cout << it->second << endl;
  }

  // vector<pair<int, int>> result = rankParagraphs(arr, wd);

  // for (int i = 0; i < result.size(); i++) {
  //   cout << "Paragraph " << result[i].first + 1 << " : " << result[i].second
  //        << endl;
  // }

  return 0;
}
