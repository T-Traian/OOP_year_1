void MainWindow::handleAdd() {
    if (nameEdit->text().isEmpty() || manufacturerEdit->text().isEmpty() || modelEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please fill in all required fields.");
        return;
    }

    // Always use a new ID for new components
    int newId = nextId++;
    HardwareComponent component(
        newId,
        nameEdit->text(),
        typeCombo->currentText(),
        manufacturerEdit->text(),
        modelEdit->text(),
        priceSpinBox->value(),
        specificationsEdit->toPlainText()
    );

    controller.addComponent(component);
    refreshTable();

    // Clear inputs and reset currentComponentId
    clearInputs();
    currentComponentId = -1;
    updateButtons();
}

void MainWindow::handleUpdate() {
    if (currentComponentId == -1) {
        QMessageBox::warning(this, "Error", "Please select a component to update.");
        return;
    }

    if (nameEdit->text().isEmpty() || manufacturerEdit->text().isEmpty() || modelEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please fill in all required fields.");
        return;
    }

    // Get the current component from the repository
    auto allComponents = controller.getFilteredComponents();
    auto it = std::find_if(allComponents.begin(), allComponents.end(),
        [this](const HardwareComponent& comp) { return comp.getId() == currentComponentId; });

    if (it == allComponents.end()) {
        QMessageBox::warning(this, "Error", QString("Could not find component with ID %1").arg(currentComponentId));
        clearInputs();
        return;
    }

    // Create the old component from the repository data
    HardwareComponent oldComponent = *it;

    // Create the new component with the same ID
    HardwareComponent newComponent(
        currentComponentId,  // Keep the same ID
        nameEdit->text(),
        typeCombo->currentText(),
        manufacturerEdit->text(),
        modelEdit->text(),
        priceSpinBox->value(),
        specificationsEdit->toPlainText()
    );

    controller.updateComponent(oldComponent, newComponent);
    refreshTable();

    // Try to reselect the updated component
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        if (tableWidget->item(row, 0)->text().toInt() == currentComponentId) {
            tableWidget->selectRow(row);
            break;
        }
    }

    updateButtons();
}

void MainWindow::handleRemove() {
    if (currentComponentId == -1) {
        QMessageBox::warning(this, "Error", "Please select a component to remove.");
        return;
    }

    // Get the current component from the repository
    auto allComponents = controller.getFilteredComponents();
    auto it = std::find_if(allComponents.begin(), allComponents.end(),
        [this](const HardwareComponent& comp) { return comp.getId() == currentComponentId; });

    if (it == allComponents.end()) {
        QMessageBox::warning(this, "Error", QString("Could not find component with ID %1").arg(currentComponentId));
        clearInputs();
        return;
    }

    controller.removeComponent(*it);
    clearInputs();
    refreshTable();
    updateButtons();
}

void MainWindow::handleUndo() {
    controller.undo();
    refreshTable();
    clearInputs();
    updateButtons();
}

void MainWindow::handleRedo() {
    controller.redo();
    refreshTable();
    clearInputs();
    updateButtons();
}

void MainWindow::handleSelectionChanged() {
    auto selectedItems = tableWidget->selectedItems();
    if (selectedItems.isEmpty()) {
        clearInputs();
        return;
    }

    int row = selectedItems[0]->row();
    // Store the current state of the component
    int selectedId = tableWidget->item(row, 0)->text().toInt();
    qDebug() << "Selected component with ID:" << selectedId;

    currentComponentId = selectedId;
    nameEdit->setText(tableWidget->item(row, 1)->text());
    typeCombo->setCurrentText(tableWidget->item(row, 2)->text());
    manufacturerEdit->setText(tableWidget->item(row, 3)->text());
    modelEdit->setText(tableWidget->item(row, 4)->text());
    priceSpinBox->setValue(tableWidget->item(row, 5)->text().toDouble());
    specificationsEdit->setText(tableWidget->item(row, 6)->text());

    updateButtons();
} 