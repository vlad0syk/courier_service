#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <string>
#include "../../include/DeliveryType.h"

std::string deliveryTypeToString(DeliveryType deliveryType) {
    switch (deliveryType) {
        case DeliveryType::STANDARD:
            return "standard";
        case DeliveryType::EXPRESS:
            return "express";
        case DeliveryType::OVERNIGHT:
            return "overnight";
        default:
            return "unknown";
    }
}

DeliveryType stringToDeliveryType(std::string deliveryTypeStr) {
    std::transform(deliveryTypeStr.begin(), deliveryTypeStr.end(), deliveryTypeStr.begin(), [](unsigned char c){ return std::tolower(c); });
    if (deliveryTypeStr == "standard") {
        return DeliveryType::STANDARD;
    }
    else if (deliveryTypeStr == "express") {
        return DeliveryType::EXPRESS;
    }
    else if (deliveryTypeStr == "overnight") {
        return DeliveryType::OVERNIGHT;
    }
    throw std::invalid_argument("⚠️ Invalid delivery type string: " + deliveryTypeStr);
}
