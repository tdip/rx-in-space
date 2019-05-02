#include <iterator>

#include "core/foundations/Key.hh"

#include "core/space/ReactiveMemberValueStream.hh"

namespace rx::space::structures::types{

    class IReactiveSpaceItems{
    public:
        typedef std::iterator<std::bidirectional_iterator_tag, std::pair<core::Key, core::ReactiveMemberValueStream>> Iterator;

        virtual ~IReactiveSpaceItems() = default;

        virtual Iterator find(const core::GroupKeySet&) const = 0;
    };

    class IReactiveSpaceMutableItems : public IReactiveSpaceItems{

        virtual void update(const core::Key&) = 0;
    };
}