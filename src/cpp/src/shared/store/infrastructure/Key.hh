#pragma once

#include <set>

#include "core/Query.hh"
#include "core/OutputSet.hh"

#include "store/infrastructure/Property.hh"

namespace rx::space::store::infrastructure{
    using Key = std::set<Property>;

    Key fromQuery(const core::Query&);

    Key fromOutputSet(const core::OutputSet&);
}

namespace std{
    template<typename K, typename V>
    struct hash<std::pair<K,V>>{
        std::size_t operator()(const std::pair<K,V>& value) const noexcept{
            std::hash<K> kHash;
            std::hash<V> vHash;

            return kHahs(value.first) ^ (vHash(value.second) << 1);
        }
    };

    template<>
    struct hash<rx::space::store::infrastructure::Key>{
        std::size_t operator()(const rx::space::store::infrastructure::Key& key) const noexcept{
            size_t result = 0;
            std::hash<rx::space::store::infrastructure::Property> hasher;

            for(
                auto&& entry = key.begin();
                entry != key.end();
                entry++){

                result ^= (hasher(*entry) << 1);
            }

            return result;
        }
    };

}