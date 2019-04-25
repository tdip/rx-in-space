#include "core/ReactiveValueContext.hh"

namespace rx::space::core{
    ReactiveValueContextPtr merge(std::vector<ReactiveValueContextPtr>& items){
        std::vector<Value> values;
        std::vector<ValueProps> props;
        values.reserve(items.size());

        for(
            auto&& item = items.begin();
            item != items.end();
            item++){

            values.emplace_back(*(*item)->value());
            props.emplace_back(*(*item)->properties());
        }

        ValuePtr value = std::make_shared<Value>(std::move(values));
        ValuePropsPtr properties = std::make_shared<ValueProps>(std::move(props));

        return ReactiveValueContext::create(properties, value);
    }
}