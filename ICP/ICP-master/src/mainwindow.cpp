/**
  * MainWindow
  *
  * @author     Jakub Jochlík - xjochl00
  *
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stone.cpp"
#include "board.cpp"
#include <QPixmap>


/**
 * constructor for mainWindow
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ingamePannel->setVisible(false);    //game is not started yet hide the ingame pannel
    ui->settingUpAi->setVisible(false);
    hideStart();

    playfield = new Board;

    connect(ui->startButton, SIGNAL(released()), this, SLOT(whoIsEnemy()));
    connect(ui->loadButton, SIGNAL(released()), this, SLOT(buttonLoad()));
    connect(ui->exitButton, SIGNAL(released()), this, SLOT(buttonExit()));
    //makePlayboard();
}

/**
 * destructor for mainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::whoIsEnemy(){
    if(ui->numberOfPlayers->currentText() == "1"){
        ui->settingUpGame->setVisible(false);
        connect(ui->startPVE, SIGNAL(released()), this, SLOT(makePlayboard()));
        ui->settingUpAi->setVisible(true);
    }
    else{
        makePlayboard();
    }
}

int MainWindow::getBoardSize()
{
    ui->settingUpGame->setVisible(false);
    if(ui->boardSize->currentText() == "6x6" ){
        ui->vertical6x6->setVisible(true);
        ui->horizontal6x6->setVisible(true);
        return 6;
    }
    else if(ui->boardSize->currentText() == "8x8"){
        ui->vertical8x8->setVisible(true);
        ui->horizontal8x8->setVisible(true);
        return 8;
    }
    else if(ui->boardSize->currentText() == "10x10"){
        ui->vertical10x10->setVisible(true);
        ui->horizontal10x10->setVisible(true);
        return 10;
    }
    else{           //12x12
        ui->vertical12x12->setVisible(true);
        ui->horizontal12x12->setVisible(true);
        return 12;
    }
}

void MainWindow::makePlayboard()
{
    int sizeofBoard = getBoardSize();
    for(int i = 0; i < sizeofBoard; i++){               //here i generate buttons in square shaped playfield based on choosen size
        for(int j = 0; j < sizeofBoard; j++){
            field_button[i][j] = new QPushButton("", this);
            field_button[i][j]->setGeometry(QRect(QPoint(80 + (45*j),80 + (45*i)), QSize(47, 47)));
            field_button[i][j]->setMinimumHeight(i);
            field_button[i][j]->setMinimumWidth(j);
            field_button[i][j]->setProperty("i", i);        //i for X index
            field_button[i][j]->setProperty("j", j);        //j for Y index - format is [X,Y]
            field_button[i][j]->setVisible(true);

            connect(field_button[i][j], SIGNAL(released()), this, SLOT(buttonClick()));
        }
    }
    ui->settingUpGame->setVisible(false);
    ui->settingUpAi->setVisible(false);
    start(sizeofBoard);
    setIcon(ui->displayPlayerButton,":img/white.png");      //set white to the display button, becouse white is first to start
    ui->displayPlayerButton->setProperty("player", 1);

    ui->whiteLCD->display(STARTINGSCORE);
    ui->blackLCD->display(STARTINGSCORE);
}

void MainWindow::setDifficulty(){
    if(ui->difficulty->currentText() == "Easy"){
        playfield->setDifficulty(0);
    }
    else{
        playfield->setDifficulty(1);
    }
}

void MainWindow::start(int size){
    playfield->prepareBoard(size);
    setEnemy();
    if(playfield->_PVE){
        setDifficulty();
    }


    //connect buttons in side panel
    connect(ui->saveGameButton, SIGNAL(released()), this, SLOT(buttonSave()));
    connect(ui->undoGameButton, SIGNAL(released()), this, SLOT(buttonUndo()));
    connect(ui->redoGameButton, SIGNAL(released()), this, SLOT(buttonRedo()));
    connect(ui->exitGameButton, SIGNAL(released()), this, SLOT(buttonExit()));

    ui->ingamePannel->setVisible(true);
    renderPlayboard();
}

void MainWindow::setEnemy(){
    if(ui->numberOfPlayers->currentText() == "1"){
        playfield->setEnemy(true);
    }
    else{
        playfield->setEnemy(false);
    }
}

void MainWindow::buttonClick(){
    //these two contains position of clicked button A.K.A. wich stone is clicked
    int index_X = sender()->property("i").toInt();
    int index_Y = sender()->property("j").toInt();
    if(playfield->isOwned1(index_Y, index_X)){          //is selected field free?
        QMessageBox testbox;
        testbox.setText("Toto pole je obsazené");
        testbox.exec();
        return;
    }

    //field is free so you can continue
    if(!playfield->canBePlaced(index_X, index_Y)){          //is placing stone according to the game rules?
        QMessageBox testbox;
        testbox.setText("Tah na toto pole nedovolují pravidla hry");
        testbox.exec();
        return;
    }

    //here i know that at least one line can be flipped, so I am gonna try them all

    if(playfield->getUndoPerformed())
        playfield->cleanUndoRedo();
    stone_type playersColor = playfield->getPlayersColor();

    if(playfield->canPlaceLeft(index_Y, index_X, playersColor))
        playfield->placeLeft(index_Y, index_X, playersColor);

    if(playfield->canPlaceRight(index_Y, index_X, playersColor))
        playfield->placeRight(index_Y, index_X, playersColor);

    if(playfield->canPlaceUp(index_Y, index_X, playersColor))
        playfield->placeUp(index_Y, index_X, playersColor);

    if(playfield->canPlaceDown(index_Y, index_X, playersColor))
        playfield->placeDown(index_Y, index_X, playersColor);

    if(playfield->canPlaceDiagonalLD(index_Y, index_X, playersColor))
        playfield->placeDiagonalLD(index_Y, index_X, playersColor);

    if(playfield->canPlaceDiagonalLU(index_Y, index_X, playersColor))
        playfield->placeDiagonalLU(index_Y, index_X, playersColor);

    if(playfield->canPlaceDiagonalRD(index_Y, index_X, playersColor))
        playfield->placeDiagonalRD(index_Y, index_X, playersColor);

    if(playfield->canPlaceDiagonalRU(index_Y, index_X, playersColor))
        playfield->placeDiagonalRU(index_Y, index_X, playersColor);

    swapDisplayPlayerButton(ui->displayPlayerButton);
    setLCD();
    playfield->endTurn();
    renderPlayboard();
    playfield->saveLastTurn();

    if(!canCurrentPlayerPlay()){
        QMessageBox testbox;
        playfield->endTurn();
        swapDisplayPlayerButton(ui->displayPlayerButton);
        if(!canCurrentPlayerPlay()){
            gameOver();
            return;

        }
        char message[80];
        sprintf(message, "Hráč %s nemá žádné možné tahy, pokračuje %s hráč", playfield->whoIsPlaying() == 2 ? "bílý" : "černý",  playfield->whoIsPlaying() == 2 ? "černý" : "bílý");
        testbox.setText(message);
        testbox.exec();
    }

    if(playfield->_PVE && playfield->getCurrentlyPlaying() == 2){                   //if its black's turn and it is PVE perform ai step
        if(playfield->getDifficulty() == 0 || playfield->getDifficulty() == 1){    //easy           //TODO fix ||..... erase right side of '||' when medium is done
            playfield->performEasyAI();
            swapDisplayPlayerButton(ui->displayPlayerButton);
            setLCD();
            playfield->endTurn();
            renderPlayboard();
            playfield->saveLastTurn();

            if(!canCurrentPlayerPlay()){
                QMessageBox testbox;
                playfield->endTurn();
                swapDisplayPlayerButton(ui->displayPlayerButton);
                if(!canCurrentPlayerPlay()){
                    gameOver();
                    return;

                }
                char message[80];
                sprintf(message, "Hráč %s nemá žádné možné tahy, pokračuje %s hráč", playfield->whoIsPlaying() == 2 ? "bílý" : "černý",  playfield->whoIsPlaying() == 2 ? "černý" : "bílý");
                testbox.setText(message);
                testbox.exec();
            }
        }
        else{           //medium

        }
    }
}

void MainWindow::buttonSave(){
    playfield->saveGame();
}

void MainWindow::buttonLoad(){
    loadGameGui();
}

void MainWindow::buttonUndo(){
    if(playfield->undo()){
        swapDisplayPlayerButton(ui->displayPlayerButton);
        if(playfield->_PVE){
            playfield->undo();
            swapDisplayPlayerButton(ui->displayPlayerButton);
        }
        setLCD();
        renderPlayboard();
    }
    else{
        QMessageBox testbox;
        testbox.setText("Nelze provést další UNDO krok");
        testbox.exec();
    }
}

void MainWindow::buttonRedo(){
    if(playfield->redo()){
        swapDisplayPlayerButton(ui->displayPlayerButton);
        if(playfield->_PVE){
            playfield->redo();
            swapDisplayPlayerButton(ui->displayPlayerButton);
        }
        setLCD();
        renderPlayboard();
    }
    else{
        QMessageBox testbox;
        testbox.setText("Nelze provést další REDO krok");
        testbox.exec();
    }
}

void MainWindow::buttonExit(){
    QApplication::quit();
}

void MainWindow::renderPlayboard(){
    Stone **stones = playfield->getBoard();
    for(int i = 0; i < playfield->getSize(); i++){
        for(int j = 0; j < playfield->getSize(); j++){
            this->setStone(field_button[i][j], stones[i * playfield->getSize() + j]);
        }
    }
}

void MainWindow::setStone(QPushButton *button, Stone *stone){
    stone_type color = stone->getColor();
    QPixmap img(color == white ? ":img/white.png" : color == black ? ":img/black.png" : ":img/empty.png");

    QIcon icon(img);
    button->setIcon(icon);
    button->setIconSize(QSize(ICONSIZE, ICONSIZE));
    button->setStyleSheet("border: none");
}

void MainWindow::setIcon(QPushButton *button, const char *imgPath){
    QPixmap img(imgPath);
    QIcon icon(img);
    button->setIcon(icon);
    button->setIconSize(QSize(ICONSIZE, ICONSIZE));
}

void MainWindow::swapDisplayPlayerButton(QPushButton *display){
    int player = display->property("player").toInt();
    if(player == 1){
        display->setProperty("player", 2);
        setIcon(display, ":img/black.png");
    }
    else{
        display->setProperty("player", 1);
        setIcon(display, ":img/white.png");
    }
}

void MainWindow::setLCD(){
    int W = 0;
    int B = 0;
    int size = playfield->getSize();
    Stone **tmpStone = playfield->getBoard();
    stone_type tmpColor;
    for(int x = 0; x < size; x++){
        for(int y = 0; y < size; y++){
            tmpColor = tmpStone[x * size + y]->getColor();
            if(tmpColor == white)
                W++;
            else if(tmpColor == black)
                B++;
        }
    }
    ui->whiteLCD->display(W);
    ui->blackLCD->display(B);
}

bool MainWindow::canCurrentPlayerPlay(){
    int size = playfield->getSize();
    for(int x = 0; x < size; x++){
        for(int y = 0; y < size; y++){
            if(playfield->isOwned1(y, x)){
                ;
            }
            else if(playfield->canBePlaced(x, y))
                return true;
        }
    }
    return false;
}

void MainWindow::gameOver(){
    int whitePlayer = ui->whiteLCD->intValue();
    int blackPlayer = ui->blackLCD->intValue();
    QMessageBox result;
    if(whitePlayer > blackPlayer){
        result.setText("Vyhrává bílý hráč");
        result.exec();
    }
    else if(whitePlayer < blackPlayer){
        result.setText("Vyhrává černý hráč");
        result.exec();
    }
    else{
        result.setText("Remíza");
        result.exec();
    }
    //playfield->~Board();
    //delete playfield;
    QApplication::exit();
    hideButtons();
    hideStart();

    //playfield->~Board();
    ui->ingamePannel->setVisible(false);
    ui->settingUpGame->setVisible(true);
}

void MainWindow::hideButtons(){
    int size = playfield->getSize();
    for(int x = 0; x < size; x++){
        for(int y = 0; y < size; y++){
            field_button[x][y]->setVisible(false);
        }
    }
}

void MainWindow::hideStart(){
    ui->vertical6x6->setVisible(false);
    ui->horizontal6x6->setVisible(false);
    ui->vertical8x8->setVisible(false);
    ui->horizontal8x8->setVisible(false);
    ui->vertical10x10->setVisible(false);
    ui->horizontal10x10->setVisible(false);
    ui->vertical12x12->setVisible(false);
    ui->horizontal12x12->setVisible(false);
}

void MainWindow::loadGameGui(){
    int sizeofBoard = playfield->loadGame();
    for(int i = 0; i < sizeofBoard; i++){               //here i generate buttons in square shaped playfield based on choosen size
        for(int j = 0; j < sizeofBoard; j++){
            field_button[i][j] = new QPushButton("", this);
            field_button[i][j]->setGeometry(QRect(QPoint(80 + (45*j),80 + (45*i)), QSize(47, 47)));
            field_button[i][j]->setMinimumHeight(i);
            field_button[i][j]->setMinimumWidth(j);
            field_button[i][j]->setProperty("i", i);        //i for X index
            field_button[i][j]->setProperty("j", j);        //j for Y index - format is [X,Y]
            field_button[i][j]->setVisible(true);

            connect(field_button[i][j], SIGNAL(released()), this, SLOT(buttonClick()));
        }
    }

    connect(ui->saveGameButton, SIGNAL(released()), this, SLOT(buttonSave()));
    connect(ui->undoGameButton, SIGNAL(released()), this, SLOT(buttonUndo()));
    connect(ui->redoGameButton, SIGNAL(released()), this, SLOT(buttonRedo()));
    connect(ui->exitGameButton, SIGNAL(released()), this, SLOT(buttonExit()));

    ui->settingUpGame->setVisible(false);
    switch(sizeofBoard){
    case 6:
        ui->vertical6x6->setVisible(true);
        ui->horizontal6x6->setVisible(true);
        break;
    case 8:
        ui->vertical8x8->setVisible(true);
        ui->horizontal8x8->setVisible(true);
        break;
    case 10:
        ui->vertical10x10->setVisible(true);
        ui->horizontal10x10->setVisible(true);
        break;
    default:
        ui->vertical12x12->setVisible(true);
        ui->horizontal12x12->setVisible(true);
    }

    if(playfield->getCurrentlyPlaying() == 1){
        setIcon(ui->displayPlayerButton,":img/white.png");
    }
    else{
        setIcon(ui->displayPlayerButton,":img/black.png");
    }

    ui->ingamePannel->setVisible(true);
    renderPlayboard();
    setLCD();

}
