//
// Created by Daniel on 12/17/2021.
//

#include "nodes.hpp"

//ReceiverPreferences
void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    preferences_[r] = 1;
    std::size_t size = preferences_.size();

    for (auto& kv : preferences_)
    {
        kv.second = 1 / (double)size;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    preferences_.erase (r);
    std::size_t size = preferences_.size();

    for (auto& kv : preferences_)
    {
        kv.second = 1 / (double)size;
    }
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    double rand = pg_();
    double distribution_fun = 0;

    for (auto& kv : preferences_)
    {
        distribution_fun = distribution_fun + kv.second;

        if(rand <= distribution_fun){
            return kv.first;
        }
    }
    return nullptr;
}

//PackageSender
void PackageSender::send_package() {
    if(sending_buffer_) {
        auto receiver = receiver_preferences_.choose_receiver();
        receiver->receive_package(std::move(*sending_buffer_));
        sending_buffer_.reset();
    }
}

void PackageSender::push_package(Package && p) {
    sending_buffer_.emplace(std::move(p));
}

//Ramp
void Ramp::deliver_goods(Time t) {
    if((t - 1) % di_ == 0) {
        sending_buffer_ = Package();
    }
}

//Worker
void Worker::do_work(Time t) {
    {
        if(!(*q_).empty() && (!processing_buffer_)) {
            processing_buffer_.emplace((*q_).pop());
            processing_start_time_ = t;
        }

        if(processing_buffer_){
            if(t - processing_start_time_ >= pd_ - 1) {
                sending_buffer_.swap(processing_buffer_);
                processing_buffer_.reset();
            }
        }
    }
}
