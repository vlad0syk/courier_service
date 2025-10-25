#ifndef DELIVERY_TYPE_UTILS_H
#define DELIVERY_TYPE_UTILS_H

#include <string>
#include "../../include/DeliveryType.h"

std::string deliveryTypeToString(DeliveryType deliveryType);
DeliveryType stringToDeliveryType(std::string deliveryTypeStr);

#endif