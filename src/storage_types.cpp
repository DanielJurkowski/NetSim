//
// Created by Daniel on 12/15/2021.
//

#include "storage_types.hpp"

Package PackageQueue::pop(){
    switch (PackageQueue::queue_type_)
    {
        case PackageQueueType::FIFO:{
            PackageQueue::queue_.pop_back();
            return PackageQueue::queue_.front();
        }

        // dla wszystkich innych przypadków, tj. LIFO
        default:
            PackageQueue::queue_.pop_front();
            return PackageQueue::queue_.back();
    }
}

