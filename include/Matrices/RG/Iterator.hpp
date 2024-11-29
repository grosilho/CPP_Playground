#pragma once

#include <stdafx.hpp>

namespace LinAlg::Matrices::RG::_implementation_details
{

    template <typename T>
    class Iterator
    {
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using reference = T&;

        Iterator() = default;
        Iterator(T* data)
            : m_data(data) { };

        bool operator==(const Iterator& other) const { return m_data == other.m_data; }
        T& operator*() const { return *m_data; }
        Iterator& operator++()
        {
            ++m_data;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp(*this);
            ++*this;
            return tmp;
        }
        Iterator& operator--()
        {
            --m_data;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator tmp(*this);
            --*this;
            return tmp;
        }
        Iterator& operator+=(difference_type n)
        {
            m_data += n;
            return *this;
        }
        Iterator operator+(difference_type n) const
        {
            Iterator tmp(*this);
            return tmp += n;
        }
        friend Iterator<T> operator+(std::ptrdiff_t n, const Iterator<T>& it) { return it + n; }
        Iterator& operator-=(difference_type n)
        {
            m_data -= n;
            return *this;
        }
        Iterator operator-(difference_type n) const
        {
            Iterator tmp(*this);
            return tmp -= n;
        }
        difference_type operator-(const Iterator& other) const { return m_data - other.m_data; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
        bool operator<=(const Iterator& other) const { return m_data <= other.m_data; }
        bool operator>(const Iterator& other) const { return !(*this <= other); }
        bool operator>=(const Iterator& other) const { return (*this > other) || (*this == other); }
        bool operator<(const Iterator& other) const { return !(*this >= other); }

        reference operator[](difference_type n) const { return *(m_data + n); }

      private:
        T* m_data { nullptr };
    };

    static_assert(std::output_iterator<Iterator<int>, int>);
    static_assert(std::random_access_iterator<Iterator<int>>);
}
