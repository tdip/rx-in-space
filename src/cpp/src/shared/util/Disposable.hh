#pragma once

namespace rx::space::util{

    /**
     * Utility class that simply calls the provided
     * function when it gets destroyed.
     */
    template<typename F>
    class Disposable{
        public:
        Disposable(F&& _dispose): dispose(_dispose) {}
        ~Disposable(){ dispose(); }

        private:
        const F dispose;
    };

    template<typename T>
    Disposable<T> disposable(T&& result){
        return Disposable<T>(std::forward<T>(result));
    }
}