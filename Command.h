#pragma once
#include "HardwareComponent.h"
#include "Repository.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AddCommand : public Command {
private:
    Repository& repository;
    HardwareComponent component;

public:
    AddCommand(Repository& repo, const HardwareComponent& comp);
    void execute() override;
    void undo() override;
};

class RemoveCommand : public Command {
private:
    Repository& repository;
    HardwareComponent component;

public:
    RemoveCommand(Repository& repo, const HardwareComponent& comp);
    void execute() override;
    void undo() override;
};

class UpdateCommand : public Command {
private:
    Repository& repository;
    HardwareComponent oldComponent;
    HardwareComponent newComponent;

public:
    UpdateCommand(Repository& repo, const HardwareComponent& oldComp, const HardwareComponent& newComp);
    void execute() override;
    void undo() override;
};