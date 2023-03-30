#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

typedef std::vector<std::vector<std::string>> ParagraphTokens;
typedef std::vector<std::pair<int, std::vector<int>>> PostingsList;
typedef std::map<std::string, PostingsList> Dictionary;

struct InvertedIndex {
  // A schema-dependent inverted index
  Dictionary dictionary;

  // This function creates a key value pair of the form
  // "hello": [[0, [2, 3]], [3, [5. 6]], [4, [10, 11]], [7, [50, 51]]]
  // Where "hello" is the key and the values are pairs of
  // [paragraph information, [positions within the paragraph]]
  InvertedIndex(ParagraphTokens collection) {
    for (int i = 0; i < collection.size(); i++) {
      std::vector<std::string> inner = collection[i];
      for (int j = 0; j < inner.size(); j++) {
        std::string key = inner[j];
        // Check if entry already exists else create a new entry
        if (dictionary.count(key)) {
          // Check if the paragraph already exists in the dictionary
          auto it =
              std::find_if(dictionary[key].begin(), dictionary[key].end(),
                           [i](const auto &pair) { return pair.first == i; });
          // If the paragraph exists, create an add the occurrence to the vector
          // else create a new pair of key and postings list and add them to the
          // dictionary
          if (it != dictionary[key].end()) {
            dictionary[key][i].second.push_back(j);
          } else {
            dictionary[key].emplace_back(i, std::vector<int>{j});
          }
        } else {
          dictionary[key] = std::vector<std::pair<int, std::vector<int>>>();
          dictionary[key].emplace_back(i, std::vector<int>{j});
        }
      }
    }
  }

  // Remove after testing is done
  void printDictionary() {
    for (auto it = dictionary.begin(); it != dictionary.end(); ++it) {
      std::cout << "---------- " << it->first << " ----------" << std::endl;
      for (auto &pair : it->second) {
        std::cout << "PARAGRAPH: " << pair.first << " ---> ";
        for (auto &vec : pair.second) {
          std::cout << vec << " ";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }
  }

  // Returns the positions of the words in the order they appear in the
  // paragraphs
  void getWordPositions(std::string t) {
    PostingsList vec = dictionary[t];
    for (int i = 0; i < vec.size(); i++) {
      std::cout << "Paragraph: " << vec[i].first + 1 << " "
                << "Position: ";
      for (auto &vec : vec[i].second) {
        std::cout << vec << std::endl;
      }
    }
  }

  // We assume that the `low` value of the postings is <= `current`
  // and the `high` value of postings is > `current`
  int binarySearch(std::string t, int low, int high, int current) {
    // "the" : [2, 3, 5, 6, 8, 10]
    while ((high - low) > 1) {
      int mid = low + (high - low) / 2;
      if (dictionary[t].at(mid).second <= current) {
        low = mid;
      } else {
        high = mid;
      }
    }
    return high;
  }

  // Returns the first position at which the term `t` occurs in the
  // collection
  int first(std::string t) { return dictionary[t].front().second.front(); }

  // Returns the lat position at which `t` occurs in the collection
  int last(std::string t) { return dictionary[t].back().second.back(); }

  // Returns the position of `t's first occurrence after the `current` position
  int next(std::string t, int current) {
    PostingsList postings = dictionary[t];
    // Return the end of the collection (infinity) if the postings list for `t`
    // is empty or the last position of `t` is less than or equal to the
    // `current` position
    if (postings.size() == 0 || postings.back().second.back() <= current) {
      return INT32_MAX;
    }
    // Return the first occurrence of `t` if it's position is greater than the
    // `current` position
    if (postings.front().second.front() > current) {
      return postings.front().second.front();
    }
    return postings.at(binarySearch(t, 0, postings.size(), current)).;
  }
};

// Returns a list of paragraphs containing a list of words in the paragraphs
ParagraphTokens getTokensFromParagraphs(std::string paragraphs[], int size) {
  ParagraphTokens collection;

  for (int i = 0; i < size; i++) {
    std::vector<std::string> words;
    std::string word = "";

    for (char c : paragraphs[i]) {
      // If the character is a space, add the current word to the vector
      // and start a new word
      if (c == ' ') {
        words.push_back(word);
        word = "";
      } else {
        // Convert the character to lower case
        c = std::tolower(c);
        // Add the character to the current word
        word += c;
      }
    }
    // Add the last word to the `words` vector
    words.push_back(word);
    // Add the words for a paragraph to the `colletion` vector
    collection.push_back(words);
  }

  return collection;
}

int main() {
  std::string paragraphs[4] = {"The quick brown fox jumped",
                               "Over the lazy the dog", "The quick yellow dog",
                               "Ran into the room"};

  ParagraphTokens paragraphCollection = getTokensFromParagraphs(paragraphs, 4);
  InvertedIndex index(paragraphCollection);
  index.printDictionary();
  // index.getWordPositions("quick");
  // int pos = index.next("quick", 0);
  // std::cout << "Next: " << pos << std::endl;
}
