#ifndef SERVICE_CENTER_H
#define SERVICE_CENTER_H

#include "Transport.h"

class ServiceCenter {
 public:
  void inspect(const Transport& transport) const;
};

#endif