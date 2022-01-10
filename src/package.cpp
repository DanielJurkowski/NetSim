//
// Created by Daniel on 12/15/2021.
//

#include "package.hpp"

Package::Package() : element_id_() {
    if (Package::assigned_IDs.empty() and Package::freed_IDs.empty()) {
        Package::element_id_ = 1;
    }


    else if (not Package::freed_IDs.empty()) {
        Package::element_id_ = *Package::freed_IDs.begin();
        Package::freed_IDs.erase(Package::freed_IDs.begin());
    }

    else {
        ElementID highest_id = std::max(*Package::assigned_IDs.begin(), *Package::assigned_IDs.end());

        Package::element_id_ = highest_id + 1;
    }

    Package::assigned_IDs.insert(Package::element_id_);
}

Package::Package(ElementID element_id) {
    if (Package::assigned_IDs.find(element_id) != Package::assigned_IDs.end()) {
        throw;
    }

    else {
        element_id_ = element_id;
        Package::assigned_IDs.insert(Package::element_id_);
    }

    if (Package::freed_IDs.find(element_id) != Package::freed_IDs.end()) {
        element_id_ = element_id;
        Package::freed_IDs.erase(element_id);
        Package::assigned_IDs.insert(Package::element_id_);
    }
}


Package::~Package() {
    Package::freed_IDs.insert(Package::element_id_);
    Package::assigned_IDs.erase(Package::element_id_);
}
