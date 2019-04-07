#include "store/ReactiveNodeEntry.hh"

namespace rx::space::store{

    ReactiveNodeInstance ReactiveNodeEntry::activate(){
        return ReactiveNodeInstance(observable);
    }
}