#pragma once

#include <Matrices/CR/Concepts.hpp>
#include <Matrices/CR/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::CR
{
    namespace _implementation_details
    {
        template <Concepts::MatrixType T>
        auto subscript(const T& t, int i)
        {
            return t[i];
        }

        template <Concepts::ScalarType T>
        auto subscript(const T& t, int)
        {
            return t;
        }
    }

    template <typename T>
    class Coroutine
    {
      public:
        using Scalar = T;
        class promise_type;
        using handle_type = std::coroutine_handle<promise_type>;

        class promise_type
        {
          public:
            T m_value {};

            promise_type() = default;

            Coroutine get_return_object() { return Coroutine(handle_type::from_promise(*this)); } // creates the user-facing object
            std::suspend_always initial_suspend() { return {}; }                                  // defines if the coroutine starts immediately or not
            void return_void() { }                                                                // method called when co_return is called witout arguments. Use return_value() for returning a value.
            void unhandled_exception() { }                                                        // defines what to do when to coroutine throws an exception which is not catched within the coroutine
            std::suspend_never final_suspend() noexcept
            {
                return {};
            } // when the coroutine is done, this method is called and puts the routine in a suspended state. Control is returned to the caller.
            std::suspend_always yield_value(T value) // return a value from the coroutine. This method is called by co_yield val, which is equivalent to co_await promise.yield_value(val). Therefore
                                                     // the return value of yield_value must be convertible to an awaiter or an await_transform function taking this type must be available.
            {
                m_value = value; // the compiler will not take care of passing the value to the caller. We need to store it in the promise object and take care of that.
                return {};
            }
        };

        // The handle is a pointer. Therefore we define the move constructor and move assignment operator to handle the ownership of the handle and delete the (shallow) copy constructor and copy
        // assignment operator.
        Coroutine(Coroutine&& other) noexcept
            : m_handle(other.m_handle)
        {
            other.m_handle = nullptr;
        }
        Coroutine& operator=(Coroutine&& other) noexcept
        {
            if (m_handle)
                m_handle.destroy();
            m_handle = other.m_handle;
            other.m_handle = nullptr;
            return *this;
        }
        ~Coroutine() // destroy the coroutine hendle, hence the coroutine, when the object is destroyed. Since shallow copy of Coroutine is forbidded, there is no need to check if the
                     // handle is already destroyed by a copy of this object.
        {
            if (m_handle)
                m_handle.destroy();
        }

        void resume() { m_handle.resume(); }
        T current_value() { return m_handle.promise().m_value; }
        T next_value()
        {
            if (!m_handle.done())
                resume();
            return current_value();
        }
        // T operator[](int i) const { return next_value(); }

        template <typename Callable, typename... Args>
        static Coroutine from_fun_args(int rows, int cols, Callable&& callable, Args&&... args)
        {
            using _implementation_details::subscript;

            auto coroutine = []<typename Fun, typename... Matrices>(int l_rows, int l_cols, Fun&& fun, Matrices&&... mats) -> Coroutine
            {
                for (int i = 0; i < l_rows * l_cols; ++i)
                    co_yield fun(subscript(mats, i)...);
            }(rows, cols, std::forward<Callable>(callable), std::forward<Args>(args)...);

            return coroutine;
        }

      private:
        handle_type m_handle;
        Coroutine(handle_type handle)
            : m_handle(handle)
        {
        }
        Coroutine(Coroutine const&) = delete;
        Coroutine& operator=(Coroutine const&) = delete;
        T& operator[](int i) = delete;
    };
}
