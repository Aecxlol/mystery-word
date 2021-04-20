#ifndef MYSTERY_WORD_H
#define MYSTERY_WORD_H

#include <string>
#include <vector>

// Scoreboard related
unsigned int gameId = 0;
std::vector<int> scores;
std::vector<std::string> gameType;
std::vector<std::string> wordToGuessScoreboard;

void displayMainMenu();
void loadGame(int playerNumber);
void loadSinglePlayerGame();
void loadMultiPlayerGame();
void displayScoreboard();
std::string shuffleWord(std::vector<char> & word);
void askUserWhatIsTheWord(std::string userAnswer, std::string wordToFind, std::string randomWordShuffled);
void displayMenuAfterWinning(bool isSinglePlayerGame);

#endif