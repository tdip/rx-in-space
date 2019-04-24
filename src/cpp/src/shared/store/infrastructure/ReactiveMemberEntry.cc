#include "store/infrastructure/ReactiveMemberEntry.hh"

namespace rx::space::store::infrastructure{

    ReactiveMemberEntry::ReactiveMemberEntry(
        const core::OutputSet& outputSet,
        const types::IReactiveSpaceMemberPtr& activeNode) :
        context(std::make_shared<ReactiveMemberEntryContext>(
            new ReactiveMemberEntryContext{
                outputSet,
                activeNode
            })) {}

    const core::OutputSet& ReactiveMemberEntry::outputSet() const{
        return context->outputSet;
    }

    bool ReactiveMemberEntry::matches(const core::Query&) const{
        return true;
    }

    types::IReactiveSpaceMemberPtr ReactiveMemberEntry::getMember() const{
        return context->activeNode;
    }
}