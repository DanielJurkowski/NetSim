//
// Created by Daniel on 1/17/2022.
//

#ifndef NETSIM_REPORTS_HPP
#define NETSIM_REPORTS_HPP

#include "factory.hpp"
#include <iostream>
#include <ostream>

class IntervalReportNotifier{
public:
    IntervalReportNotifier(TimeOffset t_offset){t_offset_ = t_offset;}
    bool should_generate_report(Time time);

private:
    TimeOffset t_offset_;
};

class SpecificTurnsReportNotifier{
public:
    SpecificTurnsReportNotifier(std::set<Time> turns){turns_ = turns;}
    bool should_generate_report(Time time);

private:
    std::set<Time> turns_;
};

void generate_structure_report(const Factory& f, std::ostream& os);
void generate_simulation_turn_report(const Factory& f, std::ostream& os, Time time);

#endif //NETSIM_REPORTS_HPP
