#pragma once

#include <functional>
#include <memory>

#include "rx.hh"

#include "util/Disposable.hh"

#include <unordered_map>

namespace rx::space::util{

    using ObservableSubjectDispose = Disposable<std::function<void()>>;

    /**
     * The context of the ObservableSubjectBase is in a separate
     * class because subscribers need a reference to *this*. However,
     * if the subscriber outlives the object, segfaults can ocurr.
     * By placing the context in a separate class and providing the
     * subscribers to a weak reference to the context, they must
     * first check if the subject is still alive before accessing
     * it's fields. This prevents the segfaults.
     */
    template<typename T>
    class ObservableSubjectBaseContext{

        public:
        /**
         * Counter to generate unique identifiers to all
         * subscribers to this node entry.
         */
        long idCount;

        /**
         * The active subscribers to this subject
         */
        std::unordered_map<long, rx::subscriber<T>> subscriptions;

        /**
         * Pointer to the disposer. Once all references to the disposer
         * are discarded. It will be discarded and call the deactivate
         * handler.
         */
        std::weak_ptr<ObservableSubjectDispose> dispose;

        virtual void onActivate(){};
        virtual void onDeActivate(){};
    };

    /**
     * Class that exposes an observable. Additionally, it includes
     * custom handlers to perform actions when it becomes active
     * or inactive. Active means there is at least one subscriber
     * to the observable, inactive is the complement of being
     * active.
     */
    template<typename T>
    class ObservableSubjectBase{

    typedef std::shared_ptr<ObservableSubjectBaseContext<T>> ContextPtr;
    typedef std::weak_ptr<ObservableSubjectBaseContext<T>> ContextWPtr;

    public:
        ObservableSubjectBase(ContextPtr&& _context): context(std::move(_context)) {}

        ObservableSubjectBase(): context(std::make_shared<ObservableSubjectBaseContext<T>>()) {}

        virtual ~ObservableSubjectBase(){
            context->subscriptions.clear();
            auto wDispose = context->dispose.lock();

            if(wDispose){
                wDispose->runDispose();
            }
        }

        /**
         * Get an observable to view values of this subject. This observable
         * will participate in determining whether the subject is active or not.
         * Maning that subscribing/unsubscribing from it can potentially trigger
         * the call to the activate/deactivate functions.
         */
        rx::observable<T> observable() {
            ContextWPtr wContext = context;
            return rx::create<T>(
                std::function<void(rx::subscriber<T>&)>(
                    [wContext](rx::subscriber<T> &ss) mutable {

                        auto context = wContext.lock();
                        if(context){
                            onSubscribe(context, ss);
                        }
                    }));
        }

        /**
         * Get an observable of values from this subject. This observable
         * will not participate in determining if the subject is active or not.
         * Subscribing or un-subscribing from it will never trigger the
         * activate or deactivate function.
         */
        rx::observable<T> observableWeak() {
            ContextWPtr wContext = context;
            return rx::create<T>(
                std::function<void(rx::subscriber<T>&)>(
                    [wContext](rx::subscriber<T> &ss) mutable {
                        auto context = wContext.lock();
                        if(context){
                            onSubscribeWeak(context, ss);
                        }
                    }));
        }

        bool isActive() const { return !context->dispose.expired(); }

        /**
         * Emit a value into the observable.
         */
        void onNext(T value){
            auto& subscriptions = context->subscriptions;
            for(
                auto subscription = subscriptions.begin();
                subscription != subscriptions.end();
                subscription++){

                subscription->second.on_next(value);
            }
        }

    protected:
        ContextPtr context;
    private:
        static std::shared_ptr<ObservableSubjectDispose> getActiveDisposer(
            ContextPtr context){
        
            // Try get a copy of the dispose handler
            std::shared_ptr<ObservableSubjectDispose> disposeRef = context->dispose.lock();
            ContextWPtr wContext = context;

            // If the dispose handler returns null, it means the node is not
            // active. This will activate the node and create a dispose
            // handler.
            if(!disposeRef){
                disposeRef = std::make_shared<ObservableSubjectDispose>(
                    [wContext](){
                        auto context = wContext.lock();

                        if(context){
                            context->onDeActivate();
                        }
                    });

                // Store the dispose handler as a weak-ref, that way
                // it gets discarded when all subscribers get discarded.
                context->dispose = disposeRef;
                context->onActivate();
            }

            return disposeRef;
        }

        static void onSubscribe(
            ContextPtr context,
            rx::subscriber<T>& ss){
            ObservableSubjectBase<T>::onSubscribeBase(
                context,
                ObservableSubjectBase<T>::getActiveDisposer(context),
                ss);
        }

        static void onSubscribeWeak(
            ContextPtr context,
            rx::subscriber<T>& ss){
            ObservableSubjectBase<T>::onSubscribeBase(
                context,
                nullptr,
                ss);
        }

        /**
        * Function called when a subject subscribes to the node.
        */ 
        static void onSubscribeBase(
            ContextPtr context,
            std::shared_ptr<ObservableSubjectDispose> disposeRef,
            rx::subscriber<T>& ss){
        
            const long id = context->idCount++;
            ContextWPtr wContext;
            ss.add(
                std::function<void()>(
                    [id, disposeRef, wContext]() mutable {
                        auto context = wContext.lock();
                        if(context){
                            context->subscriptions.erase(id);
                        }
                        disposeRef.reset();
                }));

            context->subscriptions.emplace(id, std::move(ss));
        }
    };

    /**
     * Implementation of an observable subject that can
     * be used as a standalone object instead of requiring
     * inheritance.
     */
    template<typename T, typename A, typename D>
    class ObservableSubjectContext : public ObservableSubjectBaseContext<T>{

    public:
    ObservableSubjectContext(A&& _activate, D&& _deactivate) :
        ObservableSubjectBaseContext<T>(),
        activate(std::forward<A>(_activate)),
        deactivate(std::forward<D>(_deactivate)) {}

    protected:
    virtual void onActivate() override{
        activate();
    }

    virtual void onDeActivate() override{
        deactivate();
    }

    private:
        A activate;
        D deactivate;
    };

    template<typename T, typename A, typename D>
    class ObservableSubject : public ObservableSubjectBase<T>{
        public:
        ObservableSubject(A&& activate, D&& deactivate)
            : ObservableSubjectBase<T>(std::make_shared<ObservableSubjectContext<T,A,D>>(
                std::forward<A>(activate),
                std::forward<D>(deactivate))) {}
    };

    template<typename T, typename A, typename D>
    ObservableSubject<T, A, D> createSubject(A&& activate, D&& deactivate){
        return ObservableSubject<T,A,D>(
            std::forward<A>(activate),
            std::forward<D>(deactivate));
    }
}