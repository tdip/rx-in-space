#include "store/infrastructure/ReactiveQueryAggregator.hh"

#include "util/operators.hh"

namespace rx::space::store::infrastructure{

    ReactiveQueryAggregator::ReactiveQueryAggregator(
        const core::Query& query,
        std::vector<std::reference_wrapper<const types::ReactiveMemberValueStream>>& values) :
        _stream(util::merge(values)){}

    ReactiveQueryAggregator::~ReactiveQueryAggregator(){}

    const types::ReactiveMemberValueStream& ReactiveQueryAggregator::steam() const{
        return _stream;
    }

    static types::ReactiveMemberValueStream aggregator(
        const core::Query& query,
        std::vector<std::reference_wrapper<const types::ReactiveMemberValueStream>>& oss){

        return rx::create<core::ReactiveValueContextPtr>(
            [ctx = std::make_shared<ReactiveQueryAggregator>(query, oss)]
            (rx::subscriber<core::ReactiveValueContextPtr> subs){

            subs.add(ctx->steam().subscribe(subs));
            subs.add([ctx](){});
        });
    }
}