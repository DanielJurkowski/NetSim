//
// Created by Daniel on 12/15/2021.
//

#include "storage_types.hpp"

Package PackageQueue::pop(){
    switch (queue_type_)
    {
        case PackageQueueType::FIFO:{
            Package package = queue_.front();
            queue_.pop_back();
            return package;
        }

        // dla wszystkich innych przypadków, tj. LIFO
        default:
            Package package = queue_.back();
            queue_.pop_front();
            return package;
    }
}

