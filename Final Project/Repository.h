#pragma once
#include <vector>
#include <QString>
#include "HardwareComponent.h"

class Repository {
public:
    virtual ~Repository() = default;
    
    virtual void add(const HardwareComponent& component) = 0;
    virtual void remove(const HardwareComponent& component) = 0;
    virtual void update(const HardwareComponent& oldComponent, const HardwareComponent& newComponent) = 0;
    virtual std::vector<HardwareComponent> getAll() const = 0;
    virtual void save() = 0;
    virtual void load() = 0;
};

class JSONRepository : public Repository {
private:
    QString filename;
    std::vector<HardwareComponent> components;
    void loadFromCSV(const QString& csvFilename);

public:
    explicit JSONRepository(const QString& filename);
    void add(const HardwareComponent& component) override;
    void remove(const HardwareComponent& component) override;
    void update(const HardwareComponent& oldComponent, const HardwareComponent& newComponent) override;
    std::vector<HardwareComponent> getAll() const override;
    void save() override;
    void load() override;
}; 