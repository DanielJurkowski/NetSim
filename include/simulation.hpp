//
// Created by Daniel on 1/17/2022.
//

#ifndef NETSIM_SIMULATION_HPP
#define NETSIM_SIMULATION_HPP

#include "factory.hpp"
#include "types.hpp"

void simulate(Factory &f, TimeOffset d, std::function<void(Factory &, Time)> rf);

#endif //NETSIM_SIMULATION_HPP
