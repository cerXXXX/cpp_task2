#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <string>

class FleetError : public std::runtime_error {
 public:
  explicit FleetError(const std::string& message)
      : std::runtime_error(message) {}
};

class InspectionRejected : public FleetError {
 public:
  InspectionRejected() : FleetError("inspection rejected") {}
};

class InvalidArgument : public FleetError {
 public:
  explicit InvalidArgument(const std::string& message) : FleetError(message) {}
};

#endif