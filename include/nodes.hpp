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

#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "helpers.hpp"

enum class ReceiverType{
    WORKER, STOREHOUSE
};

class IPackageReceiver{
public:
    virtual void receive_package(Package&& p) = 0;
    virtual ElementID get_id() const = 0;

    using const_iterator = IPackageStockpile::const_iterator;

    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const = 0;

    virtual ~IPackageReceiver() = default;
};

class Storehouse : IPackageReceiver{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) {}

    //

    void receive_package(Package&& p) override { d_->push(std::move(p)); }
    ElementID get_id() const override { return id_; }

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;

};

class ReceiverPreferences{
public:
    ReceiverPreferences(ProbabilityGenerator pg) : pg_(pg) {}

    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    // iteratory

    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    preferences_t& get_preferences();

private:
    ProbabilityGenerator pg_;

};

class PackageSender{
public:
    PackageSender() = default;

    PackageSender(PackageSender& ps) = default;
    PackageSender(PackageSender&& ps) = default;

    void send_package();
    //std::optional<Package>& get_sending_buffer() const { return sending_buffer_; }

protected:
    virtual void push_package(Package&& package);

private:
    //std::optional<Package>& sending_buffer_;
    //ReceiverPreferences receiverPreferences_;
};

class Ramp : PackageSender{
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {};

    void deliver_goods(Time t);
    TimeOffset get_deilvery_interval() const { return di_; }
    ElementID get_id() const { return id_; }


private:
    ElementID id_;
    TimeOffset di_;
};

class Worker : public PackageSender, public IPackageReceiver {
public:
    //Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(q) {}

    void do_work(Time t);
    TimeOffset get_processing_duration() const { return pd_; }
    Time get_package_processing_start_time() const { return processing_start_time_; }

    void receive_package(Package&& p) override { q_->push(std::move(p)); }
    ElementID get_id() const override { return id_; }

private:
    ElementID id_;
    TimeOffset pd_{};
    Time processing_start_time_{};
    std::unique_ptr<IPackageQueue> q_;
};


#endif //NETSIM_NODES_HPP
