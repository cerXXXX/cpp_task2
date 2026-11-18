#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "Errors.h"
#include "Fleet.h"
#include "Things.h"
#include "Transport.h"

std::unique_ptr<InventoryItem> readItem(std::istream& input) {
  std::string type;
  std::string id;
  std::string name;

  if (!(input >> type >> id >> name)) {
    throw InvalidArgument("expected type, id and name");
  }

  std::unique_ptr<InventoryItem> item;

  if (type == "scooter" || type == "ebike") {
    double energy;
    int score;

    if (!(input >> energy) || !std::isspace(input.peek()) ||
        !(input >> score)) {
      throw InvalidArgument("expected energy and score");
    }

    if (type == "scooter") {
      item = std::make_unique<ElectricScooter>(id, name, energy, score);
    } else {
      item = std::make_unique<ElectricBicycle>(id, name, energy, score);
    }
  } else if (type == "bike") {
    int score;

    if (!(input >> score)) {
      throw InvalidArgument("expected score");
    }

    item = std::make_unique<Bicycle>(id, name, score);
  } else if (type == "helmet") {
    item = std::make_unique<Helmet>(id, name);
  } else if (type == "dock") {
    double energy;

    if (!(input >> energy)) {
      throw InvalidArgument("expected energy");
    }

    item = std::make_unique<DockStation>(id, name, energy);
  } else if (type == "cargo") {
    double energy;
    int score;
    double capacity;

    if (!(input >> energy) || !std::isspace(input.peek()) ||
        !(input >> score) || !std::isspace(input.peek()) ||
        !(input >> capacity)) {
      throw InvalidArgument("expected energy, score and capacity");
    }

    item = std::make_unique<ElectricCargoBicycle>(id, name, energy, score,
                                                  capacity);
  } else {
    throw InvalidArgument("unknown item type");
  }

  std::string extra;
  if (input >> extra) {
    throw InvalidArgument("unexpected argument");
  }

  return item;
}
int main() {
  Fleet fleet;
  std::string line;

  while (std::getline(std::cin, line)) {
    try {
      std::istringstream input(line);
      std::string command;

      if (!(input >> command)) {
        continue;
      }

      if (command == "focus" || command == "remove") {
        std::string id;

        if (!(input >> id)) {
          throw InvalidArgument("inventory id expected");
        }

        std::string extra;
        if (input >> extra) {
          throw InvalidArgument("unexpected argument");
        }

        if (command == "focus") {
          fleet.focus(id);
        } else {
          fleet.remove(id);
        }

        continue;
      }

      if (command == "add") {
        auto item = readItem(input);
        fleet.add(std::move(item));
        continue;
      }

      std::string extra;
      if (input >> extra) {
        throw InvalidArgument("unexpected argument");
      }

      if (command == "quit") break;
      if (command == "list") {
        fleet.list(std::cout);
      } else if (command == "novice") {
        fleet.novice(std::cout);
      } else if (command == "energy") {
        std::cout << std::fixed << std::setprecision(1) << fleet.totalEnergy()
                  << '\n';
      } else if (command == "show_focus") {
        fleet.showFocus(std::cout);
      } else if (command == "max_energy") {
        fleet.maxEnergy(std::cout);
      } else if (command == "report") {
        std::cout << "count: " << fleet.size() << '\n'
                  << "energy: " << std::fixed << std::setprecision(1)
                  << fleet.totalEnergy() << '\n';
      } else {
        throw InvalidArgument("unknown command");
      }
    } catch (const FleetError& error) {
      std::cout << "error: " << error.what() << '\n';
    }
  }

  return 0;
}
