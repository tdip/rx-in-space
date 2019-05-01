#pragma once

#include <stdint.h>
#include <variant>
#include <vector>

namespace rx::space::core{
    typedef int128_t Key;

    struct KeySet;

    struct GroupKeySet{
        const Key module;
        const Key item;

        GroupKeySet& operator=(const KeySet& other){
            const_cast<Key&>(moudle) = other.module;
            const_cast<Key&>(module) = other.item;

            return *this;
        }
    };

    typedef std::pair<KeySet, KeySet> Union;

    typedef std::pair<KeySet, KeySet> Intersection;

    struct KeySet{
        const std::variant<GroupKeySet, Union, Intersection> expression;

        KeySet& operator=(const KeySet& other){
            const_cast<std::variant<GroupKeySet, Union, Intersection>&>(expression) = other.expression;
            return *this;
        };
    };

    using SetIdentifier = std::vector<int64_t>;

    struct AllSets{};
    struct PowerSetIdentifier{
        std::unordered_map<int64_t, std::variant<AllSets, PowerSetIdentifier>> members;
    };



    namespace set_identifier{
        SetIdentifier nextScope(const SetIdentifier&);
        SetIdentifier intersect(const SetIdentifier&, const SetIdentifier&);
    }

    namespace power_set_identifier{
        bool inScope(const int64_t, const PowerSetIdentifier&);
        PowerSetIdentifier intersect(const PowerSetIdentifier&, const PowerSetIdentifier&);
    }
}