#include "ServiceCenter.h"

#include <algorithm>
#include <string>

#include "Errors.h"

void ServiceCenter::inspect(const Transport& transport) const {
  std::string lowered = transport.name();

  std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  if (lowered.find("broken") != std::string::npos) {
    throw InspectionRejected();
  }
}