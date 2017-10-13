/**
  * Board - class for playboard itself. This is the main class for whole game containing all subclasses
  *
  * @author     Jakub Jochlík - xjochl00
  *
  */

#ifndef BOARD_H
#define BOARD_H

#include "stone.h"
#include "save.h"
#include <stdlib.h>
#include <vector>
#include <time.h>

#define MAXTURNS 144
#define MAXIMUM 12

class Board
{
public:

    /**
      * Destructor
      */
    ~Board();

    /**
     * @Generates board and prepares game to be played
     *
     * @param boardSize     sizeof playBoard
     */
    void prepareBoard(int boardSize);

    /**
     *  get playboard as 2D array of stones
     *
     * @return      Pointer to the 2D stone array
     */\
    Stone** getBoard();

    /**
     * Tells the size of board
     *
     * @return      size of board as integer
     */
    int getSize();

    /**
     * creates starting positions for stones
     */
    void setStart();

    /**
     * Set up enemy - player or computer
     */
    void setEnemy(bool enemy);

    /**
     * just litle helper... for Stone::isowned2();
     */
    bool isOwned1(int x, int y);

    /**
     * Places stone to selected field
     *
     * @param x     index x of selected position
     * @param y     index y of selected position
     */
    void placeStone(int x, int y);

    /**
     * Ends turn and sets currently plaing player
     */
    void endTurn();

    /**
     * Method for performing stone placement check. Placing stone must be allowed
     * based on game rules - look just for first posible option
     *
     * @param x         index x of selected position
     * @param y         index y of selected position
     * @return          True if can be placed, false otherwise
     */
    bool canBePlaced(int x, int y);

    /**
     * Methods for performing check form point to given direction. Searching for same color stone
     * canPlaceLeft() checks that from choosen place to the left is same color stone
     * So on for the rest
     *
     * @return          True if can be placed, false otherwise
     */
    bool canPlaceLeft(int x, int y, stone_type color);
    bool canPlaceRight(int x, int y, stone_type color);
    bool canPlaceUp(int x, int y, stone_type color);
    bool canPlaceDown(int x, int y, stone_type color);
    bool canPlaceDiagonalLD(int x, int y, stone_type color);      //left down
    bool canPlaceDiagonalLU(int x, int y, stone_type color);      //left up
    bool canPlaceDiagonalRD(int x, int y, stone_type color);      //right down
    bool canPlaceDiagonalRU(int x, int y, stone_type color);      //right up

    /**
     * Methods for placing stone and fliping the rest
     * placeLeft() places stones from selected point to the left
     */
    void placeLeft(int x, int y, stone_type color);
    void placeRight(int x, int y, stone_type color);
    void placeUp(int x, int y, stone_type color);
    void placeDown(int x, int y, stone_type color);
    void placeDiagonalLD(int x, int y, stone_type color);
    void placeDiagonalLU(int x, int y, stone_type color);
    void placeDiagonalRD(int x, int y, stone_type color);
    void placeDiagonalRU(int x, int y, stone_type color);

    /**
     * Get players color based on _currentlyPlaying
     *
     * @return          color of _currentlyPlaying stone
     */
    stone_type getPlayersColor();

    /**
     * tells who is plazing
     *
     * @return          number based on whos turn is it
     */\
    int whoIsPlaying();

    /**
     * increase turn counter
     */
    void increaseTurnCounter();

    /**
     * decrease Turn Counter
     */
    void decreaseTurnCounter();

    /**
     * Before each turn, save current stones as field of stone_type - save onlz their collors
     */
    void saveLastTurn();

    /**
     * set board to selected turn
     */
    void setBoard();

    /**
     * perform undo step
     *
     * @return          False if no more steppes can be performed, true otherwise
     */
    bool undo();

    /**
     * Perform redo step
     *
     * @return          False if no more steppes can be performed, true otherwise
     */
    bool redo();

    /**
     * return information, if there were any undo stepps performed
     *
     * @return              True if undo was performed, false otherwise
     */
    bool getUndoPerformed();

    /**
     * in progress...
     */
    void cleanUndoRedo();

    /**
     * Sets game difficulty
     */
    void setDifficulty(int i);

    /**
     * returns value decribing what level ai is set up
     *
     * @return              _difficulty
     */
    int getDifficulty();

    /**
     * returns _currentlyPlaying
     */
    int getCurrentlyPlaying();

    /**
     * perform eazy ai turn... RNGESUS take the wheel!
     */
    void performEasyAI();

    /**
     * Saves all inforamtion about game into file
     */
    void saveGame();

    /**
     * Loads all inforamtion about game from file
     */
    int loadGame();

    /**
     * debug function
     */
    void fixUndoStack();

protected:
    Stone** _playBoard;
    int _size;
    int _currentlyPlaying;   // who is plaing, 1 - white player, 2 - black player
    int _currentTurn;           //index for undoRedo field
    stone_type* _lastTurn;          //contains field of colors - says how stones were placed last turn
    std::vector<stone_type*> _undoRedo;
    bool _undoPerformed;
    int _difficulty;                // 0 - very easy, 1 - easy

public:
    bool _PVE;       //true - one player, false - two players
};

#endif // BOARD_H
