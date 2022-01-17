//
// Created by Daniel on 12/17/2021.
//

#include "types.hpp"
#include "factory.hpp"

// Factory
enum class NodeColor { UNVISITED, VISITED, VERIFIED };

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if(node_colors[sender] == NodeColor::VERIFIED) { return true; }

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

// Factory IO

ParsedLineData parse_line(std::string line) {
    std::vector<std::string> tokens;
    std::string token;

    std::istringstream token_stream(line);
    char delimiter = ' ';

    while (std::getline(token_stream, token, delimiter)) {
        tokens.push_back(token);
    }

    ParsedLineData object;

    if(tokens[0] == "LOADING_RAMP"){
        object.element_type = ElementType::RAMP;
    }

    else if(tokens[0] == "WORKER"){
        object.element_type = ElementType::WORKER;
    }

    else if(tokens[0] == "STOREHOUSE"){
        object.element_type = ElementType::STOREHOUSE;
    }

    else if(tokens[0] == "LINK"){
        object.element_type = ElementType::LINK;
    }

    else {
        throw std::logic_error("Error");
    }

    tokens.erase(tokens.begin());

    for(const auto& t:tokens){
        std::stringstream stringstream(t);
        std::string map[2];

        int i = 0;
        while (std::getline(stringstream, token, '=')){
            map[i] = token;
            i++;
        }

        object.parameters[map[0]] = map[1];
    }

    return object;
}

Factory load_factory_structure(std::istream &is){
    Factory factory;
    std::string line;

    while (std::getline(is, line)){
        if (!line.empty() && line[0] != ';'){
            ParsedLineData data = parse_line(line);

            if (data.element_type == ElementType::RAMP){
                factory.add_ramp(Ramp(std::stoi(data.parameters["id"]),
                                                std::stoi(data.parameters["delivery-interval"])));
            }

            else if (data.element_type == ElementType::WORKER){
                if (data.parameters["queue-type"] == "LIFO"){
                    factory.add_worker(Worker(std::stoi(data.parameters["id"]),
                                              std::stoi(data.parameters["processing-time"]),
                                              std::make_unique<PackageQueue>(PackageQueueType::LIFO)));
                }

                if (data.parameters["queue-type"] == "FIFO"){
                    factory.add_worker(Worker(std::stoi(data.parameters["id"]),
                                              std::stoi(data.parameters["processing-time"]),
                                              std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
                }
            }

            else if (data.element_type == ElementType::STOREHOUSE){
                factory.add_storehouse(Storehouse(std::stoi(data.parameters["id"])));
            }

            else if (data.element_type == ElementType::LINK){
                std::stringstream stringstream_src(data.parameters["src"]);
                std::stringstream stringstream_dest(data.parameters["dest"]);

                std::string map_src[2];
                std::string map_dest[2];
                std::string token;

                int i = 0;

                while (std::getline(stringstream_src, token, '-')) {
                    map_src[i] = token;
                    i++;
                }

                i = 0;
                while (std::getline(stringstream_dest, token, '-')) {
                    map_dest[i] = token;
                    i++;
                }

                if(map_src[0]=="ramp" && map_dest[0]=="worker"){
                    Ramp& reciever = *(factory.find_ramp_by_id(std::stoi(map_src[1])));
                    reciever.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(std::stoi(map_dest[1]))));
                }

                else if(map_src[0]=="worker" && map_dest[0]=="store"){
                    Worker& worker = *(factory.find_worker_by_id(std::stoi(map_src[1])));
                    worker.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(std::stoi(map_dest[1]))));
                }

                else if(map_src[0]=="worker" && map_dest[0]=="worker"){
                    Worker& worker = *(factory.find_worker_by_id(std::stoi(map_src[1])));
                    worker.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(std::stoi(map_dest[1]))));
                }

                else if(map_src[0]=="ramp" && map_dest[0]=="store"){
                    Ramp& ramp = *(factory.find_ramp_by_id(std::stoi(map_src[1])));
                    ramp.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(std::stoi(map_dest[1]))));
                }
            }
        }
    }
    return factory;
}

void save_factory_structure(Factory& factory, std::ostream& os){
    for (auto ptr = factory.ramp_cbegin(); ptr != factory.ramp_cend(); ptr++){
        os<<"LOADING_RAMP id="+std::to_string((*ptr).get_id())+" delivery-interval="+std::to_string((*ptr).get_delivery_interval())+"\n";
    }

    for (auto ptr = factory.worker_cbegin(); ptr != factory.worker_cend(); ptr++){
        if((*ptr).get_queue()->get_queue_type() == PackageQueueType::FIFO){
            os<<"WORKER id="+std::to_string((*ptr).get_id())+" processing-time="+std::to_string((*ptr).get_processing_duration())+" queue-type=FIFO"+"\n";
        }

        if((*ptr).get_queue()->get_queue_type() == PackageQueueType::LIFO){
            os<<"WORKER id="+std::to_string((*ptr).get_id())+" processing-time="+std::to_string((*ptr).get_processing_duration())+" queue-type=LIFO"+"\n";
        }
    }

    for (auto ptr = factory.storehouse_cbegin(); ptr != factory.storehouse_cend(); ptr++){
        os<<"STOREHOUSE id="+std::to_string((*ptr).get_id())+"\n";
    }

    for (auto ptr = factory.ramp_cbegin(); ptr != factory.ramp_cend(); ptr++){
        for (auto ptr_1 = (*ptr).receiver_preferences_.cbegin(); ptr_1 != (*ptr).receiver_preferences_.cend(); ptr_1++){
            if((*ptr_1).first->get_receiver_type() == ReceiverType::WORKER){
                os<<"LINK src=ramp-"+std::to_string((*ptr).get_id())+" dest=worker-"+std::to_string((*ptr_1).first->get_id())+"\n";
            }
        }
    }

    for (auto ptr = factory.worker_cbegin(); ptr != factory.worker_cend(); ptr++){
        for (auto ptr_1 = (*ptr).receiver_preferences_.cbegin(); ptr_1 != (*ptr).receiver_preferences_.cend(); ptr_1++){
            if((*ptr_1).first->get_receiver_type() == ReceiverType::STOREHOUSE){
                os<<"LINK src=worker-"+std::to_string((*ptr).get_id())+" dest=store-"+std::to_string((*ptr_1).first->get_id())+"\n";
            }

            if((*ptr_1).first->get_receiver_type() == ReceiverType::WORKER){
                os<<"LINK src=worker-"+std::to_string((*ptr).get_id())+" dest=worker-"+std::to_string((*ptr_1).first->get_id())+"\n";
            }

        }
    }
    os.flush();
}