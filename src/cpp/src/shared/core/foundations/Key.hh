#pragma once

#include <stdint.h>
#include <variant>
#include <vector>

namespace rx::space::core{

    /**
     * All reactive streams are asociated by a single key.
     * Whenever a query is performed, a set of desired
     * keys is produced and all reactive streams whose
     * key is in that set will be combined into a
     * single stream.
     */
    typedef int64_t KeySet;

    /**
     * Type that represents members of the power set of
     * keys. This allows efficient and precise querying
     * of sets of reactive elements.
     */
    struct KeyPowerSet{
        const KeySet module;

        KeyPowerSet(const KeyPowerSet& other) = default;

        KeyPowerSet& operator=(const KeyPowerSet&& other) noexcept{
            const_cast<KeySet&>(module) = other.module;
            return *this;
        }

        KeyPowerSet& operator=(const KeyPowerSet& other){
            return operator=(std::move(other));
        }
    };
}