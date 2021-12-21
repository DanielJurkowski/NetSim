//
// Created by Daniel on 12/15/2021.
//

#include "package.hpp"


Package::Package() {
    // first ID
    if (assigned_IDs.empty() and freed_IDs.empty()) {
        element_id_ = 1;
    }

    // ID from freed
    else if (not freed_IDs.empty()) {
        element_id_ = *freed_IDs.begin();
        freed_IDs.erase(freed_IDs.begin());
    }

    else {
        for (ElementID element_id: assigned_IDs) {
            if (assigned_IDs.find(element_id) == assigned_IDs.end()) {
                element_id_ = element_id;
                break;
            }

            element_id_ = *(assigned_IDs.rbegin()) + 1;
        }
    }
    assigned_IDs.insert(element_id_);
}

//
Package::Package(ElementID element_id) {
    if (assigned_IDs.find(element_id) != assigned_IDs.end()) {
        throw;
    }

    else {
        element_id = element_id_;
        assigned_IDs.insert(element_id_);
    }


    if (freed_IDs.find(element_id) != freed_IDs.end()) {
        freed_IDs.erase(element_id);
    }
}
//

Package &Package::operator=(Package &&package) {
    element_id_ = package.element_id_;
    return *this;
}

Package::~Package() {
    freed_IDs.insert(element_id_);
    assigned_IDs.erase(element_id_);
}