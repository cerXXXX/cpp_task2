#include "Fleet.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

#include "Errors.h"
#include "Transport.h"

void Fleet::add(std::unique_ptr<InventoryItem> item) {
  if (!item) {
    throw InvalidArgument("item must not be null");
  }

  for (const auto& existing : items_) {
    if (*existing == *item) {
      throw InvalidArgument("duplicate inventory id");
    }
  }

  if (const auto* transport = dynamic_cast<const Transport*>(item.get())) {
    serviceCenter_.inspect(*transport);
  }

  std::shared_ptr<InventoryItem> accepted(std::move(item));
  items_.add(std::move(accepted));
}

void Fleet::remove(const std::string& id) {
  bool removed = items_.removeFirst(
      [&id](const auto& item) { return item->inventoryId() == id; });

  if (!removed) {
    throw InvalidArgument("inventory id not found");
  }
}

std::size_t Fleet::size() const { return items_.size(); }

double Fleet::totalEnergy() const {
  double total = 0.0;
  for (const auto& item : items_) {
    if (const auto* consumer =
            dynamic_cast<const EnergyConsumer*>(item.get())) {
      total += consumer->dailyEnergy();
    }
  }
  return total;
}

void Fleet::novice(std::ostream& out, int threshold) const {
  for (const auto& item : items_) {
    if (item->isSuitableForNovice(threshold)) {
      out << *item << '\n';
    }
  }
}

void Fleet::list(std::ostream& out) const {
  std::vector<std::shared_ptr<InventoryItem>> sorted(items_.begin(),
                                                     items_.end());

  std::sort(sorted.begin(), sorted.end(),
            [](const auto& lhs, const auto& rhs) { return *lhs < *rhs; });

  for (const auto& item : sorted) {
    out << *item << '\n';
  }
}

void Fleet::focus(const std::string& id) {
  for (const auto& item : items_) {
    if (item->inventoryId() == id) {
      focus_ = item;
      return;
    }
  }

  throw InvalidArgument("inventory id not found");
}

void Fleet::showFocus(std::ostream& out) const {
  if (auto item = focus_.lock()) {
    out << *item << '\n';
  } else {
    out << "expired\n";
  }
}
void Fleet::maxEnergy(std::ostream& out) const {
  const InventoryItem* best = nullptr;
  double maxEnergy = 0.0;

  for (const auto& item : items_) {
    if (const auto* consumer =
            dynamic_cast<const EnergyConsumer*>(item.get())) {
      double energy = consumer->dailyEnergy();

      if (!best || energy > maxEnergy) {
        best = item.get();
        maxEnergy = energy;
      }
    }
  }

  if (best) {
    out << *best << ' ' << std::fixed << std::setprecision(1) << maxEnergy
        << '\n';
  } else {
    out << "empty\n";
  }
}