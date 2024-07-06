#include <iostream>
#include <sstream>
#include <algorithm>
// ANSI color escape codes
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

// Function to check if both sections of a word match the specified lengths
bool sectionsMatch(const std::string& word, int firstPartLetters, int secondPartLetters) {
    int firstPart = 0, secondPart = 0;
    bool isSecondPart = false;

    for (char c : word) {
        if (c == ' ') {
            isSecondPart = true;
            continue;
        }

        if (isSecondPart) {
            secondPart++;
        } else {
            firstPart++;
        }
    }

    return (firstPart == firstPartLetters && secondPart == secondPartLetters);
}

//remove words containing a specific letter from the list of matching words
void removeWordsWithLetter(std::vector<std::string>& words, char letter) {
    auto it = std::remove_if(words.begin(), words.end(), [letter](const std::string& word) {
        //convert each character of the word to lowercase and check for the letter
        for (char c : word) {
            if (std::tolower(c) == std::tolower(letter)) {
                return true;
            }
        }
        return false;
    });
    words.erase(it, words.end());
}


int main() {
//the list
    std::string text = R"(
Accomplice
Alchemist
Alpha Werewolf
Analyst
Anarchist
Arsonist
Assassin
Astronomer
Aura Seer
Avenger
Baker
Bandit
Beast Hunter
Bell Ringer
Blind Werewolf
Bodyguard
Bomber
Bully
Butcher
Cannibal
Confusion Wolf
Conjuror
Corruptor
Cupid
Cursed
Detective
Doctor
Easter Bunny
Evil Detective
Flagger
Flower Child
Fool
Forger
Fortune Teller
Gambler
Gentlewolf
Ghost Lady
Grave Robber
Grumpy Grandma
Guardian Wolf
Gunner
Headhunter
Illusionist
Instigator
Jailer
Jelly Wolf
Judge
Junior Werewolf
Kitten Wolf
Little Girl
Loudmouth
Lurker
Marksman
Mayor
Medium
Mortician
Naughty Boy
Night Watchman
Nightmare Werewolf
Pacifist
Preacher
President
Priest
Pumpkin king
Rainmaker
Red Lady
Regular Werewolf
Ritualist
Santa Claus
Sect Leader
Seer
Seer Apprentice
Serial Killer
Shadow Wolf
Sheriff
Siren
Sorcerer
Spirit Seer
Split Wolf
Storm Wolf
Stubborn Werewolf
Swamp Wolf
Tough Guy
Toxic Wolf
Trapper
Vigilante
Villager
Violinist
Voodoo Werewolf
Warden
Werewolf Berserk
Werewolf Fan
Wise Man
Witch
Wolf Pacifist
Wolf Scribe
Wolf Seer
Wolf Shaman
Wolf Summoner
Wolf Trickster
Zombie
    )";
    while (true) {
        // Ask for number of letters in each section
        int combinedLength;
        std::cout << GREEN << "Enter length of your word (or 0 to exit) : " << RESET;
        std::cin >> combinedLength;
        if (combinedLength < 10) {
            combinedLength = combinedLength * 10;
        }
        if (combinedLength < '0') {
                return 0;
            }
        // Extract first and second part lengths
        int firstPartLetters = combinedLength / 10;
        int secondPartLetters = combinedLength % 10;
        // Vector to store matching words
        std::vector<std::string> matchingWords;

        // Read words from text and check if they match the specified lengths
        std::istringstream iss(text);
        std::string word;
        while (std::getline(iss, word)) {
            if (sectionsMatch(word, firstPartLetters, secondPartLetters)) {
                matchingWords.push_back(word);
            }
        }

        // Show possible words
        std::cout << GREEN << "Possible words:" << RESET << std::endl;
        for (const auto& matchingWord : matchingWords) {
            std::cout << "-> " << RED << RED << matchingWord << RESET << std::endl;
            std::cout << std::string(matchingWord.length() + 10, '-') << std::endl;
        }

        // Remove words that have that letter
        while (!matchingWords.empty()) {
            // Ask for a letter to remove words containing it
            char letterToRemove;
            std::cout << GREEN << "Enter a letter to remove words that contain it (or 0 to exit): " << RESET;
            std::cin >> letterToRemove;

            // If the user enters '0', end the program
            if (letterToRemove == '0') {
                return 0;
            }

            // Remove words containing the specified letter
            removeWordsWithLetter(matchingWords, letterToRemove);

            // Print updated list of matching words
            std::cout << GREEN << "Words after removing those containing '" << letterToRemove << "':" << RESET << std::endl;
        
                for (const auto& matchingWord : matchingWords) {
                    std::cout << "-> " << RED << matchingWord << RESET << std::endl;
                    std::cout << std::string(matchingWord.length() + 10, '-') << std::endl; // Print longer underline
                }
            

            // If only one word is left, restart
            if (matchingWords.size() == 1) {
                break;
            }
        }

        
 
        
    }

    return 0;
}


