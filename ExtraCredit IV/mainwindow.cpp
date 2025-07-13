#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    dictionaryPath = "dictionary.txt";
    graph.buildGraph(dictionaryPath);
    ui->setupUi(this);

    //Button connection
    connect(ui->pathPushButton, &QPushButton::clicked, this, &MainWindow::pathButtonClicked);
    connect(ui->browseButton_2, &QPushButton::clicked, this, &MainWindow::browseDictionaryFile_2);
    connect(ui->browseButton_1, &QPushButton::clicked, this, &MainWindow::browseDictionaryFile_1);
    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::submitButtonClicked);
    connect(ui->startGameButton, &QPushButton::clicked, this, &MainWindow::startNewGame);
    connect(ui->hintButton, &QPushButton::clicked, this, &MainWindow::hintButtonClicked);
    connect(ui->gameSaveButton, &QPushButton::clicked, this, &MainWindow::gameSaveButtonClicked);
    connect(ui->analyticsPushButton, &QPushButton::clicked, this, &MainWindow::analyticsButtonClicked);

    //User name prompt
    bool ok;
    QString name = QInputDialog::getText(this, tr("Welcome to Word Ladder!"),
                                         tr("Please enter your name:"), QLineEdit::Normal,
                                         "Player", &ok);

    if (ok && !name.isEmpty()) {
        userName = name.trimmed();
        ui->statusEdit->setText("Welcome, " + userName + "! Browse a dictionary to start.");
        ui->statusEdit_2->setText("Welcome, " + userName + "! Browse a dictionary to start.");
    } else {
        userName = "Guest";
        ui->statusEdit->setText("Welcome, Guest! Browse a dictionary to start.");
        ui->statusEdit_2->setText("Welcome, Guest! Browse a dictionary to start.");
        QMessageBox::information(this, "No Name Entered", "You didn't enter a name. You will be 'Guest'.");
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::pathButtonClicked(){
    QString startWord = ui->startWordEdit->text();
    QString endWord = ui->targetWordEdit->text();

    if (startWord.isEmpty() || endWord.isEmpty()) {
        ui->textEdit->setText("Please enter both start and target words.");
        return;
    }

    if (startWord.length() != endWord.length()) {
        ui->textEdit->setText("Words must be the same length for a word ladder.");
        return;
    }

    std::vector<std::string> path = graph.shortestPath(startWord.toStdString(), endWord.toStdString());

    if (path.empty()) {
        ui->textEdit->setText("No path found.");
    }
    else {
        QStringList pathList;
        for (const std::string& word : path) {
            pathList.append(QString::fromStdString(word));
        }
        ui->textEdit->setText(pathList.join(" -> "));
    }
}

void MainWindow::browseDictionaryFile_2(){
    // Open a file dialog to let the user select a dictionary file
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Dictionary File"), QDir::currentPath(),tr("Text Files (*.txt);;All Files (*.*)"));

    if (!filePath.isEmpty()) {
        ui->dictionaryPathLineEdit_2->setText(filePath); // Display the selected path
        dictionaryPath = filePath; // Store the selected path in your member variable

        // Clear any previous graph data before rebuilding
        graph = Graph<std::string>(); // Reinitialize the graph (or add a clear method to Graph)

        graph.buildGraph(dictionaryPath);
        ui->statusEdit->setText("Dictionary loaded and graph built successfully. Enter word length.");

        std::vector<std::string> words = graph.getAllNodes();
        allWords = words;
    }
}

void MainWindow::browseDictionaryFile_1(){
    // Open a file dialog to let the user select a dictionary file
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Dictionary File"), QDir::currentPath(),tr("Text Files (*.txt);;All Files (*.*)"));

    if (!filePath.isEmpty()) {
        ui->dictionaryPathLineEdit_1->setText(filePath); // Display the selected path
        dictionaryPath = filePath; // Store the selected path in your member variable

        // Clear any previous graph data before rebuilding
        graph = Graph<std::string>(); // Reinitialize the graph (or add a clear method to Graph)

        graph.buildGraph(dictionaryPath);
        ui->textEdit->setText("Dictionary loaded and graph built successfully. Enter words to find a ladder.");
    }
}

void MainWindow::startNewGame(){
    if (allWords.size()<2){
        ui->statusEdit->setText("Dictionary too small to play! Needs at least two words.");
        return;
    }
    startWord.clear();
    endWord.clear();
    solutionPath.clear();
    wordLength = ui->wordSpinBox->value();
    ui->userInputPath->clear();
    hintsCount = 0;
    gameStartTime = QDateTime::currentDateTime();

    if (wordLength == 0){
        ui->statusEdit->setText("Please enter the word length to continue.");
        return;
    }

    std::string tempStartWord, tempEndWord;
    std::vector<std::string> path;
    const int MAX_ATTEMPTS = 500;
    int attempts = 0;

    // Loop until a valid, connected path is found
    do {
        // Pick random words
        tempStartWord = allWords[QRandomGenerator::global()->bounded(allWords.size())];
        tempEndWord = allWords[QRandomGenerator::global()->bounded(allWords.size())];


        if (tempStartWord == tempEndWord || tempStartWord.length() != tempEndWord.length() || tempStartWord.length()!=wordLength || tempEndWord.length()!=wordLength) {
            attempts++;
            continue;
        }

        path = graph.shortestPath(tempStartWord, tempEndWord);
        attempts++;
    } while (path.empty() && attempts < MAX_ATTEMPTS);

    if (path.empty()) {
        ui->statusEdit->setText("Could not find a connected word ladder. Try a different dictionary or restart.");
        ui->userStartWord->clear();
        ui->userEndWord->clear();
    } else {
        startWord = tempStartWord;
        endWord = tempEndWord;
        solutionPath = path;

        ui->userStartWord->setText(QString::fromStdString(startWord));
        ui->userEndWord->setText(QString::fromStdString(endWord));
        ui->statusEdit->setText("Find a path from " + QString::fromStdString(startWord) + " to " + QString::fromStdString(endWord) + "!");
        ui->userInputPath->setFocus();
    }
}

bool MainWindow::validateUserPath(const std::vector<std::string>& userPath){
    if (userPath.empty()) {
        return false;
    }

    if (userPath.front() != startWord || userPath.back() != endWord) {
        return false;
    }

    for (size_t i = 0; i < userPath.size(); ++i) {
        const std::string& currentWord = userPath[i];

        if (!graph.hasNode(currentWord)) {
            qDebug() << "Validation Error: User path word not in dictionary:" << QString::fromStdString(currentWord);
            return false;
        }

        // Check connection to the next word (if not the last word in the path)
        if (i + 1 < userPath.size()) {
            const std::string& nextWord = userPath[i+1];
            // Check if they are one letter different
            if (!isOneLetterDifferent(currentWord, nextWord)) {
                qDebug() << "Validation Error: Words not one letter different or different length:" << QString::fromStdString(currentWord) << "and" << QString::fromStdString(nextWord);
                return false;
            }
        }
    }
    return true;
}

bool MainWindow::isOneLetterDifferent(const std::string& word1, const std::string& word2) {
    if (word1.length() != word2.length()) {
        return false;
    }
    int diffCount = 0;
    for (size_t i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i]) {
            diffCount++;
        }
    }
    return diffCount == 1;
}

QString MainWindow::buildHintHtml(const std::string& sourceWord, const std::string& targetWord) {
    if (sourceWord.length() != targetWord.length()) {
        return "N/A";
    }

    for (size_t i = 0; i < sourceWord.length(); ++i) {
        if (sourceWord[i] != targetWord[i]) {
            QString diffChar = QChar(targetWord[i]);
            return "<span style='color: red; font-weight: bold;'>" + diffChar + "</span>";
        }
    }
    return "N/A";
}

void MainWindow::hintButtonClicked(){
    if (startWord.empty() || endWord.empty()) {
        ui->statusEdit->setText("No active puzzle to give a hint for. Generate a puzzle first.");
        return;
    }

    hintsCount++;

    QString userInputText = ui->userInputPath->toPlainText();
    QStringList userWordsQ = userInputText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    std::string currentHead;
    if (userWordsQ.isEmpty()) {
        currentHead = startWord;
    } else {
        currentHead = userWordsQ.back().toStdString();
    }

    if (!graph.hasNode(currentHead)) {
        ui->statusEdit->setText("Hint: The last word you typed ('" + QString::fromStdString(currentHead) + "') is not in the dictionary. Please correct your path first.");
        ui->hintDisplayLabel->clear();
        return;
    }

    if (currentHead.length() != startWord.length()) {
        ui->statusEdit->setText("Hint: The last word you typed ('" + QString::fromStdString(currentHead) + "') has an incorrect length. Please correct your path.");
        ui->hintDisplayLabel->clear();
        return;
    }

    if (currentHead == endWord) {
        ui->statusEdit->setText("You are already at the target word! No hint needed.");
        ui->hintDisplayLabel->clear();
        return;
    }

    std::vector<std::string> hintPath = graph.shortestPath(currentHead, endWord);

    if (hintPath.empty() || hintPath.size() <= 1) {
        // This means there's no path from currentHead to endWord, or currentHead IS endWord
        ui->statusEdit->setText("Hint: You might be stuck! No path found from '" + QString::fromStdString(currentHead) + "' to '" + QString::fromStdString(endWord) + "'.");
        ui->hintDisplayLabel->clear();
    } else {
        std::string nextOptimalWord = hintPath[1];

        int differingIndex = -1;
        for (size_t i = 0; i < currentHead.length(); ++i) {
            if (currentHead[i] != nextOptimalWord[i]) {
                differingIndex = static_cast<int>(i);
                break;
            }
        }

        if (differingIndex != -1) {
            QString hintCharHtml = buildHintHtml(currentHead, nextOptimalWord); // Call helper for the char's HTML
            ui->hintDisplayLabel->setText("Change letter at position " + QString::number(differingIndex + 1) + " to " + hintCharHtml + ".");
            ui->statusEdit->setText("Hint used. (" + QString::number(hintsCount) + " total hints)");
        } else {
            // This case should ideally not happen if isOneLetterDifferent is true
            ui->statusEdit->setText("Hint: Could not determine the single letter change.");
            ui->hintDisplayLabel->clear();
        }
    }
}

void MainWindow::submitButtonClicked(){
    QString userInput = ui->userInputPath->toPlainText();
    QStringList userWords = userInput.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    if (userWords.isEmpty()){
        ui->statusEdit->setText("Please enter your path.");
        return;
    }

    std::vector<std::string> userPath;
    for (const QString& word : userWords) {
        userPath.push_back(word.toStdString());
    }

    userMoves = userPath;

     bool isValid = validateUserPath(userPath);

    if (!isValid) {
        ui->statusEdit->setText("Invalid path! Check words, connections, start/end.");
        return;
    }

    if (userPath.size() == solutionPath.size()) {
        ui->statusEdit->setText("Correct! You found a shortest path!");
    } else {
        ui->statusEdit->setText("Correct path, but not the shortest! Your length: " + QString::number(userPath.size()) + ", Shortest: " + QString::number(solutionPath.size()) + ".");
    }
}

void MainWindow::gameSaveButtonClicked(){
    QString userInputText = ui->userInputPath->toPlainText();
    if (startWord.empty() or endWord.empty() or userInputText.isEmpty()){
        QMessageBox::warning(this, "Save Error", "No completed game data to save. Play a game first.");
        return;
    }

    QString filename = userName.trimmed().toLower().replace(" ", "_") + ".csv";
    QFile file(QDir::currentPath() + "/" + filename); // Save in the application's current directory

    bool fileExists = file.exists();

    // QIODevice::Text ensures newline characters are handled correctly for text files.
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Save Error", "Could not open file for saving: " + file.errorString());
        return;
    }

    QTextStream out(&file);

    if (!fileExists) {
        out << "UserName,StartWord,TargetWord,DateTime,WordsUsed,HintsUsed,UserMovesCount,OptimalMovesCount\n";
    }

    QStringList userMovesList;
    for (const auto& word: userMoves){
        userMovesList.append(QString::fromStdString(word));
    }

    QString usedMoves = userMovesList.join(" ");

    out << userName
        << "," << QString::fromStdString(startWord)
        << "," << QString::fromStdString(endWord)
        << "," << gameStartTime.toString(Qt::ISODate)
        << "," << usedMoves
        << "," << hintsCount
        << "," << static_cast<int>(userMoves.size()-1)
        << "," << static_cast<int>(solutionPath.size()-1)
        << "\n";

    file.close();

    QMessageBox::information(this, "Game Saved", "Your game results have been saved to " + filename + ".");
}

void MainWindow::analyticsButtonClicked(){
    QString analyticsUserName = ui->analyticsUserNameInput->toPlainText().trimmed();

    if (analyticsUserName.isEmpty()){
        ui->analyticsResultsDisplay->clear();
        QMessageBox::warning(this, "Input Error", "Please enter a user name to load analytics data.");
        return;
    }

    QString fileName = analyticsUserName.toLower().replace(" ", "_") + ".csv";

    QString filePath = QDir::currentPath() + "/" + fileName;

    QFile file (filePath);

    if (!file.exists()){
        ui->analyticsResultsDisplay->clear();
        QMessageBox::information(this, "No Data", "No analytics data file found for user '" + analyticsUserName + "'. Make sure they have played and saved games.");
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->analyticsResultsDisplay->clear();
        QMessageBox::critical(this, "File Error", "Could not open analytics file: " + file.errorString());
        return;
    }

    QTextStream in (&file);
    QString line;

    std::set<std::string> uniqueWordsUsed;
    int totalGamesPlayed = 0;
    int totalHintsUsed = 0;
    long long totalUserMoves = 0;
    long long totalOptimalMoves = 0;
    int gamesCompleted = 0;

    if (!in.atEnd()) {
        line = in.readLine();
    }

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList fields = line.split(',');

        // UserName (Index 0)
        // StartWord (Index 1)
        // TargetWord (Index 2)
        // DateTime (Index 3)
        // UserPath (Index 4)
        // HintsUsed (Index 5)
        // UserMovesCount (Index 6)
        // OptimalMovesCount (Index 7)

        totalGamesPlayed++;

        // Extract UserPath (now at Index 4)
        QString userPathString = fields[4];
        QStringList pathWordsQ = userPathString.split(' ', Qt::SkipEmptyParts);

        for (const QString& qWord : pathWordsQ) {
            uniqueWordsUsed.insert(qWord.toStdString());
        }

        totalHintsUsed += (fields[5]).toInt();

        totalUserMoves += (fields[6]).toLongLong();
        totalOptimalMoves += (fields[7]).toLongLong();

        if (!pathWordsQ.isEmpty() && pathWordsQ.last().toStdString() == (fields[2]).toStdString()) {
            gamesCompleted++;
        }
    }
    file.close();

    QString results;
    results += "--- Analytics for User: " + analyticsUserName + " ---\n";
    results += "Total Games Played: " + QString::number(totalGamesPlayed) + "\n";
    results += "Games Successfully Completed: " + QString::number(gamesCompleted) + "\n";
    results += "Total Unique Words Used: " + QString::number(uniqueWordsUsed.size()) + "\n";
    results += "Total Hints Used: " + QString::number(totalHintsUsed) + "\n";

    if (totalGamesPlayed > 0) {
        results += "Average Moves per Game: " + QString::number(static_cast<double>(totalUserMoves) / totalGamesPlayed, 'f', 2) + "\n";
        results += "Average Optimal Moves per Game: " + QString::number(static_cast<double>(totalOptimalMoves) / totalGamesPlayed, 'f', 2) + "\n";
        if (totalOptimalMoves > 0) {
            results += "Average Performance Ratio (User/Optimal): " + QString::number(static_cast<double>(totalUserMoves) / totalOptimalMoves, 'f', 2) + "\n";
        }
    }

    ui->analyticsResultsDisplay->setText(results);
}
