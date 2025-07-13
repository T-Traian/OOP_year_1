#include "HardwareComponent.h"

HardwareComponent::HardwareComponent(int id,
    const QString& name,
    const QString& type,
    const QString& manufacturer,
    const QString& model,
    double price,
    const QString& specifications)
    : id(id)
    , name(name)
    , type(type)
    , manufacturer(manufacturer)
    , model(model)
    , price(price)
    , specifications(specifications){}

int HardwareComponent::getId() const {
    return id;
}

QString HardwareComponent::getName() const {
    return name;
}

QString HardwareComponent::getType() const {
    return type;
}

QString HardwareComponent::getManufacturer() const {
    return manufacturer;
}

QString HardwareComponent::getModel() const {
    return model;
}

double HardwareComponent::getPrice() const {
    return price;
}

QString HardwareComponent::getSpecifications() const {
    return specifications;
}


void HardwareComponent::setName(const QString& name) {
    this->name = name;
}

void HardwareComponent::setType(const QString& type) {
    this->type = type;
}

void HardwareComponent::setManufacturer(const QString& manufacturer) {
    this->manufacturer = manufacturer;
}

void HardwareComponent::setModel(const QString& model) {
    this->model = model;
}

void HardwareComponent::setPrice(double price) {
    this->price = price;
}

void HardwareComponent::setSpecifications(const QString& specifications) {
    this->specifications = specifications;
}