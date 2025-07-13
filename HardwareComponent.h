#pragma once
#include <QString>

class HardwareComponent {
private:
    int id;
    QString name;
    QString type;      // CPU, GPU, RAM, etc.
    QString manufacturer;
    QString model;
    double price;
    QString specifications;

public:
    HardwareComponent(int id = 0,
        const QString& name = "",
        const QString& type = "",
        const QString& manufacturer = "",
        const QString& model = "",
        double price = 0.0,
        const QString& specifications = "");

    // Getters
    int getId() const;
    QString getName() const;
    QString getType() const;
    QString getManufacturer() const;
    QString getModel() const;
    double getPrice() const;
    QString getSpecifications() const;

    // Setters
    void setName(const QString& name);
    void setType(const QString& type);
    void setManufacturer(const QString& manufacturer);
    void setModel(const QString& model);
    void setPrice(double price);
    void setSpecifications(const QString& specifications);
};