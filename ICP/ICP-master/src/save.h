/**
  * Header file containing structure for save/load operations.
  * Method for these operations can be found in board.cpp
  *
  * @author     Jakub Jochlík - xjochl00
  *
  */

#ifndef SAVE_H
#define SAVE_H

typedef struct{
    int stones[12 * 12];
    int PVE;
    int currentlyPlaying;
    int currentTurn;
    int size;
    int difficulty;
    int undoPerformed;

}saveGameStruct;

#endif // SAVE_H
