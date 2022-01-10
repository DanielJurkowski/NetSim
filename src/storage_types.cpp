//
// Created by Daniel on 12/15/2021.
//

#include "storage_types.hpp"

Package PackageQueue::pop(){
    switch (PackageQueue::queue_type_)
    {
        case PackageQueueType::FIFO:{
            Package first_element(std::move(queue_.front()));
            PackageQueue::queue_.pop_front();
            return first_element;
        }

        case PackageQueueType::LIFO:{
            Package first_element(std::move(queue_.back()));
            PackageQueue::queue_.pop_back();
            return first_element;
        }
    }
    Package package;
    return package;
}


