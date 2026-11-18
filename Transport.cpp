#include "Transport.h"

#include <cmath>
#include <iostream>

#include "Errors.h"

Transport::Transport(const std::string& id, const std::string& name, int score)
    : id_(id), name_(name), score_(score) {
  if (id_.empty()) {
    throw InvalidArgument("inventory id must not be empty");
  }

  if (name_.empty()) {
    throw InvalidArgument("name must not be empty");
  }

  if (score_ < 1 || score_ > 10) {
    throw InvalidArgument("score must be between 1 and 10");
  }
}

const std::string& Transport::inventoryId() const { return id_; }

const std::string& Transport::name() const { return name_; }

int Transport::noviceScore() const { return score_; }

bool Transport::isSuitableForNovice(int threshold) const {
  return score_ >= threshold;
}

ElectricScooter::ElectricScooter(const std::string& id, const std::string& name,
                                 double energy, int score)
    : Transport(id, name, score), energy_(energy) {
  if (!std::isfinite(energy_) || energy_ < 0) {
    throw InvalidArgument("energy must be finite and non-negative");
  }
}

double ElectricScooter::dailyEnergy() const { return energy_; }

void ElectricScooter::describe(std::ostream& out) const {
  out << inventoryId() << " " << name();
}

Bicycle::Bicycle(const std::string& id, const std::string& name, int score)
    : Transport(id, name, score) {}

void Bicycle::describe(std::ostream& out) const {
  out << inventoryId() << " " << name();
}

ElectricBicycle::ElectricBicycle(const std::string& id, const std::string& name,
                                 double energy, int score)
    : Bicycle(id, name, score), energy_(energy) {
  if (!std::isfinite(energy_) || energy_ < 0) {
    throw InvalidArgument("energy must be finite and non-negative");
  }
}

double ElectricBicycle::dailyEnergy() const { return energy_; }

ElectricCargoBicycle::ElectricCargoBicycle(const std::string& id,
                                           const std::string& name,
                                           double energy, int score,
                                           double capacity)
    : ElectricBicycle(id, name, energy, score), capacity_(capacity) {
  if (!std::isfinite(capacity_) || capacity_ <= 0) {
    throw InvalidArgument("capacity must be finite and positive");
  }
}

double ElectricCargoBicycle::cargoCapacity() const { return capacity_; }
