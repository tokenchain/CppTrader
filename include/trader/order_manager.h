/*!
    \file order_manager.h
    \brief Order manager definition
    \author Ivan Shynkarenka
    \date 31.07.2017
    \copyright MIT License
*/

#ifndef CPPTRADER_ORDER_MANAGER_H
#define CPPTRADER_ORDER_MANAGER_H

#include "../../domain/order.h"

#include "fast_hash.h"

#include "containers/hashmap.h"
#include "memory/allocator_pool.h"

#include <cassert>

namespace CppTrader {

//! Order manager
/*!
    Order manager is used to register and manage orders.

    Not thread-safe.
*/
class OrderManager
{
public:
    OrderManager();
    OrderManager(const OrderManager&) = delete;
    OrderManager(OrderManager&&) noexcept = default;
    ~OrderManager();

    OrderManager& operator=(const OrderManager&) = delete;
    OrderManager& operator=(OrderManager&&) noexcept = default;

    //! Check if the order manager is not empty
    explicit operator bool() const noexcept { return !empty(); }

    //! Get the order with the given Id
    const Order* operator[](uint64_t id) const noexcept { return GetOrder(id); }

    //! Is the order manager empty?
    bool empty() const noexcept { return _orders.empty(); }

    //! Get the order manager size
    size_t size() const noexcept { return _orders.size(); }

    //! Get the order with the given Id
    /*!
        \param id - Order Id
        \return Pointer to the order with the given Id or nullptr
    */
    const Order* GetOrder(uint64_t id) const noexcept;

    //! Add a new order
    /*!
        \param order - Order to add
        \return Pointer to the new order
    */
    Order* AddOrder(const Order& order);
    //! Replace the order with a similar order but different Id, price and quantity
    /*!
        \param id - Order Id
        \param new_id - Order Id to replace
        \param new_price - Order price to replace
        \param new_quantity - Order quantity to replace
        \return Pointer to the replaced order
    */
    Order* ReplaceOrder(uint64_t id, uint64_t new_id, uint64_t new_price, uint64_t new_quantity);
    //! Replace the order with a new one
    /*!
        \param id - Order Id
        \param new_order - Order to replace
        \return Pointer to the replaced order
    */
    Order* ReplaceOrder(uint64_t id, const Order& new_order);
    //! Delete the order
    /*!
        \param id - Order Id
    */
    void DeleteOrder(uint64_t id);

private:
    CppCommon::DefaultMemoryManager _default_manager;
    CppCommon::PoolMemoryManager<CppCommon::DefaultMemoryManager> _pool_manager;
    CppCommon::PoolAllocator<Order, CppCommon::DefaultMemoryManager> _pool;
    CppCommon::HashMap<uint64_t, Order*, FastHash> _orders;
};

} // namespace CppTrader

#include "order_manager.inl"

#endif // CPPTRADER_ORDER_MANAGER_H
