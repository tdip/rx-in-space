#include "store/infrastructure/ReactiveQueryInstance.hh"

namespace rx::space::store::infrastructure{

    std::unordered_map<Key, ReactiveMemberInstancePtr> queryMembers(
        const ReactiveQueryContextBasePtr& queryContext,
        std::vector<ReactiveMemberEntry*>& entries){

        std::unordered_map<Key, ReactiveMemberInstancePtr> result;
        result.reserve(entries.size());

        for(
            auto&& entry = entries.begin();
            entry != entries.end();
            entry++){

            auto&& value = *entry;
            result.emplace(
                std::make_pair(
                    fromOutputSet(value->outputSet()),
                    ReactiveMemberInstance::create(queryContext, value->getMember())));
        }

        return result;
    }

    ReactiveQueryInstance::ReactiveQueryInstance(
        const ReactiveQueryContextBasePtr& queryContext,
        std::vector<ReactiveMemberEntry*>& entries) :
            context(new ReactiveQueryInstanceContext{
                queryContext,
                queryMembers(queryContext, entries)}) {}
}