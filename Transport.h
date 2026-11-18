#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>

#include "Inventory.h"

class Transport : public InventoryItem {
 public:
  Transport(const std::string& id, const std::string& name, int score);
  ~Transport() override = default;

  const std::string& inventoryId() const override;
  const std::string& name() const override;
  int noviceScore() const;
  bool isSuitableForNovice(int threshold) const override;

 private:
  std::string id_;
  std::string name_;
  int score_;
};

class ElectricScooter : public Transport, public EnergyConsumer {
 public:
  ElectricScooter(const std::string& id, const std::string& name, double energy,
                  int score);
  double dailyEnergy() const override;
  void describe(std::ostream& out) const override;

 private:
  double energy_;
};

class Bicycle : public Transport {
 public:
  Bicycle(const std::string& id, const std::string& name, int score);

  void describe(std::ostream& out) const override;
};

class ElectricBicycle : public Bicycle, public EnergyConsumer {
 public:
  ElectricBicycle(const std::string& id, const std::string& name, double energy,
                  int score);
  double dailyEnergy() const override;

 private:
  double energy_;
};

class ElectricCargoBicycle : public ElectricBicycle {
 public:
  ElectricCargoBicycle(const std::string& id, const std::string& name,
                       double energy, int score, double capacity);

  double cargoCapacity() const;

 private:
  double capacity_;
};
#endif
