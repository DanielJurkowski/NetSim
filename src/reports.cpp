//
// Created by Daniel on 1/17/2022.
//

#include "reports.hpp"

bool compare_ramps(NodeCollection<Ramp>::const_iterator r1, NodeCollection<Ramp>::const_iterator r2){
    return (r1->get_id() < r2->get_id());
}

bool compare_workers(NodeCollection<Worker>::const_iterator w1, NodeCollection<Worker>::const_iterator w2){
    return (w1->get_id() < w2->get_id());
}

bool compare_storehouses(NodeCollection<Storehouse>::const_iterator s1, NodeCollection<Storehouse>::const_iterator s2){
    return (s1->get_id() < s2->get_id());
}

bool compare_receivers(IPackageReceiver* r1, IPackageReceiver* r2){
    if(r1->get_receiver_type() == r2->get_receiver_type()){
        return (r1->get_id() < r2->get_id());
    }

    else return r1->get_receiver_type() == ReceiverType::STOREHOUSE;
}

bool IntervalReportNotifier::should_generate_report(Time time) {
    return (time - 1) % t_offset_;
}

bool SpecificTurnsReportNotifier::should_generate_report(Time time) {
    return !(turns_.find(time) != turns_.end());
}

void generate_simulation_turn_report(const Factory &f, std::ostream &os, Time time) {
    os<<"=== [ Turn: "+std::to_string(time)+" ] ===\n";
    os<<"\n";
    os<<"== WORKERS ==\n";
    os<<"\n";

    std::vector<NodeCollection<Worker>::const_iterator> workers;

    for (auto ptr = f.worker_cbegin(); ptr != f.worker_cend(); ptr++){
        workers.emplace_back(ptr);
    }

    sort(workers.begin(), workers.end(), compare_workers);

    for(auto i:workers) {
        os << "WORKER #" + std::to_string(i->get_id()) + "\n";

        if((*i).get_processing_buffer()){
            os << "  PBuffer: #" + std::to_string(i->get_processing_buffer().value().get_id())+" (pt = "+std::to_string(time-i->get_package_processing_start_time()+1)+ ")\n";
        }

        else{
            os<<"  PBuffer: (empty)\n";
        }

        if(i->get_queue()->empty()){
            os<<"  Queue: (empty)\n";
        }

        else{
            os<<"  Queue: ";

            for(auto prod=i->get_queue()->cbegin(); prod != i->get_queue()->cend(); prod++){
                bool is_last = (prod == std::prev(i->get_queue()->cend()));

                if(is_last){
                    os<<"#"+std::to_string((*prod).get_id())+"\n";
                }

                else{
                    os<<"#"+std::to_string((*prod).get_id())+", ";
                }
            }
        }

        if(i->get_sending_buffer()){
            os<<"  SBuffer: #"+ std::to_string(i->get_sending_buffer().value().get_id()) +"\n";
        }

        else{
            os<<"  SBuffer: (empty)\n";
        }
        os<<"\n";
    }

    os<<"\n";
    os<<"== STOREHOUSES ==\n";
    os<<"\n";

    std::vector<NodeCollection<Storehouse>::const_iterator> storehouses;

    for (auto ptr = f.storehouse_cbegin(); ptr != f.storehouse_cend(); ptr++){
        storehouses.emplace_back(ptr);
    }

    sort(storehouses.begin(), storehouses.end(), compare_storehouses);

    for(auto i:storehouses){
        os<<"STOREHOUSE #"+std::to_string(i->get_id())+"\n";
        os<<"  Stock: ";

        if(i->get_stockpile()->empty()){
            os<<"(empty)\n";
        }

        else {
            for(auto prod=i->get_stockpile()->cbegin(); prod != i->get_stockpile()->cend(); prod++){
                bool is_last = (prod == std::prev(i->get_stockpile()->cend()));

                if(is_last){
                    os<<"#"+std::to_string((*prod).get_id())+"\n";
                }

                else{
                    os<<"#"+std::to_string((*prod).get_id())+", ";
                }
            }
        }
        os<<"\n";
    }
}

void generate_structure_report(const Factory &f, std::ostream &os) {
    os<<"\n";
    os<<"== LOADING RAMPS ==\n";
    os<<"\n";
    std::vector<NodeCollection<Ramp>::const_iterator> ramps;

    for (auto ptr = f.ramp_cbegin(); ptr != f.ramp_cend(); ptr++){
        ramps.emplace_back(ptr);
    }

    sort(ramps.begin(), ramps.end(), compare_ramps);

    for(auto i:ramps){
        os<<"LOADING RAMP #"+std::to_string(i->get_id())+"\n";
        os<<"  Delivery interval: "+std::to_string(i->get_delivery_interval())+"\n";
        os<<"  Receivers:\n";

        std::vector<IPackageReceiver*> receivers;

        for (auto receiver_preference : i->receiver_preferences_){
            receivers.push_back(receiver_preference.first);
        }

        sort(receivers.begin(), receivers.end(), compare_receivers);

        for(const IPackageReceiver* rec:receivers){
            if(rec->get_receiver_type() == ReceiverType::WORKER){
                os<<"    worker #"+std::to_string(rec->get_id())+"\n";
            }

            else {
                os<<"    storehouse #"+std::to_string(rec->get_id())+"\n";
            }
        }
        os<<"\n";
    }

    os<<"\n";
    os<<"== WORKERS ==\n";
    os<<"\n";

    std::vector<NodeCollection<Worker>::const_iterator> workers;

    for (auto ptr = f.worker_cbegin(); ptr != f.worker_cend(); ptr++){
        workers.emplace_back(ptr);
    }

    sort(workers.begin(), workers.end(), compare_workers);

    for(auto i:workers){
        os<<"WORKER #"+std::to_string(i->get_id())+"\n";
        os<<"  Processing time: "+std::to_string(i->get_processing_duration())+"\n";

        if(i->get_queue()->get_queue_type() == PackageQueueType::FIFO){
            os<<"  Queue type: FIFO\n";
        }

        else{
            os<<"  Queue type: LIFO\n";
        }

        os<<"  Receivers:\n";

        std::vector<IPackageReceiver*> receivers;

        for (auto ptr = i->receiver_preferences_.cbegin(); ptr != i->receiver_preferences_.cend(); ptr++){
            receivers.push_back((*ptr).first);
        }

        sort(receivers.begin(), receivers.end(), compare_receivers);

        for(const IPackageReceiver* rec:receivers){
            if(rec->get_receiver_type() == ReceiverType::WORKER){
                os<<"    worker #"+std::to_string(rec->get_id())+"\n";
            }

            else {
                os<<"    storehouse #"+std::to_string(rec->get_id())+"\n";
            }
        }
        os<<"\n";
    }

    os<<"\n";
    os<<"== STOREHOUSES ==\n";
    os<<"\n";

    std::vector<NodeCollection<Storehouse>::const_iterator> storehouses;

    for (auto ptr = f.storehouse_cbegin(); ptr != f.storehouse_cend(); ptr++){
        storehouses.push_back(ptr);
    }
    sort(storehouses.begin(), storehouses.end(), compare_storehouses);

    for(auto i:storehouses){
        os<<"STOREHOUSE #"+std::to_string(i->get_id())+"\n";
        os<<"\n";
    }
}


