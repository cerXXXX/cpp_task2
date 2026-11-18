#ifndef FLEET_H
#define FLEET_H

#include <cstddef>
#include <iosfwd>
#include <memory>
#include <string>

#include "Inventory.h"
#include "Registry.h"
#include "ServiceCenter.h"

class Fleet {
 public:
  void add(std::unique_ptr<InventoryItem> item);
  void remove(const std::string& id);

  std::size_t size() const;
  double totalEnergy() const;

  void list(std::ostream& out) const;
  void novice(std::ostream& out, int threshold = 6) const;

  void focus(const std::string& id);
  void showFocus(std::ostream& out) const;

  void maxEnergy(std::ostream& out) const;

 private:
  Registry<std::shared_ptr<InventoryItem>> items_;
  std::weak_ptr<InventoryItem> focus_;
  ServiceCenter serviceCenter_;
};

#endif
