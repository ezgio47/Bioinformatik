#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> get_word(const std::string& query, const int word_size) {
    std::vector<std::string> word_list;

    //if (word_size > query.length()) {
    //    return word_list; // return an empty list if word_size is greater than query length
    //}

    for (uint32_t i = 0; i <= query.length() - word_size; ++i) {
        std::string created = query.substr(i, word_size);
        word_list.push_back(created);
    }

    return word_list;
}

int main() {
    // Beispielaufruf mit einer Zeichenkette und einer Wortgröße
    std::string query = "examplestring";
    int word_size = 3;

    // Aufruf der externen Funktion
    std::vector<std::string> result = get_word(query, word_size);

    // Gib die erstellte Wortliste aus
    std::cout << "Word List:\n";
    for (const auto& word : result) {
        std::cout << word << "\n";
    }

    return 0;
}
