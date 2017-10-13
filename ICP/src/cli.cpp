/**
  * cli - text interface file
  * all functions will be in this file as well as includes.
  * i dont feel that i need to create header file for this file
  *
  * @author     Jakub Jochlík - xjochl00
  *
  */

#include <iostream>
#include <stdio.h>
#include "board.h"


#define WAITTIME 999999999

using namespace std;

void renderBoard(Board *cliBoard){
    Stone **cliStones = cliBoard->getBoard();
    for(int i = 0; i < cliBoard->getSize(); i++){
        for(int j = 0; j < cliBoard->getSize(); j++){
            cout << cliStones[i * cliBoard->getSize() + j]->toCLI();
        }
        cout << endl;
    }
}

void whosTurnIsIt(Board *cliBoard){
    if(cliBoard->getCurrentlyPlaying() == 1){
        cout << "Hraje BILY hrac" << endl;
    }
    else{
        cout << "Hraje CERNY hrac" << endl;
    }
}

void waitForIt(int wait){
    while(wait > 0){
        wait--;
    }
}

bool canCurrentPlayerPlay(Board *cliBoard){
    int tmpsize = cliBoard->getSize();
    for(int x = 0; x < tmpsize; x++){
        for(int y = 0; y < tmpsize; y++){
            if(cliBoard->isOwned1(y, x)){
                ;
            }
            else if(cliBoard->canBePlaced(x, y))
                return true;
        }
    }
    return false;
}

void gameOver(Board *cliBoard){
    int W = 0;
    int B = 0;
    int size = cliBoard->getSize();
    Stone **cliStones = cliBoard->getBoard();
    for(int x = 0; x < size; x++){
        for(int y = 0; y < size; y++){
            if(cliStones[x * cliBoard->getSize() + y]->toCLI() == "W")
                W++;
            else if(cliStones[x * cliBoard->getSize() + y]->toCLI() == "B")
                B++;
        }
    }

    if(W > B){
        cout << "Vyhrava BILY hrac" << endl;
    }
    else if(W < B){
        cout << "Vyhrava CERNY hrac" << endl;
    }
    else{
        cout << "REMIZA" << endl;
    }
}

int main(void)
{
    int size;       //here the size of board will be stored
    int numOfPlayers;
    int difficulty;
    cout << "Zvolte velikost ctverce herni desky. Moznosti jsou 6, 8, 10 a 12" << endl;
    cin >> size;

    if(size == 6 || size == 8 || size == 10 || size == 12){}
    else{
        cout << "Neplatna velikost desky\n";
        return 1;
    }

    cout << "Nyni zvolte pocet hracu. 1 nebo 2 hraci..." << endl;
    cin >> numOfPlayers;
    if(numOfPlayers == 1 || numOfPlayers == 2){}
    else{
        cout << "Neplatny pocet hracu\n";
        return 1;
    }

    if(numOfPlayers == 1){
        cout << "Zadejte obtiznost protihrace. 0 - Easy       1 - Medium" << endl;
        cin >> difficulty;

        if(difficulty == 0 || difficulty == 1){}
        else{
            cout << "Neplatna obtiznost\n";
            return 1;
        }
    }

    Board *cliBoard = new Board;
    cliBoard->prepareBoard(size);
    //renderBoard(cliBoard);

    //Based on number of players select oponent and in case of PVE set AI difficulty
    if(numOfPlayers == 1){
        cliBoard->setEnemy(true);
        if(difficulty == 0){
            cliBoard->setDifficulty(0);
        }
        else{
            cliBoard->setDifficulty(1);
        }
    }
    else{
        cliBoard->setEnemy(false);
    }

    int x;
    int y;
    int input;
    while(1){
        cout << "\n\n";
        renderBoard(cliBoard);
        cout << "\n\n";
        whosTurnIsIt(cliBoard);

        cout << "Zvolte '1' pro polozeni kamene, '2' pro undo, '3' pro redo, '4' pro ulozeni hry, '5' pro nacteni hry a '0' pro ukonceni hry" << endl;
        cin >> input;
        if(input == 0)
            return 0;
        else if(input == 1){}//put stone
        else if(input == 2){
            if(cliBoard->undo()){
                cout << "Provadim undo..." << endl;
                waitForIt(WAITTIME);
                if(numOfPlayers == 1){cliBoard->undo();}
            }
            else{
                cout << "Nelze provest dalsi krok UNDO" << endl;
                waitForIt(WAITTIME);
            }
            continue;
        }
        else if(input == 3){
            if(cliBoard->redo()){
                cout << "Provadim redo..." << endl;
                waitForIt(WAITTIME);
                if(numOfPlayers == 1){cliBoard->redo();}
            }
            else{
                cout << "Nelze provest dalsi krok REDO" << endl;
                waitForIt(WAITTIME);
            }
            continue;
        }
        else if(input == 4){
            cliBoard->saveGame();
            continue;
        }
        else if(input == 5){
            cliBoard->loadGame();
            continue;
        }
        else{
            cout << "Zadan spatny prikaz" << endl;
            waitForIt(WAITTIME);
            continue;
        }


        cout << "Zadejte X-ovou souradnici mista, pro vlozeni kamenu: ";
        cin >> x;
        cout << "\nZadejte Y-ovou souradnici mista, pro vlozeni kamenu: ";
        cin >> y;
        cout << endl;

        if(cliBoard->isOwned1(y, x)){   //can you play here?
            cout << "Toto pole je obsazene\n";
            waitForIt(WAITTIME);
            continue;
        }

        if(!cliBoard->canBePlaced(x, y)){
            cout << "Tah na toto pole nedovoluji pravidla" << endl;
            waitForIt(WAITTIME);
            continue;
        }

        //here i know that selected plase is valid
        stone_type playersColor;
        if(cliBoard->getCurrentlyPlaying() == 1){playersColor = white;}
        else{playersColor = black;}

        if(cliBoard->getUndoPerformed())
            cliBoard->cleanUndoRedo();

        if(cliBoard->canPlaceLeft(y, x, playersColor))
            cliBoard->placeLeft(y, x, playersColor);

        if(cliBoard->canPlaceRight(y, x, playersColor))
            cliBoard->placeRight(y, x, playersColor);

        if(cliBoard->canPlaceUp(y, x, playersColor))
            cliBoard->placeUp(y, x, playersColor);

        if(cliBoard->canPlaceDown(y, x, playersColor))
            cliBoard->placeDown(y, x, playersColor);

        if(cliBoard->canPlaceDiagonalLD(y, x, playersColor))
            cliBoard->placeDiagonalLD(y, x, playersColor);

        if(cliBoard->canPlaceDiagonalLU(y, x, playersColor))
            cliBoard->placeDiagonalLU(y, x, playersColor);

        if(cliBoard->canPlaceDiagonalRD(y, x, playersColor))
            cliBoard->placeDiagonalRD(y, x, playersColor);

        if(cliBoard->canPlaceDiagonalRU(y, x, playersColor))
            cliBoard->placeDiagonalRU(y, x, playersColor);

        cliBoard->endTurn();
        cliBoard->saveLastTurn();

        if(!canCurrentPlayerPlay(cliBoard)){
            cliBoard->endTurn();
            if(!canCurrentPlayerPlay(cliBoard)){
               gameOver(cliBoard);
               waitForIt(WAITTIME);
               return 0;
            }
            char message[80];
            sprintf(message, "Hráč %s nemá žádné možné tahy, pokračuje %s hráč", cliBoard->whoIsPlaying() == 2 ? "bílý" : "černý",  cliBoard->whoIsPlaying() == 2 ? "černý" : "bílý");
            cout << message << endl;
            waitForIt(WAITTIME);
        }

        if(cliBoard->_PVE && cliBoard->getCurrentlyPlaying() == 2){         //pve turn
            if(cliBoard->getDifficulty() == 0 || cliBoard->getDifficulty() == 1){         //easy
                cliBoard->performEasyAI();
                cliBoard->endTurn();
                cliBoard->saveLastTurn();
                if(!canCurrentPlayerPlay(cliBoard)){
                    cliBoard->endTurn();
                    if(!canCurrentPlayerPlay(cliBoard)){
                       gameOver(cliBoard);
                       waitForIt(WAITTIME);
                       return 0;
                    }
                    char message[80];
                    sprintf(message, "Hráč %s nemá žádné možné tahy, pokračuje %s hráč", cliBoard->whoIsPlaying() == 2 ? "bílý" : "černý",  cliBoard->whoIsPlaying() == 2 ? "černý" : "bílý");
                    cout << message << endl;
                    waitForIt(WAITTIME);
                }

            }
            else{               //medium

            }
        }

    }//while
}
