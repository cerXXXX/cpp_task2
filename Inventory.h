#ifndef INVENTORY_H
#define INVENTORY_H

#include <iosfwd>
#include <string>

class InventoryItem {
 public:
  virtual ~InventoryItem() = default;

  virtual const std::string& inventoryId() const = 0;
  virtual const std::string& name() const = 0;
  virtual void describe(std::ostream& out) const = 0;
  virtual bool isSuitableForNovice(int threshold) const;
};

class EnergyConsumer {
 public:
  virtual ~EnergyConsumer() = default;

  virtual double dailyEnergy() const = 0;
};

std::ostream& operator<<(std::ostream& out, const InventoryItem& item);
bool operator<(const InventoryItem& lhs, const InventoryItem& rhs);
bool operator==(const InventoryItem& lhs, const InventoryItem& rhs);

#endif
