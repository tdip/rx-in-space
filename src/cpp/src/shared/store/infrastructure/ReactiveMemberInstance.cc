#include "store/infrastructure/ReactiveMemberInstance.hh"

namespace rx::space::store::infrastructure{


    ReactiveMemberInstance::ReactiveMemberInstance(const core::QueryArgs&){}

    types::IReactiveMemberStreamPtr ReactiveMemberInstance::stream() const{

    }

    void ReactiveMemberInstance::setActiveMember(types::IReactiveMemberStreamPtr){
        
    }
}