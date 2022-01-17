//
// Created by Daniel on 12/17/2021.
//

#ifndef NETSIM_FACTORY_HPP
#define NETSIM_FACTORY_HPP

#include <list>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <vector>
#include <ostream>
#include <string>

#include "nodes.hpp"
#include "types.hpp"
#include "package.hpp"


// Factory
template <class Node>

class NodeCollection{
public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    void add(Node&& node) { nodes_.push_back(std::move(node)); };
    void remove_by_id(ElementID id) {
        auto ptr = find_by_id(id);
        if (ptr != nodes_.end()) nodes_.erase(ptr);
    };

    NodeCollection<Node>::iterator find_by_id(ElementID id) { return std::find_if(nodes_.begin(), nodes_.end(), [=](Node& node){ return node.get_id() == id; }); };

    iterator begin() { return nodes_.begin(); };
    iterator end() { return nodes_.end(); };
    const_iterator cbegin() const { return nodes_.cbegin(); };
    const_iterator cend() const { return nodes_.cbegin(); };

private:
    container_t nodes_;
};

class Factory {
public:
    // Ramps
    void add_ramp(Ramp &&r) { ramps_.add(std::move(r)); };
    void remove_ramp(ElementID id) { ramps_.remove_by_id(id); };

    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) { return ramps_.find_by_id(id); };
    NodeCollection<Ramp>::const_iterator ramp_cbegin() { return ramps_.begin(); }
    NodeCollection<Ramp>::const_iterator ramp_cend() { return ramps_.end(); }

    // Workers
    void add_worker(Worker &&w) { workers_.add(std::move(w)); };
    void remove_worker(ElementID id);

    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) { return workers_.find_by_id(id); };
    NodeCollection<Worker>::const_iterator worker_cbegin() { return workers_.begin(); };
    NodeCollection<Worker>::const_iterator worker_cend() { return workers_.end(); };

    // Storehouses
    void add_storehouse(Storehouse &&s) { storehouses_.add(std::move(s)); };
    void remove_storehouse(ElementID id) { storehouses_.remove_by_id(id); };

    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) { return storehouses_.find_by_id(id); };
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() { return storehouses_.begin(); };
    NodeCollection<Storehouse>::const_iterator storehouse_cend() { return storehouses_.end(); };


    bool is_consistent();
    void do_deliveries(Time t){ for (auto & ramp : ramps_) ramp.deliver_goods(t); };
    void do_package_passing() {
        for (auto & ramp : ramps_) ramp.send_package();
        for (auto & worker : workers_) worker.send_package();
    };
    void do_work(Time t) { for (auto & worker : workers_) worker.do_work(t); };

private:
    NodeCollection<Ramp> ramps_;
    NodeCollection<Worker> workers_;
    NodeCollection<Storehouse> storehouses_;
};


// Factory IO
enum class ElementType{
    RAMP, WORKER, STOREHOUSE, LINK
};

struct ParsedLineData{
    ElementType element_type;
    std::map<std::string, std::string> parameters;
};

Factory load_factory_structure(std::istream &is);

void save_factory_structure(Factory& factory, std::ostream& os);

#endif //NETSIM_FACTORY_HPP
