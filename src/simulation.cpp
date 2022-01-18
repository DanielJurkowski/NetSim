//
// Created by Daniel on 1/17/2022.
//

#include "simulation.hpp"

void simulate(Factory &f, TimeOffset d, std::function<void (Factory&, Time)> rf) {
    if(!f.is_consistent()){
        throw std::logic_error("Error");
    }

    TimeOffset t = 1;

    while(d >= t){
        f.do_deliveries(t); //delivery
        f.do_package_passing(); //passing
        f.do_work(t); //working
        rf(f, t); //reports
        t++;
    }
}
