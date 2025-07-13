#include "Filter.h"

TypeFilter::TypeFilter(const QString& type) : type(type) {}

bool TypeFilter::matches(const HardwareComponent& component) const {
    return component.getType() == type;
}

ManufacturerFilter::ManufacturerFilter(const QString& manufacturer) : manufacturer(manufacturer) {}

bool ManufacturerFilter::matches(const HardwareComponent& component) const {
    return component.getManufacturer() == manufacturer;
}

PriceRangeFilter::PriceRangeFilter(double min, double max) : minPrice(min), maxPrice(max) {}

bool PriceRangeFilter::matches(const HardwareComponent& component) const {
    double price = component.getPrice();
    return price >= minPrice && price <= maxPrice;
}

void AndFilter::addFilter(std::shared_ptr<IFilter> filter) {
    filters.push_back(filter);
}

bool AndFilter::matches(const HardwareComponent& component) const {
    for (const auto& filter : filters) {
        if (!filter->matches(component)) return false;
    }
    return true;
}

void OrFilter::addFilter(std::shared_ptr<IFilter> filter) {
    filters.push_back(filter);
}

bool OrFilter::matches(const HardwareComponent& component) const {
    if (filters.empty()) return true;
    for (const auto& filter : filters) {
        if (filter->matches(component)) return true;
    }
    return false;
}