#ifndef MYSTERY_WORD_H
#define MYSTERY_WORD_H

#include <string>
#include <vector>

using std::vector;
using std::string;

// Scoreboard related
unsigned int gameId = 0;
vector<int> scores;
vector<string> gameType;
vector<string> wordToGuessScoreboard;

void displayMainMenu();
void loadGame(int playerNumber);
void loadSinglePlayerGame();
void loadMultiPlayerGame();
void displayScoreboard();
string shuffleWord(vector<char> & word);
void askUserWhatIsTheWord(string userAnswer, string wordToFind, string randomWordShuffled);
void displayMenuAfterWinning(bool isSinglePlayerGame);

#endif