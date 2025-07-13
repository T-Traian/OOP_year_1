#include "Command.h"

AddCommand::AddCommand(Repository& repo, const HardwareComponent& comp)
    : repository(repo), component(comp) {
}

void AddCommand::execute() {
    repository.add(component);
}

void AddCommand::undo() {
    repository.remove(component);
}

RemoveCommand::RemoveCommand(Repository& repo, const HardwareComponent& comp)
    : repository(repo), component(comp) {
}

void RemoveCommand::execute() {
    repository.remove(component);
}

void RemoveCommand::undo() {
    repository.add(component);
}

UpdateCommand::UpdateCommand(Repository& repo, const HardwareComponent& oldComp, const HardwareComponent& newComp)
    : repository(repo), oldComponent(oldComp), newComponent(newComp) {
}

void UpdateCommand::execute() {
    repository.update(oldComponent, newComponent);
}

void UpdateCommand::undo() {
    repository.update(newComponent, oldComponent);
}