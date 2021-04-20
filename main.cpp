#include <iostream>
#include <fstream>
#include <typeinfo>
#include <ctime>
#include <cstdlib>
#include "h/main.h"

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(0));

    cout << "============================================" << endl;
    cout << "|| Bienvenue dans le jeu du mot mystere ! ||" << endl;
    cout << "============================================" << endl;

    displayMainMenu();

    return EXIT_SUCCESS;
}

void displayMainMenu()
{
    unsigned int choice = 0;
    unsigned int firstTimeInMenu = 0;

    while (choice < 1 || choice > 2)
    {
        if (firstTimeInMenu != 0)
        {
            cout << endl << endl;
            cout << "/!\\ Choix incorrect /!\\" << endl << endl;
        }

        cout << endl << "-- MENU PRINCIPAL --" << endl; 
        cout << "1 - Jouer" << endl;
        cout << "2 - Consulter le scoreboard" << endl;
        cout << "3 - Quitter" << endl;
        cout << "Votre choix : ";

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            unsigned int choicePlayer = 0;
            unsigned int firstTimeInSubMenu = 0;

            while (choicePlayer < 1 || choicePlayer > 2)
            {
                if (firstTimeInSubMenu != 0)
                {
                    cout << endl << endl;
                    cout << "/!\\ Choix incorrect /!\\" << endl << endl;
                }
                cout << endl << "- Choisissez le nombre de joueurs -" << endl;
                cout << "1 - 1 joueur" << endl;
                cout << "2 - 2 joueurs" << endl;
                cout << "3 - Quitter" << endl;
                cout << "Votre choix : ";
                cin >> choicePlayer;

                switch (choicePlayer)
                {
                case 1:
                    loadGame(choicePlayer);
                    break;

                case 2:
                    loadGame(choicePlayer);
                    break;

                case 3:
                    cout << endl << "A bientot !" << endl << endl;
                    exit(EXIT_SUCCESS);
                    break;
                }

                firstTimeInSubMenu++;
            }
        }
        break;

        case 2:
            displayScoreboard();
            break;

        case 3:
            cout << endl << "A bientot !" << endl << endl;
            exit(EXIT_SUCCESS);
            break;
        }

        firstTimeInMenu++;
    }
}

void loadGame(int playerNumber)
{
    if (playerNumber == 1)
        loadSinglePlayerGame();
    if (playerNumber == 2)
        loadMultiPlayerGame();
}

void loadSinglePlayerGame()
{
    string const dictionary("misc/dico.txt");
    ifstream fileStream(dictionary.c_str());
    string line;
    string wordToFind;
    string randomWordShuffled;
    string userAnswer;
    vector<char> randomWord;
    unsigned int wordsNumber = 0;
    unsigned int random = 0;
    unsigned int counter = 0;
    unsigned int userChoiceAfterWinning = 0;

    gameId += 1;
    gameType.push_back("Solo");
    
    cout << endl << "- Mode solo -" << endl;
    cout << "*Chargement du dictionnaire*" << endl;

    if (fileStream)
    {
        cout << "*Ouverture du dictionnaire reussite*" << endl;

        while (getline(fileStream, line))
        {
            wordsNumber++;
        }

        random = rand() % wordsNumber;
        fileStream.clear();
        fileStream.seekg(0, ios::beg);

        while (getline(fileStream, line))
        {
            counter++;
            if (counter == random)
            {
                wordToFind = line;
                wordToGuessScoreboard.push_back(wordToFind);
                for (int i = 0; i < line.length(); i++)
                {
                    randomWord.push_back(line[i]);
                }
                break;
            }
        }
        randomWordShuffled = shuffleWord(randomWord);

        askUserWhatIsTheWord(userAnswer, wordToFind, randomWordShuffled);

        displayMenuAfterWinning(true);
    }
    else
    {
        cout << "Une erreur s'est produite pendant l'ouverture du fichier." << endl;
        exit(EXIT_FAILURE);
    }
}

void loadMultiPlayerGame()
{
    string wordToFind;
    string wordShuffled;
    string userAnswer;
    vector<char> wordToGuess;

    gameId += 1;
    gameType.push_back("Multi");

    cout << endl << "- Mode multi -" << endl;
    cout << endl << "Saisissez un mot : ";
    cin >> wordToFind;

    wordToGuessScoreboard.push_back(wordToFind);

    for (unsigned int i = 0; i < wordToFind.length(); i++)
    {
        wordToGuess.push_back(wordToFind[i]);
    }

    wordShuffled = shuffleWord(wordToGuess);

    askUserWhatIsTheWord(userAnswer, wordToFind, wordShuffled);

    displayMenuAfterWinning(false);
}

string shuffleWord(vector<char> &word)
{
    string shuffledWord;
    unsigned int wordSize = word.size();
    unsigned int random = 0;

    while (shuffledWord.length() != wordSize)
    {
        random = rand() % word.size();
        shuffledWord += word[random];
        word.erase(word.begin() + random);
    }

    return shuffledWord;
}

void displayScoreboard()
{
    double gameWon = 0.0;
    double gameLost = 0.0;
    double ratio = 0.0;

    cout << endl << "- Tableau des scores -" << endl;

    if(gameId == 0)
    {
        cout << endl << "Aucune partie n'a encore ete jouee !" << endl;
    } else {
        cout << "|--------------------------------------------------------------------|" << endl;
        cout << "|-----------------------------SCOREBOARD-----------------------------|" << endl;
        cout << "|--------------------------------------------------------------------|" << endl;
        cout << "|--Partie--|---Score----|-----Statut----|-----Type-----|-----Mot-----|" << endl;

        for (int i = 0; i < gameId; i++)
        {
            cout << "|    N " << i + 1; 
            cout << "   | " << scores[i] << " point(s)";
            cout << " |     " << (scores[i] > 0 ? " Win " : " Loss") << "     |" ;
            cout << "     " << gameType[i] << "     |";
            cout << "    " << wordToGuessScoreboard[i] << "    |" << endl;

            scores[i] > 0 ? gameWon += 1.0 : gameLost += 1.0;
        }
        ratio = (gameWon / gameId) * 100;
        cout << "|--------------------------------------------------------------------|" << endl << endl;
        cout << "Vos statistiques :" << endl;
        cout << "Nombre de partie(s) gagnee(s) : " << gameWon << endl;
        cout << "Nombre de partie(s) perdue(s) : " << gameLost << endl;
        cout << "Pourcentage de victoire(s) : " << ratio << "%" << endl << endl;
    }

    displayMainMenu();
}

void askUserWhatIsTheWord(string userAnswer, string wordToFind, string randomWordShuffled)
{
    unsigned int userAttempt = 0;
    unsigned int userLives = 5;

    cout << endl << "Vous avez " << userLives << " vies." << endl;

    while (userAnswer != wordToFind && userLives > 0)
    {
        cout << endl << "Quel est ce mot ? " << randomWordShuffled << endl;
        cout << "Votre reponse : ";
        cin >> userAnswer;
        userAttempt++;
        if (userAnswer != wordToFind)
        {
            if (userAttempt > 0)
            {
                userLives--;
                cout << "Ce n'est pas le mot !" << endl;
                cout << "Il ne vous reste plus que " << userLives << " vies." << endl;
            }
        }
    }

    if(userLives > 0){
        scores.push_back(userLives);
        cout << endl << "Bravo, le mot a trouver etait bien : " << wordToFind << " !" << endl << endl;
    } else {
        scores.push_back(userLives);
        cout << endl << "Vous avez perdu, le mot a trouver etait : " << wordToFind << " :(" << endl << endl; 
    }
}

void displayMenuAfterWinning(bool isSinglePlayerGame)
{
    unsigned int userChoiceAfterWinning;

    cout << "Que voulez-vous faire ?" << endl;
    cout << "1 - Revenir au menu principal" << endl;
    cout << "2 - Rejouer" << endl;
    cout << "3 - Quitter" << endl;
    cout << "Votre choix ? ";
    cin >> userChoiceAfterWinning;

    switch (userChoiceAfterWinning)
    {
    case 1:
        displayMainMenu();
        break;

    case 2:
        (isSinglePlayerGame) ? loadSinglePlayerGame() : loadMultiPlayerGame();
        break;

    case 3:
        cout << endl << "A bientot !" << endl << endl;
        exit(EXIT_SUCCESS);
        break;
    }
}
