#include "store/infrastructure/ReactiveQueryInstance.hh"

namespace rx::space::store::infrastructure{

    std::vector<ReactiveMemberInstancePtr> queryMembers(
        const core::Query& query,
        const IReactiveQuerySpacePtr space,
        std::vector<ReactiveMemberEntry*>& entries){

        std::vector<ReactiveMemberInstancePtr> result;
        result.reserve(entries.size());

        for(
            auto&& entry = entries.begin();
            entry != entries.end();
            entries++){

            result.emplace_back(
                query,
                (*entry)->getMember(),
                space);
        }

        return result;
    }

    ReactiveQueryInstance::ReactiveQueryInstance(
        const core::Query& query,
        const IReactiveQuerySpacePtr space,
        std::vector<ReactiveMemberEntry*>& entries)
        : context(new ReactiveQueryInstanceContext{
            query,
            std::move(_nodeInstances),
            queryMembers(query, space, entries)}) {}
}