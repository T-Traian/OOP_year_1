/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *startWordEdit;
    QLineEdit *targetWordEdit;
    QPushButton *pathPushButton;
    QTextEdit *textEdit;
    QPushButton *browseButton_1;
    QLineEdit *dictionaryPathLineEdit_1;
    QLineEdit *statusEdit_2;
    QLabel *label_7;
    QWidget *tab_2;
    QPushButton *browseButton_2;
    QLineEdit *dictionaryPathLineEdit_2;
    QLabel *startWordDisplayLabel;
    QLabel *endWordDisplayLabel;
    QLineEdit *userStartWord;
    QLineEdit *userEndWord;
    QTextEdit *userInputPath;
    QLabel *label_5;
    QPushButton *submitButton;
    QLabel *label_4;
    QLineEdit *statusEdit;
    QPushButton *startGameButton;
    QSpinBox *wordSpinBox;
    QLabel *label_6;
    QPushButton *hintButton;
    QLabel *hintDisplayLabel;
    QPushButton *gameSaveButton;
    QWidget *tab_3;
    QLabel *label_8;
    QTextEdit *analyticsUserNameInput;
    QPushButton *analyticsPushButton;
    QTextEdit *analyticsResultsDisplay;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1149, 776);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setSizeIncrement(QSize(0, 0));
        QFont font;
        font.setPointSize(16);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 0, 1111, 731));
        tab = new QWidget();
        tab->setObjectName("tab");
        label = new QLabel(tab);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 621, 51));
        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 180, 181, 51));
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(570, 190, 171, 41));
        startWordEdit = new QLineEdit(tab);
        startWordEdit->setObjectName("startWordEdit");
        startWordEdit->setGeometry(QRect(270, 180, 113, 41));
        targetWordEdit = new QLineEdit(tab);
        targetWordEdit->setObjectName("targetWordEdit");
        targetWordEdit->setGeometry(QRect(740, 190, 113, 41));
        pathPushButton = new QPushButton(tab);
        pathPushButton->setObjectName("pathPushButton");
        pathPushButton->setGeometry(QRect(270, 250, 171, 51));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(270, 310, 591, 141));
        browseButton_1 = new QPushButton(tab);
        browseButton_1->setObjectName("browseButton_1");
        browseButton_1->setGeometry(QRect(470, 50, 181, 51));
        dictionaryPathLineEdit_1 = new QLineEdit(tab);
        dictionaryPathLineEdit_1->setObjectName("dictionaryPathLineEdit_1");
        dictionaryPathLineEdit_1->setGeometry(QRect(270, 110, 581, 51));
        statusEdit_2 = new QLineEdit(tab);
        statusEdit_2->setObjectName("statusEdit_2");
        statusEdit_2->setGeometry(QRect(200, 510, 731, 71));
        label_7 = new QLabel(tab);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(120, 520, 61, 41));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        browseButton_2 = new QPushButton(tab_2);
        browseButton_2->setObjectName("browseButton_2");
        browseButton_2->setGeometry(QRect(30, 40, 191, 51));
        dictionaryPathLineEdit_2 = new QLineEdit(tab_2);
        dictionaryPathLineEdit_2->setObjectName("dictionaryPathLineEdit_2");
        dictionaryPathLineEdit_2->setGeometry(QRect(240, 40, 461, 61));
        startWordDisplayLabel = new QLabel(tab_2);
        startWordDisplayLabel->setObjectName("startWordDisplayLabel");
        startWordDisplayLabel->setGeometry(QRect(90, 220, 141, 41));
        endWordDisplayLabel = new QLabel(tab_2);
        endWordDisplayLabel->setObjectName("endWordDisplayLabel");
        endWordDisplayLabel->setGeometry(QRect(650, 230, 131, 31));
        userStartWord = new QLineEdit(tab_2);
        userStartWord->setObjectName("userStartWord");
        userStartWord->setGeometry(QRect(240, 220, 121, 41));
        userEndWord = new QLineEdit(tab_2);
        userEndWord->setObjectName("userEndWord");
        userEndWord->setGeometry(QRect(780, 220, 131, 41));
        userInputPath = new QTextEdit(tab_2);
        userInputPath->setObjectName("userInputPath");
        userInputPath->setGeometry(QRect(240, 330, 671, 51));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 330, 221, 51));
        submitButton = new QPushButton(tab_2);
        submitButton->setObjectName("submitButton");
        submitButton->setGeometry(QRect(430, 450, 191, 31));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 510, 61, 51));
        statusEdit = new QLineEdit(tab_2);
        statusEdit->setObjectName("statusEdit");
        statusEdit->setGeometry(QRect(130, 500, 851, 61));
        startGameButton = new QPushButton(tab_2);
        startGameButton->setObjectName("startGameButton");
        startGameButton->setGeometry(QRect(450, 140, 201, 61));
        wordSpinBox = new QSpinBox(tab_2);
        wordSpinBox->setObjectName("wordSpinBox");
        wordSpinBox->setGeometry(QRect(870, 50, 101, 41));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(730, 50, 131, 41));
        hintButton = new QPushButton(tab_2);
        hintButton->setObjectName("hintButton");
        hintButton->setGeometry(QRect(20, 410, 91, 31));
        hintDisplayLabel = new QLabel(tab_2);
        hintDisplayLabel->setObjectName("hintDisplayLabel");
        hintDisplayLabel->setGeometry(QRect(120, 410, 801, 31));
        gameSaveButton = new QPushButton(tab_2);
        gameSaveButton->setObjectName("gameSaveButton");
        gameSaveButton->setGeometry(QRect(460, 590, 131, 41));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_8 = new QLabel(tab_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(120, 60, 281, 41));
        analyticsUserNameInput = new QTextEdit(tab_3);
        analyticsUserNameInput->setObjectName("analyticsUserNameInput");
        analyticsUserNameInput->setGeometry(QRect(400, 50, 361, 51));
        analyticsPushButton = new QPushButton(tab_3);
        analyticsPushButton->setObjectName("analyticsPushButton");
        analyticsPushButton->setGeometry(QRect(440, 140, 201, 51));
        analyticsResultsDisplay = new QTextEdit(tab_3);
        analyticsResultsDisplay->setObjectName("analyticsResultsDisplay");
        analyticsResultsDisplay->setGeometry(QRect(150, 280, 851, 351));
        analyticsResultsDisplay->setReadOnly(true);
        tabWidget->addTab(tab_3, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1149, 34));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Playing automatic mode, please follow the instructions:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Enter starting word:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Enter target word:", nullptr));
        pathPushButton->setText(QCoreApplication::translate("MainWindow", "Calculate Path", nullptr));
        browseButton_1->setText(QCoreApplication::translate("MainWindow", "Browse Dictionary", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Status:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Automatic", nullptr));
        browseButton_2->setText(QCoreApplication::translate("MainWindow", "Browse Dictionary", nullptr));
        startWordDisplayLabel->setText(QCoreApplication::translate("MainWindow", "Starting Word:", nullptr));
        endWordDisplayLabel->setText(QCoreApplication::translate("MainWindow", "Ending Word:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Please enter the path:", nullptr));
        submitButton->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Status:", nullptr));
        statusEdit->setText(QString());
        startGameButton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Word Length:", nullptr));
        hintButton->setText(QCoreApplication::translate("MainWindow", "HINT", nullptr));
        hintDisplayLabel->setText(QString());
        gameSaveButton->setText(QCoreApplication::translate("MainWindow", "Save Game", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Standard", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Enter user name for analytics:", nullptr));
        analyticsPushButton->setText(QCoreApplication::translate("MainWindow", "Load Analytics", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Analytics", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
