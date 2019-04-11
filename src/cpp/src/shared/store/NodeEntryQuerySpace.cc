#include "store/NodeEntryQuerySpace.hh"

namespace rx::space::store{

    IReactiveNodeStreamPtr NodeEntryQuerySpace::query(const core::QueryArgs& query){
        auto stream = std::make_shared<NodeEntryQuerySpaceStream>(outerSpace, query);
        streams.push_back(stream);
        return stream;
    }

    void NodeEntryQuerySpace::activate(){

        isActive = true;
        for(
            auto wStream = streams.begin();
            wStream != streams.end();
            wStream++){

            auto stream = wStream->lock();
            if(stream){
                stream->activate();
            }
        }
    }
    
    void NodeEntryQuerySpace::deactivate(){

        // Todo: remove the invalid pointers
        // from the array
        isActive = false;
        for(
            auto wStream = streams.begin();
            wStream != streams.end();
            wStream++){

            auto stream = wStream->lock();
            if(stream){
                stream->deactivate();
            }
        }
    }

    const rx::observable<core::ContextPtr>& NodeEntryQuerySpaceStream::observable() const{
        return subject.observable();
    }

    void NodeEntryQuerySpaceStream::activate(){
        inner = outerSpace.query(query);
        inner->observable().subscribe([this](core::ContextPtr value){ subject.onNext(value); });
    }

    void NodeEntryQuerySpaceStream::deactivate(){
        inner.reset();
    }
}