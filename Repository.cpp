#include "Repository.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <algorithm>

// JSON Repository Implementation
JSONRepository::JSONRepository(const QString& filename) : filename(filename) {
    if (filename.endsWith(".csv", Qt::CaseInsensitive)) {
        loadFromCSV(filename);
    } else {
        load();
    }
}

void JSONRepository::loadFromCSV(const QString& csvFilename) {
    components.clear();
    QFile file(csvFilename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // Skip header
        if (!in.atEnd()) {
            in.readLine();
        }

        // Read data
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");

            if (fields.size() >= 7) {
                components.emplace_back(
                    fields[0].toInt(),
                    fields[1],
                    fields[2],
                    fields[3],
                    fields[4],
                    fields[5].toDouble(),
                    fields[6]
                );
            }
        }
        file.close();
    }
}

void JSONRepository::add(const HardwareComponent& component) {
    components.push_back(component);
    save();
}

void JSONRepository::remove(const HardwareComponent& component) {
    auto it = std::find_if(components.begin(), components.end(),
        [&component](const HardwareComponent& comp) { return comp.getId() == component.getId(); });

    if (it != components.end()) {
        components.erase(it);
        save();
    }
}

void JSONRepository::update(const HardwareComponent& oldComponent, const HardwareComponent& newComponent) {
    // First verify that the old component exists and matches
    auto it = std::find_if(components.begin(), components.end(),
        [&oldComponent](const HardwareComponent& comp) { 
            return comp.getId() == oldComponent.getId() &&
                   comp.getName() == oldComponent.getName() &&
                   comp.getType() == oldComponent.getType() &&
                   comp.getManufacturer() == oldComponent.getManufacturer() &&
                   comp.getModel() == oldComponent.getModel() &&
                   comp.getPrice() == oldComponent.getPrice() &&
                   comp.getSpecifications() == oldComponent.getSpecifications();
        });

    if (it != components.end()) {
        *it = newComponent;
        save();
    }
}

std::vector<HardwareComponent> JSONRepository::getAll() const {
    return components;
}

void JSONRepository::save() {
    QString saveFilename = filename;
    if (saveFilename.endsWith(".csv", Qt::CaseInsensitive)) {
        // Save as CSV
        QFile file(saveFilename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            
            // Write header
            out << "ID,Name,Type,Manufacturer,Model,Price,Specifications\n";
            
            // Write data
            for (const auto& component : components) {
                out << component.getId() << ","
                    << component.getName() << ","
                    << component.getType() << ","
                    << component.getManufacturer() << ","
                    << component.getModel() << ","
                    << component.getPrice() << ","
                    << component.getSpecifications() << "\n";
            }
            file.close();
        }
    } else {
        // Save as JSON
        QFile file(saveFilename);
        if (file.open(QIODevice::WriteOnly)) {
            QJsonArray componentsArray;

            for (const auto& component : components) {
                QJsonObject componentObj;
                componentObj["id"] = component.getId();
                componentObj["name"] = component.getName();
                componentObj["type"] = component.getType();
                componentObj["manufacturer"] = component.getManufacturer();
                componentObj["model"] = component.getModel();
                componentObj["price"] = component.getPrice();
                componentObj["specifications"] = component.getSpecifications();

                componentsArray.append(componentObj);
            }

            QJsonDocument doc(componentsArray);
            file.write(doc.toJson());
            file.close();
        }
    }
}

void JSONRepository::load() {
    components.clear();
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        QJsonArray componentsArray = doc.array();

        for (const QJsonValue& value : componentsArray) {
            QJsonObject obj = value.toObject();
            components.emplace_back(
                obj["id"].toInt(),
                obj["name"].toString(),
                obj["type"].toString(),
                obj["manufacturer"].toString(),
                obj["model"].toString(),
                obj["price"].toDouble(),
                obj["specifications"].toString()
            );
        }
        file.close();
    }
} 