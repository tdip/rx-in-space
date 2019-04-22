#pragma once

#include <memory>

#include "store/types/IReactiveMemberStream.hh"
#include "store/types/IReactiveSpaceMember.hh"

namespace rx::space::store::infrastructure{

    struct ReactiveMemberInstanceContext{
        const core::QueryArgs query;
        types::IReactiveSpaceMemberPtr activeMember;
    };

    class ReactiveMemberInstanceStream : public types::IReactiveMemberStream{

    };

    class ReactiveMemberInstance{
    typedef std::unique_ptr<ReactiveMemberInstanceContext> Context;

    public:
    ReactiveMemberInstance(const core::QueryArgs&);

    types::IReactiveMemberStreamPtr stream() const;

    void setActiveMember(types::IReactiveMemberStreamPtr);

    private:
        const Context context;
    };
}