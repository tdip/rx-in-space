#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "rx.hh"

#include "util/ObservableSubjectBase.hh"

namespace rx::space::util{

    template<typename T>
    using CombineLatestValues = std::shared_ptr<std::vector<T>>;

    template<typename T>
    class CombineLatestContext : public ObservableSubjectBaseContext<CombineLatestValues<T>>{

        public:
        CombineLatestContext(
            const std::vector<observable<T>>& _observables) :

            ObservableSubjectBaseContext<CombineLatestValues<T>>(),
            observables(std::make_unique<std::vector<rx::observable<T>>>(_observables)),
            mask(std::make_unique<std::vector<bool>>(_observables.size())),
            values(std::make_unique<std::vector<T>>(_observables.size())),
            itemSubscriptions(
                std::make_unique<std::vector<rx::composite_subscription>>(_observables.size())){}

        virtual ~CombineLatestContext() override{
            onDeActivate();
        }

        protected:
        virtual void onActivate() override{
            for(size_t i = 0; i < observables->size(); i++){
                // It is ok to capture *this* since this subscriptions
                // get discarded once the object is destroyed.
                itemSubscriptions->operator[](i) = observables->operator[](i).subscribe(
                    [i, this](T v){ onNext(i, v); });
            }
        }

        virtual void onDeActivate() override{
            for(
                auto&& subscription = itemSubscriptions->begin();
                subscription != itemSubscriptions->end();
                subscription++){

                subscription->unsubscribe();
            }
        }

        private:
        const std::unique_ptr<std::vector<rx::observable<T>>> observables;
        const std::unique_ptr<std::vector<bool>> mask;
        const std::unique_ptr<std::vector<T>> values;
        const std::unique_ptr<std::vector<rx::composite_subscription>> itemSubscriptions;

        void onNext(size_t i, T value) const{

            mask->operator[](i) = true;
            values->operator[](i) = value;

            for(auto&& item = mask->begin(); item != mask->end(); item++){
                if(!(*item)){
                    return;
                }
            }

            auto& subscriptions = ObservableSubjectBaseContext<CombineLatestValues<T>>::subscriptions;
            auto result = std::make_shared<std::vector<T>>(*values);
            for(
                auto&& subscription = subscriptions.begin();
                subscription != subscriptions.end();
                subscription++){

                subscription->second.on_next(result);
            }
        }
    };

    template<typename T>
    class CombineLatestSubject : public ObservableSubjectBase<CombineLatestValues<T>>{
        public:
        CombineLatestSubject(const std::vector<observable<T>>& _observables) :
            ObservableSubjectBase<CombineLatestValues<T>>(
                std::make_shared<CombineLatestContext<T>>(
                    _observables)) {}
    };

    /**
     * Given an array of observables of the same type, construct an array that
     * contains all of the latest values of the observables in the inner array.
     * It will return a shared_ptr to an array to avoid unecessary copying of
     * the original array.
     */
    template<typename T>
    rx::observable<CombineLatestValues<T>> combineLatest(std::vector<rx::observable<T>>& oss){

        return rx::create<CombineLatestValues<T>>(
            std::function<void(rx::subscriber<CombineLatestValues<T>>& subscriber)>(
                [ctx = CombineLatestSubject(oss)]
                (rx::subscriber<CombineLatestValues<T>>& subscriber){

                    subscriber.add(
                        ctx.observable().subscribe(
                            [subscriber](CombineLatestValues<T> value){ subscriber.on_next(value); }));
            }));
    }

    /**
     * Combine all observables in the given vector into a single
     * sequential observable.
     * 
     * Todo: optimize the loop
     */
    template<typename T>
    const rx::observable<T> merge(std::vector<rx::observable<T>> oss){
        if(oss.size() < 1){
            return rx::empty<T>();
        }

        auto initial = oss[0];

        for(size_t i = 1; i < oss.size(); i++){
            initial = initial | rx::merge(oss[i]);
        }

        return initial;
    }
}