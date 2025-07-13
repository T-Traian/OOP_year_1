#include "Controller.h"

Controller::Controller(Repository& repo) : repository(repo), currentFilter(nullptr) {
}

void Controller::addComponent(const HardwareComponent& component) {
    auto command = std::make_unique<AddCommand>(repository, component);
    command->execute();
    undoStack.push(std::move(command));
    while (!redoStack.empty()) redoStack.pop();
}

void Controller::removeComponent(const HardwareComponent& component) {
    auto command = std::make_unique<RemoveCommand>(repository, component);
    command->execute();
    undoStack.push(std::move(command));
    while (!redoStack.empty()) redoStack.pop();
}

void Controller::updateComponent(const HardwareComponent& oldComponent, const HardwareComponent& newComponent) {
    auto command = std::make_unique<UpdateCommand>(repository, oldComponent, newComponent);
    command->execute();
    undoStack.push(std::move(command));
    while (!redoStack.empty()) redoStack.pop();
}

bool Controller::canUndo() const {
    return !undoStack.empty();
}

bool Controller::canRedo() const {
    return !redoStack.empty();
}

void Controller::undo() {
    if (!undoStack.empty()) {
        auto command = std::move(undoStack.top());
        undoStack.pop();
        command->undo();
        redoStack.push(std::move(command));
    }
}

void Controller::redo() {
    if (!redoStack.empty()) {
        auto command = std::move(redoStack.top());
        redoStack.pop();
        command->execute();
        undoStack.push(std::move(command));
    }
}

void Controller::setFilter(std::shared_ptr<IFilter> filter) {
    currentFilter = filter;
}

void Controller::clearFilter() {
    currentFilter = nullptr;
}

std::vector<HardwareComponent> Controller::getAllComponents() const {
    return repository.getAll();
}

std::vector<HardwareComponent> Controller::getFilteredComponents() const {
    if (!currentFilter) {
        return getAllComponents();
    }

    std::vector<HardwareComponent> allComponents = repository.getAll();
    std::vector<HardwareComponent> filteredComponents;

	for (auto& component : allComponents) {
		if (currentFilter->matches(component)) {
			filteredComponents.push_back(component);
		}
	}

    return filteredComponents;
}

// Static helper methods for creating filters
std::shared_ptr<IFilter> Controller::createTypeFilter(const QString& type) {
    return std::make_shared<TypeFilter>(type);
}

std::shared_ptr<IFilter> Controller::createManufacturerFilter(const QString& manufacturer) {
    return std::make_shared<ManufacturerFilter>(manufacturer);
}

std::shared_ptr<IFilter> Controller::createPriceRangeFilter(double minPrice, double maxPrice) {
    return std::make_shared<PriceRangeFilter>(minPrice, maxPrice);
}

std::shared_ptr<AndFilter> Controller::createAndFilter() {
    return std::make_shared<AndFilter>();
}

std::shared_ptr<OrFilter> Controller::createOrFilter() {
    return std::make_shared<OrFilter>();
}