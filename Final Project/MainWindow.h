#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include "Controller.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    static int nextId;  
    int currentComponentId;  

    Controller& controller;
    QTableWidget* tableWidget;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateButton;
    QPushButton* undoButton;
    QPushButton* redoButton;

    QLineEdit* nameEdit;
    QComboBox* typeCombo;
    QLineEdit* manufacturerEdit;
    QLineEdit* modelEdit;
    QDoubleSpinBox* priceSpinBox;
    QTextEdit* specificationsEdit;

    QGroupBox* filterGroup;
    QComboBox* filterTypeCombo;
    QLineEdit* filterManufacturerEdit;
    QDoubleSpinBox* filterMinPriceSpinBox;
    QDoubleSpinBox* filterMaxPriceSpinBox;
    QRadioButton* useOrFilterRadio;
    QRadioButton* useAndFilterRadio;
    QButtonGroup* filterButtonGroup;
    QPushButton* applyFilterButton;
    QPushButton* clearFilterButton;

    void setupUI();
    void setupFilterUI();
    void refreshTable();
    void updateButtons();
    HardwareComponent getComponentFromInputs() const;
    void clearInputs();
    void applyFilters();
    void initializeNextId();

private slots:
    void handleAdd();
    void handleRemove();
    void handleUpdate();
    void handleUndo();
    void handleRedo();
    void handleSelectionChanged();
    void handleFilterApply();
    void handleFilterClear();

public:
    explicit MainWindow(Controller& controller, QWidget* parent = nullptr);
};