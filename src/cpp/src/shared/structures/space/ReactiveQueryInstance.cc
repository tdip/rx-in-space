#include "structures/space/ReactiveQueryInstance.hh"

namespace rx::space::structures{

    const core::KeyPowerSet& ReactiveQueryInstance::query() const{
        return _query;
    }
}