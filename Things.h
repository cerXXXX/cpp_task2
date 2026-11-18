#ifndef THINGS_H
#define THINGS_H

#include "Inventory.h"

class Helmet : public InventoryItem {
 public:
  Helmet(const std::string& id, const std::string& name);

  const std::string& name() const override;
  void describe(std::ostream& out) const override;
  const std::string& inventoryId() const override;

 private:
  std::string id_;
  std::string name_;
};

class DockStation : public InventoryItem, public EnergyConsumer {
 public:
  DockStation(const std::string& id, const std::string& name, double energy);

  const std::string& name() const override;
  void describe(std::ostream& out) const override;
  const std::string& inventoryId() const override;
  double dailyEnergy() const override;

 private:
  std::string id_;
  std::string name_;
  double energy_;
};

#endif
