#pragma once
#include <Matrices/RG/Iterator.hpp>
#include <stdafx.hpp>

namespace LinAlg::Matrices::RG::_implementation_details
{
    template <typename T>
    class Container;

    template <typename T>
    void swap(Container<T>& first, Container<T>& second) noexcept;

    template <typename T>
    class Container
    {
      public:
        using value_type = T;
        using iterator = Iterator<T>;
        using const_iterator = Iterator<const T>;

        Container(int size = 0);
        Container(const Container& other);
        Container(Container&& other) noexcept;
        ~Container() { delete[] m_data; }

        Container& operator=(Container other) noexcept;

        friend void swap<T>(Container<T>& first, Container<T>& second);

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        T& operator[](int index) { return m_data[index]; }
        T operator[](int index) const { return m_data[index]; }

        int size() const;

      private:
        int m_size;
        T* m_data { nullptr };
    };

    template <typename T>
    Container<T>::Container(int size)
        : m_size(size)
        , m_data(size > 0 ? new T[size] : nullptr) {};

    template <typename T>
    Container<T>::Container(const Container& other)
        : m_size(other.m_size)
        , m_data(other.m_size > 0 ? new T[m_size] : nullptr)
    {
        if (m_data)
            std::copy_n(other.m_data, m_size, m_data);
    }

    template <typename T>
    void swap(Container<T>& first, Container<T>& second) noexcept
    {
        using std::swap;
        swap(first.m_size, second.m_size);
        swap(first.m_data, second.m_data);
    }

    template <typename T>
    Container<T>::Container(Container&& other) noexcept
        : Container(0)
    {
        swap(*this, other);
    }

    template <typename T>
    Container<T>& Container<T>::operator=(Container other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    template <typename T>
    Container<T>::iterator Container<T>::begin()
    {
        return iterator(m_data);
    }

    template <typename T>
    Container<T>::iterator Container<T>::end()
    {
        return iterator(m_data + m_size);
    }

    template <typename T>
    Container<T>::const_iterator Container<T>::begin() const
    {
        return const_iterator(m_data);
    }

    template <typename T>
    Container<T>::const_iterator Container<T>::end() const
    {
        return const_iterator(m_data + m_size);
    }

    template <typename T>
    int Container<T>::size() const
    {
        return m_size;
    }

    static_assert(std::ranges::sized_range<Container<int>>);
    static_assert(std::ranges::random_access_range<Container<int>>);
}
