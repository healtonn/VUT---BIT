/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *othelloGroup;
    QGroupBox *settingUpGame;
    QLabel *label;
    QPushButton *startButton;
    QLabel *label_3;
    QComboBox *numberOfPlayers;
    QLabel *label_2;
    QComboBox *boardSize;
    QPushButton *loadButton;
    QPushButton *exitButton;
    QGroupBox *ingamePannel;
    QPushButton *exitGameButton;
    QPushButton *undoGameButton;
    QPushButton *saveGameButton;
    QLabel *displayPlayerLabel;
    QPushButton *displayPlayerButton;
    QLCDNumber *whiteLCD;
    QLCDNumber *blackLCD;
    QLabel *whiteScoreLabel;
    QLabel *blackScoreLabel;
    QPushButton *redoGameButton;
    QGroupBox *settingUpAi;
    QLabel *label_4;
    QComboBox *difficulty;
    QPushButton *startPVE;
    QGroupBox *horizontal6x6;
    QVBoxLayout *verticalLayout;
    QPushButton *one;
    QPushButton *two;
    QPushButton *three;
    QPushButton *four;
    QPushButton *five;
    QPushButton *six;
    QGroupBox *vertical6x6;
    QHBoxLayout *horizontalLayout;
    QPushButton *one_2;
    QPushButton *two_2;
    QPushButton *three_2;
    QPushButton *four_2;
    QPushButton *five_2;
    QPushButton *six_2;
    QGroupBox *horizontal8x8;
    QVBoxLayout *verticalLayout_2;
    QPushButton *one_3;
    QPushButton *two_3;
    QPushButton *three_3;
    QPushButton *four_3;
    QPushButton *five_3;
    QPushButton *six_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *vertical8x8;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *one_4;
    QPushButton *two_4;
    QPushButton *three_4;
    QPushButton *four_4;
    QPushButton *five_4;
    QPushButton *six_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QGroupBox *horizontal10x10;
    QVBoxLayout *verticalLayout_3;
    QPushButton *one_5;
    QPushButton *two_5;
    QPushButton *three_5;
    QPushButton *four_5;
    QPushButton *five_5;
    QPushButton *six_5;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QGroupBox *vertical10x10;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *one_6;
    QPushButton *two_6;
    QPushButton *three_6;
    QPushButton *four_6;
    QPushButton *five_6;
    QPushButton *six_6;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QGroupBox *horizontal12x12;
    QVBoxLayout *verticalLayout_4;
    QPushButton *one_7;
    QPushButton *two_7;
    QPushButton *three_7;
    QPushButton *four_7;
    QPushButton *five_7;
    QPushButton *six_7;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QGroupBox *vertical12x12;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *one_8;
    QPushButton *two_8;
    QPushButton *three_8;
    QPushButton *four_8;
    QPushButton *five_8;
    QPushButton *six_8;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QPushButton *pushButton_22;
    QPushButton *pushButton_23;
    QPushButton *pushButton_24;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1250, 700);
        MainWindow->setMinimumSize(QSize(1250, 700));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        othelloGroup = new QGroupBox(centralWidget);
        othelloGroup->setObjectName(QStringLiteral("othelloGroup"));
        othelloGroup->setGeometry(QRect(0, 0, 1501, 700));
        settingUpGame = new QGroupBox(othelloGroup);
        settingUpGame->setObjectName(QStringLiteral("settingUpGame"));
        settingUpGame->setGeometry(QRect(300, 170, 661, 271));
        settingUpGame->setMinimumSize(QSize(541, 0));
        label = new QLabel(settingUpGame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(230, 30, 141, 51));
        startButton = new QPushButton(settingUpGame);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(230, 210, 75, 23));
        label_3 = new QLabel(settingUpGame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(400, 60, 101, 51));
        numberOfPlayers = new QComboBox(settingUpGame);
        numberOfPlayers->setObjectName(QStringLiteral("numberOfPlayers"));
        numberOfPlayers->setGeometry(QRect(390, 140, 69, 22));
        label_2 = new QLabel(settingUpGame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 60, 101, 51));
        boardSize = new QComboBox(settingUpGame);
        boardSize->setObjectName(QStringLiteral("boardSize"));
        boardSize->setGeometry(QRect(70, 140, 69, 22));
        loadButton = new QPushButton(settingUpGame);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        loadButton->setGeometry(QRect(540, 52, 75, 41));
        exitButton = new QPushButton(settingUpGame);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(540, 152, 75, 41));
        ingamePannel = new QGroupBox(othelloGroup);
        ingamePannel->setObjectName(QStringLiteral("ingamePannel"));
        ingamePannel->setEnabled(true);
        ingamePannel->setGeometry(QRect(1000, 10, 211, 621));
        ingamePannel->setStyleSheet(QStringLiteral(""));
        exitGameButton = new QPushButton(ingamePannel);
        exitGameButton->setObjectName(QStringLiteral("exitGameButton"));
        exitGameButton->setGeometry(QRect(50, 540, 111, 51));
        undoGameButton = new QPushButton(ingamePannel);
        undoGameButton->setObjectName(QStringLiteral("undoGameButton"));
        undoGameButton->setGeometry(QRect(50, 470, 111, 51));
        saveGameButton = new QPushButton(ingamePannel);
        saveGameButton->setObjectName(QStringLiteral("saveGameButton"));
        saveGameButton->setGeometry(QRect(50, 330, 111, 51));
        displayPlayerLabel = new QLabel(ingamePannel);
        displayPlayerLabel->setObjectName(QStringLiteral("displayPlayerLabel"));
        displayPlayerLabel->setGeometry(QRect(80, 20, 121, 41));
        displayPlayerButton = new QPushButton(ingamePannel);
        displayPlayerButton->setObjectName(QStringLiteral("displayPlayerButton"));
        displayPlayerButton->setEnabled(true);
        displayPlayerButton->setGeometry(QRect(60, 40, 101, 101));
        displayPlayerButton->setStyleSheet(QLatin1String("border:none\n"
"rgb(255, 255, 255)"));
        whiteLCD = new QLCDNumber(ingamePannel);
        whiteLCD->setObjectName(QStringLiteral("whiteLCD"));
        whiteLCD->setGeometry(QRect(10, 260, 81, 41));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        whiteLCD->setFont(font);
        blackLCD = new QLCDNumber(ingamePannel);
        blackLCD->setObjectName(QStringLiteral("blackLCD"));
        blackLCD->setGeometry(QRect(120, 260, 81, 41));
        whiteScoreLabel = new QLabel(ingamePannel);
        whiteScoreLabel->setObjectName(QStringLiteral("whiteScoreLabel"));
        whiteScoreLabel->setGeometry(QRect(50, 220, 47, 20));
        blackScoreLabel = new QLabel(ingamePannel);
        blackScoreLabel->setObjectName(QStringLiteral("blackScoreLabel"));
        blackScoreLabel->setGeometry(QRect(140, 220, 47, 20));
        redoGameButton = new QPushButton(ingamePannel);
        redoGameButton->setObjectName(QStringLiteral("redoGameButton"));
        redoGameButton->setGeometry(QRect(50, 400, 111, 51));
        exitGameButton->raise();
        undoGameButton->raise();
        saveGameButton->raise();
        displayPlayerLabel->raise();
        displayPlayerButton->raise();
        whiteLCD->raise();
        blackLCD->raise();
        whiteScoreLabel->raise();
        blackScoreLabel->raise();
        redoGameButton->raise();
        loadButton->raise();
        loadButton->raise();
        settingUpAi = new QGroupBox(othelloGroup);
        settingUpAi->setObjectName(QStringLiteral("settingUpAi"));
        settingUpAi->setGeometry(QRect(410, 150, 331, 141));
        label_4 = new QLabel(settingUpAi);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(90, 20, 211, 31));
        difficulty = new QComboBox(settingUpAi);
        difficulty->setObjectName(QStringLiteral("difficulty"));
        difficulty->setGeometry(QRect(108, 71, 101, 21));
        startPVE = new QPushButton(settingUpAi);
        startPVE->setObjectName(QStringLiteral("startPVE"));
        startPVE->setGeometry(QRect(120, 110, 75, 23));
        horizontal6x6 = new QGroupBox(othelloGroup);
        horizontal6x6->setObjectName(QStringLiteral("horizontal6x6"));
        horizontal6x6->setGeometry(QRect(30, 50, 61, 311));
        horizontal6x6->setStyleSheet(QLatin1String("border:none\n"
""));
        verticalLayout = new QVBoxLayout(horizontal6x6);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        one = new QPushButton(horizontal6x6);
        one->setObjectName(QStringLiteral("one"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        one->setFont(font1);
        one->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout->addWidget(one);

        two = new QPushButton(horizontal6x6);
        two->setObjectName(QStringLiteral("two"));
        two->setFont(font1);
        two->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout->addWidget(two);

        three = new QPushButton(horizontal6x6);
        three->setObjectName(QStringLiteral("three"));
        three->setFont(font1);
        three->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout->addWidget(three);

        four = new QPushButton(horizontal6x6);
        four->setObjectName(QStringLiteral("four"));
        four->setFont(font1);
        four->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(four);

        five = new QPushButton(horizontal6x6);
        five->setObjectName(QStringLiteral("five"));
        five->setFont(font1);
        five->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(five);

        six = new QPushButton(horizontal6x6);
        six->setObjectName(QStringLiteral("six"));
        six->setFont(font1);
        six->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(six);

        vertical6x6 = new QGroupBox(othelloGroup);
        vertical6x6->setObjectName(QStringLiteral("vertical6x6"));
        vertical6x6->setGeometry(QRect(70, 25, 291, 61));
        vertical6x6->setStyleSheet(QLatin1String("border:none\n"
""));
        horizontalLayout = new QHBoxLayout(vertical6x6);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        one_2 = new QPushButton(vertical6x6);
        one_2->setObjectName(QStringLiteral("one_2"));
        one_2->setFont(font1);
        one_2->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout->addWidget(one_2);

        two_2 = new QPushButton(vertical6x6);
        two_2->setObjectName(QStringLiteral("two_2"));
        two_2->setFont(font1);
        two_2->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout->addWidget(two_2);

        three_2 = new QPushButton(vertical6x6);
        three_2->setObjectName(QStringLiteral("three_2"));
        three_2->setFont(font1);
        three_2->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout->addWidget(three_2);

        four_2 = new QPushButton(vertical6x6);
        four_2->setObjectName(QStringLiteral("four_2"));
        four_2->setFont(font1);
        four_2->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(four_2);

        five_2 = new QPushButton(vertical6x6);
        five_2->setObjectName(QStringLiteral("five_2"));
        five_2->setFont(font1);
        five_2->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(five_2);

        six_2 = new QPushButton(vertical6x6);
        six_2->setObjectName(QStringLiteral("six_2"));
        six_2->setFont(font1);
        six_2->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(six_2);

        horizontal8x8 = new QGroupBox(othelloGroup);
        horizontal8x8->setObjectName(QStringLiteral("horizontal8x8"));
        horizontal8x8->setGeometry(QRect(30, 50, 61, 400));
        horizontal8x8->setStyleSheet(QLatin1String("border:none\n"
""));
        verticalLayout_2 = new QVBoxLayout(horizontal8x8);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        one_3 = new QPushButton(horizontal8x8);
        one_3->setObjectName(QStringLiteral("one_3"));
        one_3->setFont(font1);
        one_3->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout_2->addWidget(one_3);

        two_3 = new QPushButton(horizontal8x8);
        two_3->setObjectName(QStringLiteral("two_3"));
        two_3->setFont(font1);
        two_3->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout_2->addWidget(two_3);

        three_3 = new QPushButton(horizontal8x8);
        three_3->setObjectName(QStringLiteral("three_3"));
        three_3->setFont(font1);
        three_3->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout_2->addWidget(three_3);

        four_3 = new QPushButton(horizontal8x8);
        four_3->setObjectName(QStringLiteral("four_3"));
        four_3->setFont(font1);
        four_3->setStyleSheet(QStringLiteral(""));

        verticalLayout_2->addWidget(four_3);

        five_3 = new QPushButton(horizontal8x8);
        five_3->setObjectName(QStringLiteral("five_3"));
        five_3->setFont(font1);
        five_3->setStyleSheet(QStringLiteral(""));

        verticalLayout_2->addWidget(five_3);

        six_3 = new QPushButton(horizontal8x8);
        six_3->setObjectName(QStringLiteral("six_3"));
        six_3->setFont(font1);
        six_3->setStyleSheet(QStringLiteral(""));

        verticalLayout_2->addWidget(six_3);

        pushButton = new QPushButton(horizontal8x8);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font1);

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(horizontal8x8);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setFont(font1);

        verticalLayout_2->addWidget(pushButton_2);

        vertical8x8 = new QGroupBox(othelloGroup);
        vertical8x8->setObjectName(QStringLiteral("vertical8x8"));
        vertical8x8->setGeometry(QRect(70, 25, 381, 61));
        vertical8x8->setStyleSheet(QLatin1String("border:none\n"
""));
        horizontalLayout_2 = new QHBoxLayout(vertical8x8);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        one_4 = new QPushButton(vertical8x8);
        one_4->setObjectName(QStringLiteral("one_4"));
        one_4->setFont(font1);
        one_4->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout_2->addWidget(one_4);

        two_4 = new QPushButton(vertical8x8);
        two_4->setObjectName(QStringLiteral("two_4"));
        two_4->setFont(font1);
        two_4->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout_2->addWidget(two_4);

        three_4 = new QPushButton(vertical8x8);
        three_4->setObjectName(QStringLiteral("three_4"));
        three_4->setFont(font1);
        three_4->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout_2->addWidget(three_4);

        four_4 = new QPushButton(vertical8x8);
        four_4->setObjectName(QStringLiteral("four_4"));
        four_4->setFont(font1);
        four_4->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(four_4);

        five_4 = new QPushButton(vertical8x8);
        five_4->setObjectName(QStringLiteral("five_4"));
        five_4->setFont(font1);
        five_4->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(five_4);

        six_4 = new QPushButton(vertical8x8);
        six_4->setObjectName(QStringLiteral("six_4"));
        six_4->setFont(font1);
        six_4->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(six_4);

        pushButton_3 = new QPushButton(vertical8x8);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setFont(font1);

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(vertical8x8);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setFont(font1);

        horizontalLayout_2->addWidget(pushButton_4);

        horizontal10x10 = new QGroupBox(othelloGroup);
        horizontal10x10->setObjectName(QStringLiteral("horizontal10x10"));
        horizontal10x10->setGeometry(QRect(30, 50, 61, 490));
        horizontal10x10->setStyleSheet(QLatin1String("border:none\n"
""));
        verticalLayout_3 = new QVBoxLayout(horizontal10x10);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        one_5 = new QPushButton(horizontal10x10);
        one_5->setObjectName(QStringLiteral("one_5"));
        one_5->setFont(font1);
        one_5->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout_3->addWidget(one_5);

        two_5 = new QPushButton(horizontal10x10);
        two_5->setObjectName(QStringLiteral("two_5"));
        two_5->setFont(font1);
        two_5->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout_3->addWidget(two_5);

        three_5 = new QPushButton(horizontal10x10);
        three_5->setObjectName(QStringLiteral("three_5"));
        three_5->setFont(font1);
        three_5->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout_3->addWidget(three_5);

        four_5 = new QPushButton(horizontal10x10);
        four_5->setObjectName(QStringLiteral("four_5"));
        four_5->setFont(font1);
        four_5->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(four_5);

        five_5 = new QPushButton(horizontal10x10);
        five_5->setObjectName(QStringLiteral("five_5"));
        five_5->setFont(font1);
        five_5->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(five_5);

        six_5 = new QPushButton(horizontal10x10);
        six_5->setObjectName(QStringLiteral("six_5"));
        six_5->setFont(font1);
        six_5->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(six_5);

        pushButton_5 = new QPushButton(horizontal10x10);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setFont(font1);

        verticalLayout_3->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(horizontal10x10);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setFont(font1);

        verticalLayout_3->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(horizontal10x10);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setFont(font1);

        verticalLayout_3->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(horizontal10x10);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setFont(font1);

        verticalLayout_3->addWidget(pushButton_8);

        vertical10x10 = new QGroupBox(othelloGroup);
        vertical10x10->setObjectName(QStringLiteral("vertical10x10"));
        vertical10x10->setGeometry(QRect(70, 25, 470, 61));
        vertical10x10->setStyleSheet(QLatin1String("border:none\n"
""));
        horizontalLayout_3 = new QHBoxLayout(vertical10x10);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        one_6 = new QPushButton(vertical10x10);
        one_6->setObjectName(QStringLiteral("one_6"));
        one_6->setFont(font1);
        one_6->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout_3->addWidget(one_6);

        two_6 = new QPushButton(vertical10x10);
        two_6->setObjectName(QStringLiteral("two_6"));
        two_6->setFont(font1);
        two_6->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout_3->addWidget(two_6);

        three_6 = new QPushButton(vertical10x10);
        three_6->setObjectName(QStringLiteral("three_6"));
        three_6->setFont(font1);
        three_6->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout_3->addWidget(three_6);

        four_6 = new QPushButton(vertical10x10);
        four_6->setObjectName(QStringLiteral("four_6"));
        four_6->setFont(font1);
        four_6->setStyleSheet(QStringLiteral(""));

        horizontalLayout_3->addWidget(four_6);

        five_6 = new QPushButton(vertical10x10);
        five_6->setObjectName(QStringLiteral("five_6"));
        five_6->setFont(font1);
        five_6->setStyleSheet(QStringLiteral(""));

        horizontalLayout_3->addWidget(five_6);

        six_6 = new QPushButton(vertical10x10);
        six_6->setObjectName(QStringLiteral("six_6"));
        six_6->setFont(font1);
        six_6->setStyleSheet(QStringLiteral(""));

        horizontalLayout_3->addWidget(six_6);

        pushButton_9 = new QPushButton(vertical10x10);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setFont(font1);

        horizontalLayout_3->addWidget(pushButton_9);

        pushButton_10 = new QPushButton(vertical10x10);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setFont(font1);

        horizontalLayout_3->addWidget(pushButton_10);

        pushButton_11 = new QPushButton(vertical10x10);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setFont(font1);

        horizontalLayout_3->addWidget(pushButton_11);

        pushButton_12 = new QPushButton(vertical10x10);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setFont(font1);

        horizontalLayout_3->addWidget(pushButton_12);

        horizontal12x12 = new QGroupBox(othelloGroup);
        horizontal12x12->setObjectName(QStringLiteral("horizontal12x12"));
        horizontal12x12->setGeometry(QRect(30, 50, 61, 580));
        horizontal12x12->setStyleSheet(QLatin1String("border:none\n"
""));
        verticalLayout_4 = new QVBoxLayout(horizontal12x12);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        one_7 = new QPushButton(horizontal12x12);
        one_7->setObjectName(QStringLiteral("one_7"));
        one_7->setFont(font1);
        one_7->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout_4->addWidget(one_7);

        two_7 = new QPushButton(horizontal12x12);
        two_7->setObjectName(QStringLiteral("two_7"));
        two_7->setFont(font1);
        two_7->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout_4->addWidget(two_7);

        three_7 = new QPushButton(horizontal12x12);
        three_7->setObjectName(QStringLiteral("three_7"));
        three_7->setFont(font1);
        three_7->setStyleSheet(QStringLiteral("border:none"));

        verticalLayout_4->addWidget(three_7);

        four_7 = new QPushButton(horizontal12x12);
        four_7->setObjectName(QStringLiteral("four_7"));
        four_7->setFont(font1);
        four_7->setStyleSheet(QStringLiteral(""));

        verticalLayout_4->addWidget(four_7);

        five_7 = new QPushButton(horizontal12x12);
        five_7->setObjectName(QStringLiteral("five_7"));
        five_7->setFont(font1);
        five_7->setStyleSheet(QStringLiteral(""));

        verticalLayout_4->addWidget(five_7);

        six_7 = new QPushButton(horizontal12x12);
        six_7->setObjectName(QStringLiteral("six_7"));
        six_7->setFont(font1);
        six_7->setStyleSheet(QStringLiteral(""));

        verticalLayout_4->addWidget(six_7);

        pushButton_13 = new QPushButton(horizontal12x12);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setFont(font1);

        verticalLayout_4->addWidget(pushButton_13);

        pushButton_14 = new QPushButton(horizontal12x12);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setFont(font1);

        verticalLayout_4->addWidget(pushButton_14);

        pushButton_15 = new QPushButton(horizontal12x12);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        pushButton_15->setFont(font1);

        verticalLayout_4->addWidget(pushButton_15);

        pushButton_16 = new QPushButton(horizontal12x12);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        pushButton_16->setFont(font1);

        verticalLayout_4->addWidget(pushButton_16);

        pushButton_17 = new QPushButton(horizontal12x12);
        pushButton_17->setObjectName(QStringLiteral("pushButton_17"));
        pushButton_17->setFont(font1);

        verticalLayout_4->addWidget(pushButton_17);

        pushButton_18 = new QPushButton(horizontal12x12);
        pushButton_18->setObjectName(QStringLiteral("pushButton_18"));
        pushButton_18->setFont(font1);

        verticalLayout_4->addWidget(pushButton_18);

        vertical12x12 = new QGroupBox(othelloGroup);
        vertical12x12->setObjectName(QStringLiteral("vertical12x12"));
        vertical12x12->setGeometry(QRect(70, 25, 560, 61));
        vertical12x12->setStyleSheet(QLatin1String("border:none\n"
""));
        horizontalLayout_4 = new QHBoxLayout(vertical12x12);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        one_8 = new QPushButton(vertical12x12);
        one_8->setObjectName(QStringLiteral("one_8"));
        one_8->setFont(font1);
        one_8->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout_4->addWidget(one_8);

        two_8 = new QPushButton(vertical12x12);
        two_8->setObjectName(QStringLiteral("two_8"));
        two_8->setFont(font1);
        two_8->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout_4->addWidget(two_8);

        three_8 = new QPushButton(vertical12x12);
        three_8->setObjectName(QStringLiteral("three_8"));
        three_8->setFont(font1);
        three_8->setStyleSheet(QStringLiteral("border:none"));

        horizontalLayout_4->addWidget(three_8);

        four_8 = new QPushButton(vertical12x12);
        four_8->setObjectName(QStringLiteral("four_8"));
        four_8->setFont(font1);
        four_8->setStyleSheet(QStringLiteral(""));

        horizontalLayout_4->addWidget(four_8);

        five_8 = new QPushButton(vertical12x12);
        five_8->setObjectName(QStringLiteral("five_8"));
        five_8->setFont(font1);
        five_8->setStyleSheet(QStringLiteral(""));

        horizontalLayout_4->addWidget(five_8);

        six_8 = new QPushButton(vertical12x12);
        six_8->setObjectName(QStringLiteral("six_8"));
        six_8->setFont(font1);
        six_8->setStyleSheet(QStringLiteral(""));

        horizontalLayout_4->addWidget(six_8);

        pushButton_19 = new QPushButton(vertical12x12);
        pushButton_19->setObjectName(QStringLiteral("pushButton_19"));
        pushButton_19->setFont(font1);

        horizontalLayout_4->addWidget(pushButton_19);

        pushButton_20 = new QPushButton(vertical12x12);
        pushButton_20->setObjectName(QStringLiteral("pushButton_20"));
        pushButton_20->setFont(font1);

        horizontalLayout_4->addWidget(pushButton_20);

        pushButton_21 = new QPushButton(vertical12x12);
        pushButton_21->setObjectName(QStringLiteral("pushButton_21"));
        pushButton_21->setFont(font1);

        horizontalLayout_4->addWidget(pushButton_21);

        pushButton_22 = new QPushButton(vertical12x12);
        pushButton_22->setObjectName(QStringLiteral("pushButton_22"));
        pushButton_22->setFont(font1);

        horizontalLayout_4->addWidget(pushButton_22);

        pushButton_23 = new QPushButton(vertical12x12);
        pushButton_23->setObjectName(QStringLiteral("pushButton_23"));
        pushButton_23->setFont(font1);

        horizontalLayout_4->addWidget(pushButton_23);

        pushButton_24 = new QPushButton(vertical12x12);
        pushButton_24->setObjectName(QStringLiteral("pushButton_24"));
        pushButton_24->setFont(font1);

        horizontalLayout_4->addWidget(pushButton_24);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        othelloGroup->setTitle(QString());
        settingUpGame->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "Nastavte hru", 0));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0));
        label_3->setText(QApplication::translate("MainWindow", "Po\304\215et hr\303\241\304\215\305\257", 0));
        numberOfPlayers->clear();
        numberOfPlayers->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
        );
        label_2->setText(QApplication::translate("MainWindow", "velikost herni desky", 0));
        boardSize->clear();
        boardSize->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "8x8", 0)
         << QApplication::translate("MainWindow", "6x6", 0)
         << QApplication::translate("MainWindow", "10x10", 0)
         << QApplication::translate("MainWindow", "12x12", 0)
        );
        loadButton->setText(QApplication::translate("MainWindow", "Nahr\303\241t Hru", 0));
        exitButton->setText(QApplication::translate("MainWindow", "Konec", 0));
        ingamePannel->setTitle(QString());
        exitGameButton->setText(QApplication::translate("MainWindow", "Ukon\304\215it Hru", 0));
        undoGameButton->setText(QApplication::translate("MainWindow", "Undo", 0));
        saveGameButton->setText(QApplication::translate("MainWindow", "Ulo\305\276it Hru", 0));
        displayPlayerLabel->setText(QApplication::translate("MainWindow", "Hr\303\241\304\215 na tahu", 0));
        displayPlayerButton->setText(QString());
        whiteScoreLabel->setText(QApplication::translate("MainWindow", "B\303\255l\303\275", 0));
        blackScoreLabel->setText(QApplication::translate("MainWindow", "\304\214ern\303\275", 0));
        redoGameButton->setText(QApplication::translate("MainWindow", "Redo", 0));
        settingUpAi->setTitle(QString());
        label_4->setText(QApplication::translate("MainWindow", "Vyberte obt\303\255\305\276nost protihr\303\241\304\215e", 0));
        difficulty->clear();
        difficulty->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Easy", 0)
         << QApplication::translate("MainWindow", "Medium", 0)
        );
        startPVE->setText(QApplication::translate("MainWindow", "Start", 0));
        horizontal6x6->setTitle(QString());
        one->setText(QApplication::translate("MainWindow", "1", 0));
        two->setText(QApplication::translate("MainWindow", "2", 0));
        three->setText(QApplication::translate("MainWindow", "3", 0));
        four->setText(QApplication::translate("MainWindow", "4", 0));
        five->setText(QApplication::translate("MainWindow", "5", 0));
        six->setText(QApplication::translate("MainWindow", "6", 0));
        vertical6x6->setTitle(QString());
        one_2->setText(QApplication::translate("MainWindow", "A", 0));
        two_2->setText(QApplication::translate("MainWindow", "B", 0));
        three_2->setText(QApplication::translate("MainWindow", "C", 0));
        four_2->setText(QApplication::translate("MainWindow", "D", 0));
        five_2->setText(QApplication::translate("MainWindow", "E", 0));
        six_2->setText(QApplication::translate("MainWindow", "F", 0));
        horizontal8x8->setTitle(QString());
        one_3->setText(QApplication::translate("MainWindow", "1", 0));
        two_3->setText(QApplication::translate("MainWindow", "2", 0));
        three_3->setText(QApplication::translate("MainWindow", "3", 0));
        four_3->setText(QApplication::translate("MainWindow", "4", 0));
        five_3->setText(QApplication::translate("MainWindow", "5", 0));
        six_3->setText(QApplication::translate("MainWindow", "6", 0));
        pushButton->setText(QApplication::translate("MainWindow", "7", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "8", 0));
        vertical8x8->setTitle(QString());
        one_4->setText(QApplication::translate("MainWindow", "A", 0));
        two_4->setText(QApplication::translate("MainWindow", "B", 0));
        three_4->setText(QApplication::translate("MainWindow", "C", 0));
        four_4->setText(QApplication::translate("MainWindow", "D", 0));
        five_4->setText(QApplication::translate("MainWindow", "E", 0));
        six_4->setText(QApplication::translate("MainWindow", "F", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "G", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "H", 0));
        horizontal10x10->setTitle(QString());
        one_5->setText(QApplication::translate("MainWindow", "1", 0));
        two_5->setText(QApplication::translate("MainWindow", "2", 0));
        three_5->setText(QApplication::translate("MainWindow", "3", 0));
        four_5->setText(QApplication::translate("MainWindow", "4", 0));
        five_5->setText(QApplication::translate("MainWindow", "5", 0));
        six_5->setText(QApplication::translate("MainWindow", "6", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "7", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "8", 0));
        pushButton_7->setText(QApplication::translate("MainWindow", "9", 0));
        pushButton_8->setText(QApplication::translate("MainWindow", "10", 0));
        vertical10x10->setTitle(QString());
        one_6->setText(QApplication::translate("MainWindow", "A", 0));
        two_6->setText(QApplication::translate("MainWindow", "B", 0));
        three_6->setText(QApplication::translate("MainWindow", "C", 0));
        four_6->setText(QApplication::translate("MainWindow", "D", 0));
        five_6->setText(QApplication::translate("MainWindow", "E", 0));
        six_6->setText(QApplication::translate("MainWindow", "F", 0));
        pushButton_9->setText(QApplication::translate("MainWindow", "G", 0));
        pushButton_10->setText(QApplication::translate("MainWindow", "H", 0));
        pushButton_11->setText(QApplication::translate("MainWindow", "I", 0));
        pushButton_12->setText(QApplication::translate("MainWindow", "J", 0));
        horizontal12x12->setTitle(QString());
        one_7->setText(QApplication::translate("MainWindow", "1", 0));
        two_7->setText(QApplication::translate("MainWindow", "2", 0));
        three_7->setText(QApplication::translate("MainWindow", "3", 0));
        four_7->setText(QApplication::translate("MainWindow", "4", 0));
        five_7->setText(QApplication::translate("MainWindow", "5", 0));
        six_7->setText(QApplication::translate("MainWindow", "6", 0));
        pushButton_13->setText(QApplication::translate("MainWindow", "7", 0));
        pushButton_14->setText(QApplication::translate("MainWindow", "8", 0));
        pushButton_15->setText(QApplication::translate("MainWindow", "9", 0));
        pushButton_16->setText(QApplication::translate("MainWindow", "10", 0));
        pushButton_17->setText(QApplication::translate("MainWindow", "11", 0));
        pushButton_18->setText(QApplication::translate("MainWindow", "12", 0));
        vertical12x12->setTitle(QString());
        one_8->setText(QApplication::translate("MainWindow", "A", 0));
        two_8->setText(QApplication::translate("MainWindow", "B", 0));
        three_8->setText(QApplication::translate("MainWindow", "C", 0));
        four_8->setText(QApplication::translate("MainWindow", "D", 0));
        five_8->setText(QApplication::translate("MainWindow", "E", 0));
        six_8->setText(QApplication::translate("MainWindow", "F", 0));
        pushButton_19->setText(QApplication::translate("MainWindow", "G", 0));
        pushButton_20->setText(QApplication::translate("MainWindow", "H", 0));
        pushButton_21->setText(QApplication::translate("MainWindow", "I", 0));
        pushButton_22->setText(QApplication::translate("MainWindow", "J", 0));
        pushButton_23->setText(QApplication::translate("MainWindow", "K", 0));
        pushButton_24->setText(QApplication::translate("MainWindow", "L", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
