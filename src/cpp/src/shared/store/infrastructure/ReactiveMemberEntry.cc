#include "store/infrastructure/ReactiveNodeEntry.hh"

#include <cassert>

namespace rx::space::store::infrastructure{

    ReactiveMemberEntry::~ReactiveMemberEntry(){
        unsubscribeNode(context);
    }

    ReactiveMemberEntry::ReactiveMemberEntry() :
        context(new ReactiveNodeEntryContext{ nullptr }) {}

    void ReactiveMemberEntry::setNode(IReactiveNodePtr&& node) const{
        context->activeNode = std::move(node);
    }
}