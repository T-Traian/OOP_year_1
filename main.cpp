#include <QApplication>
#include <QMessageBox>
#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QGroupBox>
#include "MainWindow.h"
#include "Repository.h"
#include "Controller.h"
#include <memory>

std::unique_ptr<Repository> createRepository() {
    QDialog dialog;
    dialog.setWindowTitle("Storage Options");
    dialog.setMinimumWidth(400);

    auto* mainLayout = new QVBoxLayout(&dialog);

    // Create new file group
    auto* newFileGroup = new QGroupBox("Create New File", &dialog);
    auto* newFileLayout = new QVBoxLayout(newFileGroup);

    auto* label1 = new QLabel("Create a new storage file:", newFileGroup);
    auto* csvNewButton = new QPushButton("New CSV File...", newFileGroup);
    auto* jsonNewButton = new QPushButton("New JSON File...", newFileGroup);

    newFileLayout->addWidget(label1);
    newFileLayout->addWidget(csvNewButton);
    newFileLayout->addWidget(jsonNewButton);

    // Load existing file group
    auto* loadFileGroup = new QGroupBox("Load Existing File", &dialog);
    auto* loadFileLayout = new QVBoxLayout(loadFileGroup);

    auto* label2 = new QLabel("Load an existing storage file:", loadFileGroup);
    auto* csvLoadButton = new QPushButton("Load CSV File...", loadFileGroup);
    auto* jsonLoadButton = new QPushButton("Load JSON File...", loadFileGroup);

    loadFileLayout->addWidget(label2);
    loadFileLayout->addWidget(csvLoadButton);
    loadFileLayout->addWidget(jsonLoadButton);

    mainLayout->addWidget(newFileGroup);
    mainLayout->addWidget(loadFileGroup);

    std::unique_ptr<Repository> repository;

    // New file connections
    QObject::connect(csvNewButton, &QPushButton::clicked, [&]() {
        QString filename = QFileDialog::getSaveFileName(&dialog,
            "Create New CSV File",
            "hardware_inventory.csv",
            "CSV Files (*.csv)");
        if (!filename.isEmpty()) {
            repository = std::make_unique<JSONRepository>(filename);
            dialog.accept();
        }
    });

    QObject::connect(jsonNewButton, &QPushButton::clicked, [&]() {
        QString filename = QFileDialog::getSaveFileName(&dialog,
            "Create New JSON File",
            "hardware_inventory.json",
            "JSON Files (*.json)");
        if (!filename.isEmpty()) {
            repository = std::make_unique<JSONRepository>(filename);
            dialog.accept();
        }
    });

    // Load file connections
    QObject::connect(csvLoadButton, &QPushButton::clicked, [&]() {
        QString filename = QFileDialog::getOpenFileName(&dialog,
            "Open CSV File",
            "",
            "CSV Files (*.csv)");
        if (!filename.isEmpty()) {
            repository = std::make_unique<JSONRepository>(filename);
            dialog.accept();
        }
    });

    QObject::connect(jsonLoadButton, &QPushButton::clicked, [&]() {
        QString filename = QFileDialog::getOpenFileName(&dialog,
            "Open JSON File",
            "",
            "JSON Files (*.json)");
        if (!filename.isEmpty()) {
            repository = std::make_unique<JSONRepository>(filename);
            dialog.accept();
        }
    });

    dialog.exec();

    if (!repository) {
        // If dialog is closed without selection, ask user for a default JSON file name
        QString filename = QFileDialog::getSaveFileName(nullptr,
            "Create Default JSON File",
            "hardware_inventory.json",
            "JSON Files (*.json)");
        if (!filename.isEmpty()) {
            repository = std::make_unique<JSONRepository>(filename);
        }
        else {
            // If user cancels file selection, use a default name
            repository = std::make_unique<JSONRepository>("hardware_inventory.json");
        }
    }

    return repository;
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Let user choose repository type and file
    std::unique_ptr<Repository> repository = createRepository();

    // Create controller with repository
    Controller controller(*repository);

    // Create main window with controller
    MainWindow window(controller);
    window.show();

    return app.exec();
} 