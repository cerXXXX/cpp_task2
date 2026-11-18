#include "Things.h"

#include <cmath>
#include <iostream>

#include "Errors.h"

Helmet::Helmet(const std::string& id, const std::string& name)
    : id_(id), name_(name) {
  if (id_.empty()) {
    throw InvalidArgument("inventory id must not be empty");
  }

  if (name_.empty()) {
    throw InvalidArgument("name must not be empty");
  }
}

const std::string& Helmet::name() const { return name_; }

const std::string& Helmet::inventoryId() const { return id_; }

void Helmet::describe(std::ostream& out) const {
  out << inventoryId() << " " << name();
}

DockStation::DockStation(const std::string& id, const std::string& name,
                         double energy)
    : id_(id), name_(name), energy_(energy) {
  if (id_.empty()) {
    throw InvalidArgument("inventory id must not be empty");
  }

  if (name_.empty()) {
    throw InvalidArgument("name must not be empty");
  }

  if (!std::isfinite(energy_) || energy_ < 0) {
    throw InvalidArgument("energy must be finite and non-negative");
  }
}

const std::string& DockStation::name() const { return name_; }

const std::string& DockStation::inventoryId() const { return id_; }

double DockStation::dailyEnergy() const { return energy_; }

void DockStation::describe(std::ostream& out) const {
  out << inventoryId() << " " << name();
}