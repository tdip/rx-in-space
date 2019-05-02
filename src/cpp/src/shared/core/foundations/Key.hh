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
    typedef int64_t Key;

    /**
     * Represetns a set of keys corresponding to
     * the set of reactive streams desired.
     */
    struct KeySet{
        KeySet(const KeySet&);
        KeySet& operator=(const KeySet& other);
        KeySet& operator=(const KeySet&& other) noexcept;        
    };

    typedef std::pair<GroupKeySet, GroupKeySet> Union;
    typedef std::pair<GroupKeySet, GroupKeySet> Intersection;

    struct GroupKeySet{
        const Key module;

        GroupKeySet(const GroupKeySet& other) = default;

        GroupKeySet& operator=(const GroupKeySet&& other) noexcept{
            const_cast<Key&>(module) = other.module;
            return *this;
        }

        GroupKeySet& operator=(const GroupKeySet& other){
            return operator=(std::move(other));
        }
    };

    struct KeySet{

        const std::variant<int, Union, Intersection> expression;

        KeySet(const KeySet&) = default;

        KeySet& operator=(const KeySet& other){
            return operator=(std::move(other));
        };

        KeySet& operator=(const KeySet&& other) noexcept{
            const_cast<std::variant<int, Union, Intersection>&>(expression) = other.expression;
            return *this;
        };
    };
}