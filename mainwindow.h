#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "StateMachine.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
class QMenuBar;
class QGroupBox;
class QTextEdit;
class QDialogButtonBox;
class QMenu;
class QVBoxLayout;
class QSpinBox;
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QDialog
{
   Q_OBJECT
public:
   MainWindow();
   void mainMenu(QGroupBox *widget);

   void enableButtons(bool enable);
   void setLogger(const QString& text);

   void createGameSpace();
   void createHighscoreMenu();
   void createSettingsMenu();

   QGroupBox *highscoreGroupBox = nullptr;
   QGroupBox *settingsGroupBox = nullptr;

private:
   //General Purpose***********************************************************
   QVBoxLayout *mainLayout;
   QPushButton *backButton;
   enum {NumMenuButtons = 4, numHighscoreLabels = 10};

   //Create Menu***************************************************************
   void createMenu();
   QMenuBar *menuBar;
   QMenu *fileMenu;
   QAction *exitAction;
   QAction *returnAction;

   //Create Menu Buttons*******************************************************
   void createMenuButtons();
   QGroupBox *menuButtonsGroupBox = nullptr;
   QPushButton *buttons[NumMenuButtons];

   //Create Logger*************************************************************
   void createLogger();
   QGroupBox *loggerGroupBox = nullptr;
   QTextEdit *logDisplay;

   //Create Game Space*********************************************************
   void createGameGroupBox();
   QGroupBox *gameGroupBox = nullptr;
   QTextEdit *gameDisplay;

   //Create Highscore Menu****************************************************
   void createHighscoreGroupBox();
   QLabel *rank[numHighscoreLabels];

   //Create Settings Menu******************************************************
   void createSettingsGroupBox();
   QPushButton *saveButton;
   QSpinBox *widthInt;
   QSpinBox *heightInt;

   //**************************************************************************
   StateMachine *pStateMachine;

   //**************************************************************************
   int x = 200, y = 400;

private slots:

   void createMainMenu();
   void buttonStart();
   void buttonHighscore();
   void buttonSettings();
   void buttonQuit();
   void buttonBack();
   void buttonSaveSettings();

};

#endif // MAINWINDOW_H
