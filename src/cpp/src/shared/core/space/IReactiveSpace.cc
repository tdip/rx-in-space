#include "core/space/IReactiveSpace.hh"

#include "core/foundations/ProtectedSetIdentifier.hh"

namespace rx::space::core::reactive_update{

    int64_t getScopedIndex(const Update& update){
        return foundations::protected_set::getScopedIndex(update.setId);
    }

    Update nextScope(const Update& update){
        return {
            foundations::protected_set::nextScope(update.setId),
            update.operation
        };
    }
}