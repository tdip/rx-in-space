#include "store/collection/ReactiveSpace.hh"

namespace rx::space::store::collection{


    const ReactiveMemberValueStream ReactiveSpace::query(const core::Query& query){
        std::vector<std::reference_wrapper<ReactiveMemberEntry>> entries;

        return rx::create<core::ReactiveValueContextPtr>();
    }
}