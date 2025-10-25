#ifndef PARCEL_H
#define PARCEL_H

#include <string> 
#include "../../include/DeliveryType.h"

struct Parcel {
    std::string id;
    std::string sender;
    std::string recipient;
    std::string address;
    double weight;
    DeliveryType deliveryType;
};

void createParcel(const std::string& senderLogin);

#endif