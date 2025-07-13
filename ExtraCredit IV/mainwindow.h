#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QInputDialog>
#include <QDir>
#include <QDateTime>
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Graph<std::string> graph;
    QString dictionaryPath;
    QString userName;

    std::string startWord;
    std::string endWord;
    std::vector<std::string> solutionPath;
    size_t wordLength;

    std::vector<std::string> allWords;
    std::vector<std::string> userMoves;

    QDateTime gameStartTime;
    int hintsCount;

private slots:
    void pathButtonClicked();
    void browseDictionaryFile_1();
    void browseDictionaryFile_2();

    void submitButtonClicked();
    void startNewGame();
    bool validateUserPath(const std::vector<std::string>& userPath);
    bool isOneLetterDifferent(const std::string& word1, const std::string& word2); // Helper for path validation

    void hintButtonClicked();
    void gameSaveButtonClicked();
    QString buildHintHtml(const std::string& sourceWord, const std::string& targetWord);

    void analyticsButtonClicked();
};
#endif // MAINWINDOW_H
