#pragma once
#include "Repository.h"
#include "Command.h"
#include "Filter.h"
#include <memory>
#include <stack>

class Controller {
private:
    Repository& repository;
    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;
    std::shared_ptr<IFilter> currentFilter;

public:
    explicit Controller(Repository& repo);

    void addComponent(const HardwareComponent& component);
    void removeComponent(const HardwareComponent& component);
    void updateComponent(const HardwareComponent& oldComponent, const HardwareComponent& newComponent);

    bool canUndo() const;
    bool canRedo() const;
    void undo();
    void redo();

    // Filter methods
    void setFilter(std::shared_ptr<IFilter> filter);
    void clearFilter();
    std::vector<HardwareComponent> getAllComponents() const;
    std::vector<HardwareComponent> getFilteredComponents() const;

    // Helper methods for creating common filters
    static std::shared_ptr<IFilter> createTypeFilter(const QString& type);
    static std::shared_ptr<IFilter> createManufacturerFilter(const QString& manufacturer);
    static std::shared_ptr<IFilter> createPriceRangeFilter(double minPrice, double maxPrice);
    static std::shared_ptr<AndFilter> createAndFilter();
    static std::shared_ptr<OrFilter> createOrFilter();
};