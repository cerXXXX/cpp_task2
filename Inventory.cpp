#include "Inventory.h"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const InventoryItem& item) {
  item.describe(out);
  return out;
}

bool operator<(const InventoryItem& lhs, const InventoryItem& rhs) {
  return lhs.inventoryId() < rhs.inventoryId();
}

bool operator==(const InventoryItem& lhs, const InventoryItem& rhs) {
  return lhs.inventoryId() == rhs.inventoryId();
}

bool InventoryItem::isSuitableForNovice(int threshold) const { return false; }