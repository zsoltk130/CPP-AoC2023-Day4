// CPP-AoC2023-Day4.cpp : Defines the entry point for the application.
//

#include "CPP-AoC2023-Day4.h"

#include <string>
#include <vector>
#include <fstream>
#include <regex>

struct Card
{
    int cardNumber;
    std::vector<int> winningNumbers;
    std::vector<int> ownedNumbers;
};

std::vector<std::string> readLinesFromFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

std::vector<Card> findNumbers(const std::vector<std::string>& input)
{
    std::regex numberPattern("\\d+|[|]");
    std::vector<Card> cards;

    for (std::string line : input)
    {
        Card card;
        std::string currentLine = line;

        auto numberPattern_begin = std::sregex_iterator(line.begin(), line.end(), numberPattern);
        auto numberPattern_end = std::sregex_iterator();

        bool isCardNumber = true;
        bool isSeparator = false;

        for (std::sregex_iterator it = numberPattern_begin; it != numberPattern_end; ++it) {
            std::smatch match = *it;
            std::string currentNumber = match.str();
            
            if (isCardNumber) 
            { 
                card.cardNumber = std::stoi(currentNumber);
                isCardNumber = false;
                continue;
            }
            if (currentNumber == "|")
            {
                isSeparator = true;
                continue;
            }
            if (!isSeparator && !isCardNumber)
            {
                int num = std::stoi(currentNumber);
                card.winningNumbers.push_back(num);
            }
            if (isSeparator && !isCardNumber)
            {
                int num = std::stoi(currentNumber);
                card.ownedNumbers.push_back(num);
            }
        }
        cards.push_back(card);
    }
    return cards;
}

int main()
{
    std::string filename = "aoc_d4.txt";
    std::vector<std::string> input = readLinesFromFile(filename);
    std::vector<Card> cards = findNumbers(input);
	std::cout << "Hello CMake." << std::endl;
	return 0;
}
