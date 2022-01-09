//
// Created by Daniel on 12/15/2021.
//

#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "types.hpp"
#include "package.hpp"

enum class PackageQueueType {
    FIFO, LIFO
};

class IPackageStockpile{
public:
    virtual void push(Package&& package) = 0;
    virtual bool empty() = 0;
    virtual std::size_t size() = 0;

    // iterators
    using const_iterator = std::list<Package>::const_iterator;

    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const = 0;

    virtual ~IPackageStockpile() = default;
};

class IPackageQueue : public IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;
};

class PackageQueue : public IPackageQueue {
public:
    explicit PackageQueue(PackageQueueType queue_type) : queue_type_(queue_type) {}

    void push(Package&& package) override { queue_.emplace_back(std::move(package)); }
    bool empty() override { return queue_.empty(); }
    size_t size() override { return queue_.size(); }
    Package pop() override;
    PackageQueueType get_queue_type() override { return queue_type_; }

    const_iterator begin() const override { return queue_.begin(); }
    const_iterator cbegin() const override { return queue_.cbegin(); }
    const_iterator end() const override { return queue_.end(); }
    const_iterator cend() const override { return queue_.cend(); }

    ~PackageQueue() override = default;

private:
    PackageQueueType queue_type_;
    std::list<Package> queue_;
};

#endif //NETSIM_STORAGE_TYPES_HPP
