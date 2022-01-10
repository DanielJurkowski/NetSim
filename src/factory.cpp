//
// Created by Daniel on 12/17/2021.
//

#include "types.hpp"
#include "factory.hpp"


enum class NodeColor { UNVISITED, VISITED, VERIFIED };


bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if(node_colors[sender] == NodeColor::VERIFIED) return true;

    node_colors[sender] = NodeColor::VISITED;

    if((*sender).receiver_preferences_.cend() == (*sender).receiver_preferences_.cbegin()){
        throw std::logic_error("Error");
    }

    bool is_storehouse_reachable = true;
    bool sender_has_receiver = false;

    for(auto ptr = (*sender).receiver_preferences_.cbegin(); ptr != (*sender).receiver_preferences_.cend(); ptr++){
        if((*ptr).first->get_receiver_type() == ReceiverType::STOREHOUSE){
            sender_has_receiver = true;
        }

        else if((*ptr).first->get_receiver_type() == ReceiverType::WORKER){
            IPackageReceiver* receiver_ptr = (*ptr).first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);

            if(sendrecv_ptr == sender) {
                continue;
            }

            sender_has_receiver = true;

            if(node_colors[sendrecv_ptr] == NodeColor::UNVISITED) {
                is_storehouse_reachable = has_reachable_storehouse(sendrecv_ptr, node_colors);
            }
        }
    }

    node_colors[sender] = NodeColor::VERIFIED;

    if(sender_has_receiver && is_storehouse_reachable){
        return true;
    }

    else{
        throw std::logic_error("Error");
    }
}

void Factory::remove_worker(ElementID id) {
    IPackageReceiver* worker = &(*workers_.find_by_id(id));

    for (auto & ptr : workers_){
        ptr.receiver_preferences_.remove_receiver(worker);
    }

    for (auto & ramp : ramps_){
        ramp.receiver_preferences_.remove_receiver(worker);
    }

    workers_.remove_by_id(id);
}

bool Factory::is_consistent() {
    std::map<const PackageSender *, NodeColor> color;

    for (auto & ptr : workers_){
        Worker* worker = &ptr;
        auto sender = dynamic_cast<PackageSender*>(worker);
        color[sender] = NodeColor::UNVISITED;
    }

    for (auto & ptr : ramps_){
        Ramp* ramp = &ptr;
        auto sender = dynamic_cast<PackageSender*>(ramp);
        color[sender] = NodeColor::UNVISITED;
    }

    try {
        for (auto & ptr : ramps_){
            Ramp* ramp = &ptr;
            auto sender = dynamic_cast<PackageSender*>(ramp);
            has_reachable_storehouse(sender, color);
        }
    }

    catch (const std::logic_error&) {
        return false;
    }

    return true;
}
