#include "MainWindow.h"
#include "statemachine.h"

#include <QtWidgets>
#include <string>

MainWindow::MainWindow()

{
   pStateMachine = new StateMachine(this);

   resize(x,y);

   createMenu();
   createMenuButtons();
   createLogger();

   mainLayout = new QVBoxLayout;
   mainLayout->setMenuBar(menuBar);
   mainLayout->addWidget(menuButtonsGroupBox);
   mainLayout->addWidget(loggerGroupBox);

   setLayout(mainLayout);
   setWindowTitle(tr("Snake V0.1"));

   pStateMachine->handleEvent(EVT_INITIALIZED);

}

void MainWindow::createMenu()
{
   menuBar = new QMenuBar;
   fileMenu = new QMenu(tr("&File"), this);
   exitAction = fileMenu->addAction(tr("E&xit"));
   returnAction = fileMenu->addAction(tr("&Return"));
   returnAction->setEnabled(false);
   menuBar->addMenu(fileMenu);
   connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
   connect(returnAction, SIGNAL(triggered()), this, SLOT(createMainMenu()));
}

void MainWindow::enableButtons(bool enable) {
   for (int i = 0; i < NumMenuButtons; i++) {
      buttons[i]->setEnabled(enable);
   }
}

void MainWindow::createMenuButtons()
{
   menuButtonsGroupBox = new QGroupBox(tr("Main Menu"));
   QVBoxLayout *layoutMainMenu = new QVBoxLayout;

   buttons[0] = new QPushButton(tr("Start"));
   layoutMainMenu->addWidget(buttons[0]);
   connect(buttons[0], SIGNAL(released()), this, SLOT(buttonStart()));

   buttons[1] = new QPushButton(tr("Highscore"));
   layoutMainMenu->addWidget(buttons[1]);
   connect(buttons[1], SIGNAL(released()), this, SLOT(buttonHighscore()));

   buttons[2] = new QPushButton(tr("Settings"));
   layoutMainMenu->addWidget(buttons[2]);
   connect(buttons[2], SIGNAL(released()), this, SLOT(buttonSettings()));

   buttons[3] = new QPushButton(tr("Quit"));
   layoutMainMenu->addWidget(buttons[3]);
   connect(buttons[3], SIGNAL(released()), this, SLOT(buttonQuit()));

   enableButtons(false);
   menuButtonsGroupBox->setLayout(layoutMainMenu);
}

void MainWindow::createLogger()
{
   loggerGroupBox = new QGroupBox(tr("Logging"));
   QHBoxLayout *layoutLogger = new QHBoxLayout;

   logDisplay = new QTextEdit("Logging started", this);
   logDisplay->setOverwriteMode(false);
   logDisplay->setReadOnly(true);

   layoutLogger->addWidget(logDisplay);
   loggerGroupBox->setLayout(layoutLogger);
}

void MainWindow::setLogger(const QString &text)
{
   static int i;
   logDisplay->moveCursor(QTextCursor::End);
   logDisplay->insertPlainText("\n" + QString::number(i) + ": " + text);
   logDisplay->moveCursor(QTextCursor::End);
   i++;
}

void MainWindow::createGameGroupBox()
{
   gameGroupBox = new QGroupBox(tr("Game"));
   QHBoxLayout *layoutGame = new QHBoxLayout;

   gameDisplay = new QTextEdit("", this);
   gameDisplay->setOverwriteMode(false);
   gameDisplay->setReadOnly(true);

   layoutGame->addWidget(gameDisplay);
   gameGroupBox->setLayout(layoutGame);
}

void MainWindow::createGameSpace()
{
   createGameGroupBox();

   returnAction->setEnabled(true);
   mainLayout->replaceWidget(menuButtonsGroupBox, gameGroupBox);

   delete menuButtonsGroupBox;
}

void MainWindow::createHighscoreGroupBox()
{
   highscoreGroupBox = new QGroupBox(tr("Highscores"));
   QGridLayout *layoutHighscore = new QGridLayout;

   for(int i = 1; i <= 10; i++)
   {
      rank[i] = new QLabel;
      rank[i]->setText(QString::number(i)+":");
      layoutHighscore->addWidget(rank[i], i-1, 0);
   }
   backButton = new QPushButton(tr("back"));
   connect(backButton, SIGNAL(released()), this, SLOT(buttonBack()));

   layoutHighscore->addWidget(backButton, 10, 0);

   highscoreGroupBox->setLayout(layoutHighscore);
}

void MainWindow::createHighscoreMenu()
{
   createHighscoreGroupBox();

   mainLayout->replaceWidget(menuButtonsGroupBox, highscoreGroupBox);

   delete menuButtonsGroupBox;
}

void MainWindow::createSettingsGroupBox()
{
   settingsGroupBox = new QGroupBox(tr("Settings"));
   QGridLayout *settingsLayout = new QGridLayout;

   QLabel *labelWidth = new QLabel;
   widthInt = new QSpinBox;

   QLabel *labelHeight = new QLabel;
   heightInt = new QSpinBox;

   backButton = new QPushButton(tr("Back"));
   connect(backButton, SIGNAL(released()), this, SLOT(buttonBack()));

   saveButton = new QPushButton(tr("Save"));
   connect(saveButton, SIGNAL(released()), this, SLOT(buttonSaveSettings()));

   labelWidth->setText("Width");
   labelHeight->setText("Height");

   widthInt->setValue(x);
   widthInt->setMinimum(150);
   widthInt->setMaximum(1000);
   widthInt->setSingleStep(50);

   heightInt->setValue(y);
   heightInt->setMinimum(300);
   heightInt->setMaximum(500);
   heightInt->setSingleStep(50);

   settingsLayout->addWidget(labelWidth, 0, 0);
   settingsLayout->addWidget(widthInt, 0, 1);
   settingsLayout->addWidget(labelHeight, 1, 0);
   settingsLayout->addWidget(heightInt, 1, 1);
   settingsLayout->addWidget(backButton, 2, 0);
   settingsLayout->addWidget(saveButton, 2, 1);

   settingsGroupBox->setLayout(settingsLayout);

}

void MainWindow::createSettingsMenu()
{
   createSettingsGroupBox();

   mainLayout->replaceWidget(menuButtonsGroupBox, settingsGroupBox);

   delete menuButtonsGroupBox;
}

void MainWindow::createMainMenu()
{
   createMenuButtons();

   returnAction->setEnabled(false);
   mainLayout->replaceWidget(gameGroupBox, menuButtonsGroupBox);

   delete gameGroupBox;

   pStateMachine->handleEvent(EVT_INITIALIZED);
}

void MainWindow::mainMenu(QGroupBox *widget)
{
   createMenuButtons();
   mainLayout->replaceWidget(widget, menuButtonsGroupBox);
   delete widget;
}

void MainWindow::buttonSaveSettings()
{
   x = widthInt->value();
   y = heightInt->value();
   this->setFixedSize(x, y);
}

void MainWindow::buttonStart()
{
   pStateMachine->handleEvent(EVT_START);
}

void MainWindow::buttonHighscore()
{
   pStateMachine->handleEvent(EVT_HIGHSCORE);
}

void MainWindow::buttonSettings()
{
   pStateMachine->handleEvent(EVT_SETTINGS);
}

void MainWindow::buttonQuit()
{
   pStateMachine->handleEvent(EVT_QUIT);
}

void MainWindow::buttonBack()
{
   pStateMachine->handleEvent(EVT_BACK_MAIN);
}
