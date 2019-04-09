#pragma once

#include <functional>
#include <memory>

#include "rx.hh"

#include "util/Disposable.hh"

#include <unordered_map>

namespace rx::space::util{

    using ObservableSubjectDispose = Disposable<std::function<void()>>;

    /**
     * Class that exposes an observable. Additionally, it includes
     * custom handlers to perform actions when it becomes active
     * or inactive. Active means there is at least one subscriber
     * to the observable, inactive is the complement of being
     * active.
     */
    template<typename T>
    class ObservableSubjectBase{

    public:
        ObservableSubjectBase() :
            subscribe([this](rx::subscriber<T> &ss) mutable { onSubscribe(ss); }),
            _observable(rx::create<T>(subscribe)) {};

        virtual ~ObservableSubjectBase(){
            subscriptions.clear();
            auto wDispose = dispose.lock();

            if(wDispose){
                wDispose->runDispose();
            }
        }

        const rx::observable<T>& observable() const { return _observable; }

        bool isActive() const { return !dispose.expired(); }

        /**
         * Emit a value into the observable.
         */
        void onNext(T& value){

            for(
                auto subscription = subscriptions.begin();
                subscription != subscriptions.end();
                subscription++){

                subscription->second.on_next(value);
            }
        }

    protected:

        virtual void onActivate(){};
        virtual void onDeActivate(){};

    private:
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
         * Lambda function that wraps around the 'onSubscribe' method to make
         * it easier to construct an observable with it.
         */
        const std::function<void(rx::subscriber<T>&)> subscribe;

        const rx::observable<T> _observable;

        /**
         * Pointer to the disposer. Once all references to the disposer
         * are discarded. It will be discarded and call the deactivate
         * handler.
         */
        std::weak_ptr<ObservableSubjectDispose> dispose;

        std::shared_ptr<ObservableSubjectDispose> getActiveDisposer(){
        
            // Try get a copy of the dispose handler
            std::shared_ptr<ObservableSubjectDispose> disposeRef = dispose.lock();

            // If the dispose handler returns null, it means the node is not
            // active. This will activate the node and create a dispose
            // handler.
            if(!disposeRef){
                disposeRef = std::make_shared<ObservableSubjectDispose>(
                    [this](){
                        onDeActivate();
                    });

                // Store the dispose handler as a weak-ref, that way
                // it gets discarded when all subscribers get discarded.
                dispose = disposeRef;
                onActivate();
            }

            return disposeRef;
        }

        /**
        * Function called when a subject subscribes to the node.
        */ 
        void onSubscribe(rx::subscriber<T>& ss){
        
            const long id = idCount++;
            auto disposeRef = getActiveDisposer();

            ss.add(
                std::function<void()>(
                    [id, disposeRef, this]() mutable {
                        printf("hahaha %d\n", subscriptions.size());
                        this->subscriptions.erase(id);
                        printf("hohohoh %d\n", subscriptions.size());
                        disposeRef.reset();
                }));

            subscriptions.emplace(id, std::move(ss));
        }
    };

    /**
     * Implementation of an observable subject that can
     * be used as a standalone object instead of requiring
     * inheritance.
     */
    template<typename T, typename A, typename D>
    class ObservableSubject : public ObservableSubjectBase<T>{

    public:
    ObservableSubject(A&& _activate, D&& _deactivate) :
        ObservableSubjectBase<T>(),
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
    ObservableSubject<T, A, D> createSubject(A&& activate, D&& deactivate){
        return ObservableSubject<T,A,D>(
            std::forward<A>(activate),
            std::forward<D>(deactivate));
    }
}