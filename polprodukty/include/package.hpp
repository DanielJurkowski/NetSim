//
// Created by Daniel on 12/15/2021.
//

#ifndef NETSIM_PACKKAGE_HPP
#define NETSIM_PACKKAGE_HPP

#include "types.hpp"
#include <list>
#include <set>

class Package{
public:
    explicit Package();
    explicit Package(ElementID element_id);

    // konstruktor kopiujący oraz konstruktor typu 'move'
    Package(const Package& package) : element_id_(package.element_id_) {};
    Package(const Package&& package) : element_id_(package.element_id_) {};

    // operator przypisania
    Package& operator=(Package&&);

    ElementID get_id() const { return element_id_; }

    inline static std::set<ElementID> assigned_IDs;
    inline static std::set<ElementID> freed_IDs;

    ~Package();

private:
    ElementID element_id_{};
};

#endif //NETSIM_PACKKAGE_HPP
