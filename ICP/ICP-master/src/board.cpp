/**
  * Board - class for playboard itself. This is the main class for whole game containing all subclasses
  *
  * @author     Jakub Jochlík - xjochl00
  *
  */

#include "board.h"
#include <iostream>

using namespace std;

void Board::prepareBoard(int size){
    _size = size;
    _currentTurn = 0;
    _playBoard = (Stone**)malloc(sizeof(Stone*) *size*size-1);
    _lastTurn = (stone_type*)malloc(sizeof(stone_type) *size*size-1);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            Stone *newStone = new Stone(i, j);
            _playBoard[i * size + j] = newStone;
        }
    }
    _currentlyPlaying = 1;   //white is first to play
    _undoPerformed = false;
    setStart();
}

Board::~Board(){
    for(int x = 0; x < _size; x++){
        for(int y = 0; y < _size; y++){
            delete _playBoard[x * _size + y];
        }
    }
    free(_playBoard);
    free(_lastTurn);

    for (auto &&turn : _undoRedo){
        free(turn);
    }
}

Stone** Board::getBoard(){
    return _playBoard;
}

bool Board::getUndoPerformed(){
    return _undoPerformed;
}

void Board::increaseTurnCounter(){
    _currentTurn++;
}

void Board::decreaseTurnCounter(){
    _currentTurn--;
}

void Board::saveLastTurn(){
    _lastTurn = (stone_type*)malloc(sizeof(stone_type) *_size * _size);
    for(int x = 0; x < _size; x++){
        for(int y = 0; y < _size; y++){
            _lastTurn[x * _size + y] = _playBoard[x * _size + y]->getColor();
        }
    }
    _undoRedo.insert(_undoRedo.begin() + _currentTurn, _lastTurn);
    increaseTurnCounter();
}


bool Board::undo(){
    decreaseTurnCounter();
    if(_currentTurn <= 0){
        increaseTurnCounter();
        return false;
    }
    _lastTurn = _undoRedo[_currentTurn - 1];

    if(_currentTurn % 2 == 0)
        _currentlyPlaying = 2;
    else{
        _currentlyPlaying = 1;
    }
    _undoPerformed = true;
    setBoard();
    return true;
}

bool Board::redo(){
    increaseTurnCounter();
    if(_currentTurn > (int)_undoRedo.size()){
        decreaseTurnCounter();
        return false;
    }
    if(_currentTurn % 2 == 0)
        _currentlyPlaying = 2;
    else{
        _currentlyPlaying = 1;
    }

    _lastTurn = _undoRedo[_currentTurn - 1];
    setBoard();
    return true;
}

void Board::setBoard(){
    for(int i = 0; i < _size; i++){
        for(int j = 0; j < _size; j++){
            _playBoard[i * _size + j]->setColor(_lastTurn[i * _size + j]);
        }
    }
}

void Board::cleanUndoRedo(){
    _undoRedo.erase(_undoRedo.begin() + _currentTurn, _undoRedo.end());
    _undoPerformed = false;
}

int Board::getSize(){
    return _size;
}

int Board::whoIsPlaying(){
    if(_currentlyPlaying == 1)
        return 1;
    else
        return 2;
}

void Board::setStart(){
    if(_size == 6){
        _playBoard[14]->setColor(white);
        _playBoard[15]->setColor(black);
        _playBoard[20]->setColor(black);
        _playBoard[21]->setColor(white);

    }
    else if(_size == 8){
        _playBoard[27]->setColor(white);
        _playBoard[28]->setColor(black);
        _playBoard[35]->setColor(black);
        _playBoard[36]->setColor(white);
    }
    else if(_size == 10){
        _playBoard[44]->setColor(white);
        _playBoard[45]->setColor(black);
        _playBoard[54]->setColor(black);
        _playBoard[55]->setColor(white);
    }
    else{           //12x12
        _playBoard[65]->setColor(white);
        _playBoard[66]->setColor(black);
        _playBoard[77]->setColor(black);
        _playBoard[78]->setColor(white);
    }
    saveLastTurn();
}

void Board::setEnemy(bool enemy){
    _PVE = enemy;
}

bool Board::isOwned1(int x, int y){
    int index = y * _size + x;
    return _playBoard[index]->isOwned2();
}

void Board::placeStone(int x, int y){
    if(_currentlyPlaying == 1){
        _playBoard[x * _size + y]->setColor(white);
    }
    else{
        _playBoard[x * _size + y]->setColor(black);
    }
}

int Board::getCurrentlyPlaying(){
    return _currentlyPlaying;
}

void Board::endTurn(){
    if(_currentlyPlaying == 1){_currentlyPlaying = 2;}
    else{_currentlyPlaying = 1;}
}

void Board::setDifficulty(int i){
    _difficulty = i;
}

int Board::getDifficulty(){
    return _difficulty;
}

bool Board::canBePlaced(int x, int y){
    stone_type col;
    if(_currentlyPlaying == 1){col = white;}
    else{col = black;}

    if(canPlaceLeft(y, x, col)){return true;}
    else if(canPlaceRight(y, x, col)){return true;}
    else if(canPlaceUp(y, x, col)){return true;}
    else if(canPlaceDown(y, x, col)){return true;}
    else if(canPlaceDiagonalLD(y, x, col)){return true;}
    else if(canPlaceDiagonalLU(y, x, col)){return true;}
    else if(canPlaceDiagonalRD(y, x, col)){return true;}
    else if(canPlaceDiagonalRU(y, x, col)){return true;}
    else
    return false;
}

stone_type Board::getPlayersColor(){
    if(_currentlyPlaying == 1){return white;}
    else{return black;}
}

bool Board::canPlaceLeft(int x, int y, stone_type color){
    bool first = true;
    bool self = true;
    for(int i = x; i >= 0; i--){
        if(self){       //skip clicked place
            self = false;
            continue;
        }
        if(first){      //first field next to you
            first = false;
            if(_playBoard[y * _size + i]->getColor() == color || _playBoard[y * _size + i]->getColor() == empty_field)
                return false;
            continue;
        }
        if(_playBoard[y * _size + i]->getColor() == empty_field)
            return false;
        if(_playBoard[y * _size + i]->getColor() == color){return true;}
    }
    return false;
}

bool Board::canPlaceRight(int x, int y, stone_type color){
    bool first = true;
    bool self = true;
    for(int i = x; i < _size; i++){
        if(self){       //skip clicked place
            self = false;
            continue;
        }
        if(first){      //first field next to you
            first = false;
            if(_playBoard[y * _size + i]->getColor() == color || _playBoard[y * _size + i]->getColor() == empty_field)
                return false;
            continue;
        }
        if(_playBoard[y * _size + i]->getColor() == empty_field)
            return false;
        if(_playBoard[y * _size + i]->getColor() == color){return true;}
    }
    return false;
}

bool Board::canPlaceUp(int x, int y, stone_type color){
    bool first = true;
    bool self = true;
    for(int j = y; j >= 0; j--){
        if(self){       //skip clicked place
            self = false;
            continue;
        }
        if(first){      //first field next to you
            first = false;
            if(_playBoard[j * _size + x]->getColor() == color || _playBoard[j * _size + x]->getColor() == empty_field)
                return false;
            continue;
        }
        if(_playBoard[j * _size + x]->getColor() == empty_field)
            return false;
        if(_playBoard[j * _size + x]->getColor() == color){return true;}
    }
    return false;
}

bool Board::canPlaceDown(int x, int y, stone_type color){
    bool first = true;
    bool self = true;
    for(int j = y; j < _size; j++){
        if(self){       //skip clicked place
            self = false;
            continue;
        }
        if(first){      //first field next to you
            first = false;
            if(_playBoard[j * _size + x]->getColor() == color || _playBoard[j * _size + x]->getColor() == empty_field)
                return false;
            continue;
        }
        if(_playBoard[j * _size + x]->getColor() == empty_field)
            return false;
        if(_playBoard[j * _size + x]->getColor() == color){return true;}
    }
    return false;
}

bool Board::canPlaceDiagonalLD(int x, int y, stone_type color){
    bool first = true;
    bool self = true;
    for(int i = x; i >= 0; i--){
        if(y >= _size)
            return false;
        if(self){       //skip clicked place
            self = false;
            y++;
            continue;
        }
        if(first){      //first field next to you
            first = false;
            if(_playBoard[y * _size + i]->getColor() == color || _playBoard[y * _size + i]->getColor() == empty_field)
                return false;
            y++;
            continue;
        }
        if( _playBoard[y * _size + i]->getColor() == empty_field)
            return false;
        if(_playBoard[y * _size + i]->getColor() == color){return true;}
        y++;
    }
    return false;
}

bool Board::canPlaceDiagonalLU(int x, int y, stone_type color){
    bool first = true;
    bool self = true;
    for(int i = x; i >= 0; i--){
        if(y < 0)
            return false;
        if(self){       //skip clicked place
            self = false;
            y--;
            continue;
        }
        if(first){      //first field next to you
            first = false;
            if(_playBoard[y * _size + i]->getColor() == color || _playBoard[y * _size + i]->getColor() == empty_field)
                return false;
            y--;
            continue;
        }
        if( _playBoard[y * _size + i]->getColor() == empty_field)
            return false;
        if(_playBoard[y * _size + i]->getColor() == color){return true;}
        y--;
    }
    return false;
}

bool Board::canPlaceDiagonalRD(int x, int y, stone_type color){
    bool first = true;
    bool self = true;
    for(int i = x; i < _size; i++){
        if(self){
            self = false;
            y++;
            continue;
        }
        if(y >= _size)
            return false;
        if(first){
            first = false;
            if(_playBoard[y * _size + i]->getColor() == color || _playBoard[y * _size + i]->getColor() == empty_field)
                return false;
            y++;
            continue;
        }
        if( _playBoard[y * _size + i]->getColor() == empty_field)
            return false;
        if(_playBoard[y * _size + i]->getColor() == color){return true;}
        y++;
    }
    return false;
}

bool Board::canPlaceDiagonalRU(int x, int y, stone_type color){
    bool first = true;
    bool self = true;
    for(int i = x; i < _size; i++){
        if(self){
            self = false;
            y--;
            continue;
        }
        if(y < 0)
            return false;
        if(first){
            first = false;
            if(_playBoard[y * _size + i]->getColor() == color || _playBoard[y * _size + i]->getColor() == empty_field)
                return false;
            y--;
            continue;
        }
        if( _playBoard[y * _size + i]->getColor() == empty_field)
            return false;
        if(_playBoard[y * _size + i]->getColor() == color){return true;}
        y--;
    }
    return false;
}

void Board::placeLeft(int x, int y, stone_type color){
    placeStone(y, x);
    bool self = true;
    for(int i = x; i >= 0; i--){
        if(self){       //skip clicked place
            self = false;
            continue;
        }
        if(_playBoard[y * _size + i]->getColor() == color)
            return;
        _playBoard[y * _size + i]->flipStone();
    }
}

void Board::placeRight(int x, int y, stone_type color){
    placeStone(y, x);
    bool self = true;
    for(int i = x; i < _size; i++){
        if(self){       //skip clicked place
            self = false;
            continue;
        }
        if(_playBoard[y * _size + i]->getColor() == color)
            return;
        _playBoard[y * _size + i]->flipStone();
    }
}

void Board::placeUp(int x, int y, stone_type color){
    placeStone(y, x);
    bool self = true;
    for(int j = y; j >= 0; j--){
        if(self){       //skip clicked place
            self = false;
            continue;
        }
        if(_playBoard[j * _size + x]->getColor() == color)
            return;
        _playBoard[j * _size + x]->flipStone();
    }
}

void Board::placeDown(int x, int y, stone_type color){
    placeStone(y, x);
    bool self = true;
    for(int j = y; j < _size; j++){
        if(self){       //skip clicked place
            self = false;
            continue;
        }
        if(_playBoard[j * _size + x]->getColor() == color)
            return;
        _playBoard[j * _size + x]->flipStone();
    }
}

void Board::placeDiagonalLD(int x, int y, stone_type color){
    placeStone(y, x);
    bool self = true;
    for(int i = x; i >= 0; i--){
        if(self){       //skip clicked place
            self = false;
            y++;
            continue;
        }
        if(_playBoard[y * _size + i]->getColor() == color)
            return;
         _playBoard[y * _size + i]->flipStone();
         y++;
    }
}

void Board::placeDiagonalLU(int x, int y, stone_type color){
    placeStone(y, x);
    bool self = true;
    for(int i = x; i >= 0; i--){
        if(self){       //skip clicked place
            self = false;
            y--;
            continue;
        }
        if(_playBoard[y * _size + i]->getColor() == color)
            return;
         _playBoard[y * _size + i]->flipStone();
         y--;
    }
}

void Board::placeDiagonalRD(int x, int y, stone_type color){
        placeStone(y, x);
        bool self = true;
        for(int i = x; i < _size; i++){
            if(self){       //skip clicked place
                self = false;
                y++;
                continue;
            }
            if(_playBoard[y * _size + i]->getColor() == color)
                return;
             _playBoard[y * _size + i]->flipStone();
             y++;
        }
}

void Board::placeDiagonalRU(int x, int y, stone_type color){
    placeStone(y, x);
    bool self = true;
    for(int i = x; i < _size; i++){
        if(self){       //skip clicked place
            self = false;
            y--;
            continue;
        }
        if(_playBoard[y * _size + i]->getColor() == color)
            return;
         _playBoard[y * _size + i]->flipStone();
         y--;
    }
}

void Board::performEasyAI(){
    bool AIBrain [_size][_size];
    for(int i = 0; i < _size; i++){
        for(int j = 0; j <_size; j++){
            AIBrain[i][j] = _playBoard[i * _size + j]->isOwned2();
        }
    }
    stone_type AIColor = black;
    srand (time(NULL));
    bool stop = true;
    int x;
    int y;

    while(stop){
        x = rand() % _size;
        y = rand() % _size;
        if(!AIBrain[x][y]){             //choosen place is free
            if(canBePlaced(x, y)){
                if(canPlaceLeft(y, x, AIColor))
                    placeLeft(y, x, AIColor);

                if(canPlaceRight(y, x, AIColor))
                    placeRight(y, x, AIColor);

                if(canPlaceUp(y, x, AIColor))
                    placeUp(y, x, AIColor);

                if(canPlaceDown(y, x, AIColor))
                    placeDown(y, x, AIColor);

                if(canPlaceDiagonalLD(y, x, AIColor))
                    placeDiagonalLD(y, x, AIColor);

                if(canPlaceDiagonalLU(y, x, AIColor))
                    placeDiagonalLU(y, x, AIColor);

                if(canPlaceDiagonalRD(y, x, AIColor))
                    placeDiagonalRD(y, x, AIColor);

                if(canPlaceDiagonalRU(y, x, AIColor))
                    placeDiagonalRU(y, x, AIColor);

                stop = false;
            }
            else{
                ;
            }
        }
        else{                   //occupied
            ;
        }
    }
}

void Board::saveGame(){
    saveGameStruct* save = (saveGameStruct*)calloc(sizeof(saveGameStruct), 1);

    for(int x = 0; x < _size; x++){
        for(int y = 0; y < _size; y++){
            save->stones[x * _size + y] = _playBoard[x * _size + y]->toInt();
        }
    }

    save->currentlyPlaying = _currentlyPlaying;
    save->currentTurn = _currentTurn;
    save->difficulty = _difficulty;
    save->size = _size;

    if(_undoPerformed){
        save->undoPerformed = 1;
    }
    else{
        save->undoPerformed = 0;
    }

    if(_PVE){
        save->PVE = 1;
    }
    else{
        save->PVE = 0;
    }

    FILE* file = fopen("savegame.dat", "w");
    fwrite(save, 1, sizeof(saveGameStruct), file);
    fclose(file);
}

int Board::loadGame(){
    saveGameStruct* load;
    load = (saveGameStruct*)calloc(sizeof(saveGameStruct), 1);
    FILE* file = fopen("savegame.dat", "r");
    fread(load, 1, sizeof(saveGameStruct), file);
    fclose(file);

    prepareBoard(load->size);
    _size = load->size;
    for(int i = 0; i < _size; i++){
        for(int j = 0; j < _size; j++){
            _playBoard[i * _size + j]->fromInt(load->stones[i * _size + j]);
        }
    }
    _currentlyPlaying = load->currentlyPlaying;
    _currentTurn = load->currentTurn;
    _difficulty = load->difficulty;

    if(load->PVE){
        _PVE = true;
    }
    else{
        _PVE = false;
    }

    if(load->undoPerformed){
        _undoPerformed = true;
    }
    else{
        _undoPerformed = false;
    }

    fixUndoStack();
    return load->size;
}

void Board::fixUndoStack(){
    _undoRedo.erase(_undoRedo.begin(), _undoRedo.end());
    _currentTurn = 0;
}
