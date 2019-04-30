#include "core/space/IReactiveSpace.hh"

#include "core/foundations/ProtectedSetIdentifier.hh"

namespace rx::space::core::reactive_update{
    Update nextScope(const Update& update){
        return std::make_tuple(
            foundations::protected_set::nextScope(std::get<0>(update)),
            std::get<1>(update));
    }
}