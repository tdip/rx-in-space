#pragma once

#include <optional>
#include <tuple>
#include <vector>

#include "core/foundations/ProtectedSetIdentifier.hh"

#include "core/space/IReactiveQuerySpace.hh"
#include "core/space/UpdateException.hh"

namespace rx::space::core{

    struct SetReactiveSpace{
        const IReactiveQuerySpacePtr space;
    };

    struct DeleteValue{};

    typedef std::variant<SetReactiveSpace, DeleteValue> Operation;

    struct Update{
        foundations::ProtectedSetIdentifier setId;
        Operation operation;
    };

    typedef std::vector<Update> ReactiveUpdates;

    namespace reactive_update{
        int64_t getScopedIndex(const Update&);
        Update nextScope(const Update&);
    }

    /**
     * Interface for a reactive query space that has
     * internal reactive subspaces that can be updated.
     */
    class IReactiveSpace : public IReactiveQuerySpace{
    public:
        virtual std::optional<exceptions::UpdateException> update(const ReactiveUpdates&) = 0;
    };

    using IReactiveSpacePtr = std::shared_ptr<IReactiveSpace>;
}