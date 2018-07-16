/**
 *  @file
 *  @copyright defined in myeosio/LICENSE.txt
 */

#pragma once

#include <vector>

namespace myeosio {

template<typename T>
class consumer_core {
public:
    virtual ~consumer_core() {}
    virtual void consume(const std::vector<T>& elements) = 0;
};

} // namespace


