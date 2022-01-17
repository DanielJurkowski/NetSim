//
// Created by Daniel on 12/17/2021.
//

#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <map>
#include <utility>

#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "helpers.hpp"
#include "config.hpp"

enum class ReceiverType{
    WORKER, STOREHOUSE
};

class IPackageReceiver{
public:
    virtual void receive_package(Package&& package) = 0;
    virtual ElementID get_id() const = 0;

    #if (defined EXERCISE_ID && EXERCISE_ID != EXERCISE_ID_NODES)
    virtual ReceiverType get_receiver_type() const = 0;
    #endif

    using const_iterator = IPackageStockpile::const_iterator;

    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const = 0;

    virtual ~IPackageReceiver() = default;
};

class Storehouse : public IPackageReceiver{
public:
    explicit Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d =
            std::make_unique<PackageQueue>(PackageQueueType::LIFO)) : id_(id), d_(std::move(d)) {}

    void receive_package(Package&& package) override { d_->push(std::move(package)); }
    ElementID get_id() const override { return id_; }


    ReceiverType get_receiver_type() const { return ReceiverType::STOREHOUSE; }

    const_iterator begin() const override { return d_->begin(); }
    const_iterator cbegin() const override { return d_->cbegin(); }
    const_iterator end() const override { return d_->end(); }
    const_iterator cend() const override { return d_->cend(); }

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;

};

class ReceiverPreferences{
public:
    explicit ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : pg_(std::move(pg)) {}

    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    const_iterator begin() const { return preferences_.begin(); }
    const_iterator end() const { return preferences_.end(); }
    const_iterator cbegin() const { return preferences_.cbegin(); }
    const_iterator cend() const { return preferences_.cend(); }

    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t & get_preferences() const {return preferences_;}

private:
    ProbabilityGenerator pg_;
    preferences_t preferences_;

};

class PackageSender{
public:
    PackageSender() : sending_buffer_(std::nullopt) {}

    PackageSender(PackageSender&) = default;
    PackageSender(PackageSender&&) = default;

    void send_package();
    const std::optional<Package>& get_sending_buffer() const {return sending_buffer_;}

    ReceiverPreferences receiver_preferences_;
protected:
    virtual void push_package(Package&& package);
    std::optional<Package> sending_buffer_;
};

class Ramp : public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {};

    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const { return di_; }
    ElementID get_id() const { return id_; }

private:
    ElementID id_;
    TimeOffset di_;
};

class Worker : public PackageSender, public IPackageReceiver {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}

    void do_work(Time t);
    TimeOffset get_processing_duration() const { return pd_; }
    Time get_package_processing_start_time() const { return processing_start_time_; }
    void receive_package(Package&& package) override { q_->push(std::move(package)); }
    ElementID get_id() const override { return id_; }
    ReceiverType get_receiver_type() const { return ReceiverType::WORKER; }


    const std::optional<Package>& get_processing_buffer() const {return processing_buffer_;}
    IPackageQueue* get_queue() const {return q_.get();}

    const_iterator begin() const override { return q_->begin(); }
    const_iterator cbegin() const override { return q_->cbegin(); }
    const_iterator end() const override { return q_->end(); }
    const_iterator cend() const override { return q_->cend(); }

private:
    ElementID id_;
    TimeOffset pd_;
    Time processing_start_time_;
    std::unique_ptr<IPackageQueue> q_;
    std::optional<Package> processing_buffer_;
};


#endif //NETSIM_NODES_HPP
