#include "store/infrastructure/ReactiveMemberEntry.hh"

namespace rx::space::store::infrastructure{

    ReactiveMemberEntry::~ReactiveMemberEntry(){
        unsubscribeNode(context);
    }

    ReactiveMemberEntry::ReactiveMemberEntry() :
        context(new ReactiveNodeEntryContext{ nullptr }) {}

    void ReactiveMemberEntry::setMember(types::IReactiveSpaceMemberPtr&& member) const;
        context->activeNode = std::move(member);
    }
}