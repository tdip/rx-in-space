#include "store/NodeEntryQuerySpace.hh"

namespace rx::space::store{

    IReactiveNodeStreamPtr NodeEntryQuerySpace::query(core::QueryArgs&& query){

    }


    virtual const rx::observable<ReactiveNodeValue>& NodeEntryQuerySpace::observable() const override{
        return subject.observable();
    }

    void NodeEntryQuerySpace::activate(){
        inner = outerSpace.query(query);
        inner.observable().subscribe([this](ReactiveNodeValue value){ subject.onNext(); });
    }

    void NodeEntryQuerySpace::deactivate(){
        inner.reset();
    }
}