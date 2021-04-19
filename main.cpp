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
    int choice = 0;
    int firstTimeInMenu = 0;

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
            int choicePlayer = 0;
            int firstTimeInSubMenu = 0;

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
    vector<char> randomWord;
    string wordToFind;
    string randomWordShuffled;
    int wordsNumber = 0;
    int random = 0;
    int counter = 0;
    string userAnswer;
    int userAttempt = 0;
    int userChoiceAfterWinning = 0;

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
                for (int i = 0; i < line.length(); i++)
                {
                    randomWord.push_back(line[i]);
                }
                break;
            }
        }
        randomWordShuffled = shuffleWord(randomWord);

        while (userAnswer != wordToFind)
        {
            cout << endl << "Quel est ce mot ? " << randomWordShuffled << endl;
            cout << "Votre reponse : ";
            cin >> userAnswer;
            userAttempt++;
            if (userAnswer != wordToFind)
            {
                if (userAttempt > 0)
                {
                    cout << "Ce n'est pas le mot !" << endl;
                }
            }
        }

        cout << endl << "Bravo, le mot a trouver etait bien : " << wordToFind << " !" << endl << endl;
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
            loadSinglePlayerGame();
            break;

        case 3:
            exit(EXIT_SUCCESS);
            break;
        }
    }
    else
    {
        cout << "Une erreur s'est produite pendant l'ouverture du fichier." << endl;
        exit(EXIT_FAILURE);
    }
}

void loadMultiPlayerGame()
{
    string word;
    string wordShuffled;
    vector<char> wordToGuess;

    cout << endl << "- Mode multi -" << endl;
    cout << endl << "Saisissez un mot : ";
    cin >> word;

    for (int i = 0; i < word.length(); i++)
    {
        wordToGuess.push_back(word[i]);
    }

    wordShuffled = shuffleWord(wordToGuess);


}

string shuffleWord(vector<char> &word)
{
    string shuffledWord;
    int wordSize = word.size();
    int random = 0;

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
    cout << "|---------------------------------------|" << endl;
    cout << "|--------------SCOREBOARD---------------|" << endl;
    cout << "|---------------------------------------|" << endl;
}
