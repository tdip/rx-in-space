#pragma once

#include "store/IReactiveNodeSource.hh"

namespace rx::space::topology{
    class SetValueSource : public store::IReactiveNodeSource{
    public:
        SetValueSource(const rx::observable<core::IValuePtr>&& _source) : source(_source) {}
        virtual const rx::observable<core::IValuePtr>& observable() const override;
    private:
        const rx::observable<core::IValuePtr> source;
    };
}