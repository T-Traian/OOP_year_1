#pragma once
#include "HardwareComponent.h"
#include <memory>
#include <vector>
#include <functional>

class IFilter {
public:
    virtual ~IFilter() = default;
    virtual bool matches(const HardwareComponent& component) const = 0;
};

class TypeFilter : public IFilter {
private:
    QString type;
public:
    explicit TypeFilter(const QString& type);
    bool matches(const HardwareComponent& component) const override;
};

class ManufacturerFilter : public IFilter {
private:
    QString manufacturer;
public:
    explicit ManufacturerFilter(const QString& manufacturer);
    bool matches(const HardwareComponent& component) const override;
};

class PriceRangeFilter : public IFilter {
private:
    double minPrice;
    double maxPrice;
public:
    PriceRangeFilter(double min, double max);
    bool matches(const HardwareComponent& component) const override;
};

// Composite filters for AND/OR operations
class AndFilter : public IFilter {
private:
    std::vector<std::shared_ptr<IFilter>> filters;
public:
    void addFilter(std::shared_ptr<IFilter> filter);
    bool matches(const HardwareComponent& component) const override;
};

class OrFilter : public IFilter {
private:
    std::vector<std::shared_ptr<IFilter>> filters;
public:
    void addFilter(std::shared_ptr<IFilter> filter);
    bool matches(const HardwareComponent& component) const override;
};