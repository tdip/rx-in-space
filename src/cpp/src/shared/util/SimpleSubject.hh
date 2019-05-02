#pragma once

#include <unordered_map>
#include <memory>

#include "rx.hh"

namespace rx::space::util{

    template<typename T>
    struct SimpleSubjectContext{
        long id;
        std::unordered_map<long, rx::subscriber<T>> subscribers;
    };

    /**
     * Simple class that exposes an observable that subscribers can
     * subscribe to and a method to publish values to observables.
     */
    template<typename T>
    class SimpleSubject{

        typedef std::shared_ptr<SimpleSubjectContext<T>> ContextPtr;
        typedef std::weak_ptr<SimpleSubjectContext<T>> ContextWPtr;

        public:
        SimpleSubject() :
            context(std::make_shared<SimpleSubjectContext<T>>()),
            wContext(context),
            source(
                rx::create<T>(
                    [wContext = wContext](rx::subscriber<T>& subs){
                        SimpleSubject<T>::onSubscribe(wContext, subs);
                    })) {}

        const rx::observable<T>& observable() const { return source; }

        void onNext(T value) const{
            onNextContext(context, value);
        }

        rx::composite_subscription subscribeTo(const rx::observable<T>& os) const{
            return os.subscribe(
                [context = this.context]
                (T value){
                    onNextContext(context, value);
                });
        }

        private:
        const ContextPtr context;
        const ContextWPtr wContext;
        const rx::observable<T> source;

        static void onNextContext(ContextPtr& context, T value) const{
            for(
                auto&& subscriber = context->subscribers.begin();
                subscriber != context->subscribers.end();
                subscriber++){

                subscriber->second.on_next(value);
            }
        }

        static void onSubscribe(ContextWPtr wContext, rx::subscriber<T>& subscriber){
            ContextPtr context = wContext.lock();
            if(!context){
                return;
            }

            const long id = context->id;
            context->subscribers.emplace(id, subscriber);

            subscriber.add(
                [id, wContext](){
                    ContextPtr context = wContext.lock();
                    if(context){
                        context->subscribers.erase(id);
                    }
                });
        }
    };
}