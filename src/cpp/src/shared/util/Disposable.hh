#pragma once

namespace rx::space::util{

    /**
     * Utility class that simply calls the provided
     * function when it gets destroyed.
     */
    template<typename F>
    class Disposable{
        public:
        Disposable(F&& _dispose): dispose(_dispose), hasBeenDisposed(false) {}

        void runDispose(){

            // todo: make thread safe
            if(!hasBeenDisposed){
                hasBeenDisposed = true;
                dispose();
            }
        }

        ~Disposable(){ runDispose(); }

        private:
        const F dispose;
        bool hasBeenDisposed;
    };

    template<typename T>
    Disposable<T> disposable(T&& result){
        return Disposable<T>(std::forward<T>(result));
    }
}