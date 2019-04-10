#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "rx.hh"

#include "util/ObservableSubjectBase.hh"

namespace rx::space::util{

    template<typename T>
    class CombineLatestContext : public ObservableSubjectBaseContext<std::vector<T>>{

        public:
        CombineLatestContext(
            const std::vector<observable<T>>& _observables) :

            ObservableSubjectBaseContext<std::vector<T>>(),
            observables(_observables),
            mask(_observables.size()),
            values(_observables.size()),
            itemSubscriptions(_observables.size()){}

        protected:
        virtual void onActivate() override{
            for(size_t i = 0; i < observables.size(); i++){
                // todo: don't capture this
                itemSubscriptions[i] = observables[i].subscribe([i, this](T v){ onNext(i, v); });
            }
        }

        virtual void onDeActivate() override{
            for(
                auto&& subscription = itemSubscriptions.begin();
                subscription != itemSubscriptions.end();
                subscription++){

                subscription->unsubscribe();
            }
        }

        private:
        const std::vector<rx::observable<T>> observables;
        std::vector<bool> mask;
        std::vector<T> values;
        std::vector<rx::composite_subscription> itemSubscriptions;

        void onNext(size_t i, T value){

            mask[i] = true;
            values[i] = value;

            for(auto&& item = mask.begin(); item != mask.end(); item++){
                if(!(*item)){
                    return;
                }
            }

            auto& subscriptions = ObservableSubjectBaseContext<std::vector<T>>::subscriptions;
            for(
                auto&& subscription = subscriptions.begin();
                subscription != subscriptions.end();
                subscription++){

                subscription->second.on_next(values);
            }
        }

    };

    template<typename T>
    class CombineLatestSubject : public ObservableSubjectBase<std::vector<T>>{
        public:
        CombineLatestSubject(const std::vector<observable<T>>& _observables) :
            ObservableSubjectBase<std::vector<T>>(
                std::make_shared<CombineLatestContext<T>>(
                    _observables)) {}
    };

    template<typename T>
    rx::observable<std::vector<T>> combineLatest(std::vector<rx::observable<T>>& oss){

        return rx::create<std::vector<T>>(
            std::function<void(rx::subscriber<std::vector<T>>& subscriber)>(
                [ctx = CombineLatestSubject(oss)]
                (rx::subscriber<std::vector<T>>& subscriber){

                    subscriber.add(
                        ctx.observable().subscribe(
                            [subscriber](std::vector<T> value){ subscriber.on_next(value); }));
            }));
    }
}