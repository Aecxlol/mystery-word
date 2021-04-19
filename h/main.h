#ifndef MYSTERY_WORD_H
#define MYSTERY_WORD_H

#include <string>
#include <vector>

void displayMainMenu();
void loadGame(int playerNumber);
void loadSinglePlayerGame();
void loadMultiPlayerGame();
void displayScoreboard();
std::string shuffleWord(std::vector<char> & word);

#endif