/***************************************************************************
* Copyright (c) 2016, Sylvain Corlay and Johan Mabille                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include "xtl/xiterator_base.hpp"

namespace adl
{
    class iterator_test : public xtl::xrandom_access_iterator_base<iterator_test, int, int>
    {

    public:

        using self_type = iterator_test;
        using base_type = xtl::xrandom_access_iterator_base<self_type, int, int>;
        using value_type = typename base_type::value_type;
        using reference = typename base_type::reference;
        using pointer = typename base_type::pointer;
        using difference_type = typename base_type::difference_type;

        inline iterator_test() : m_value(0) {}

        inline self_type& operator++()
        {
            ++m_value;
            return *this;
        }

        inline self_type& operator--()
        {
            --m_value;
            return *this;
        }

        inline self_type& operator+=(difference_type n)
        {
            m_value += n;
            return *this;
        }

        inline self_type& operator-=(difference_type n)
        {
            m_value -= n;
            return *this;
        }

        inline reference operator*() const
        {
            return m_value;
        }

        inline pointer operator->() const
        {
            return &m_value;
        }

        mutable value_type m_value;
    };

    inline int operator-(const iterator_test& lhs, const iterator_test& rhs)
    {
        return *lhs - *rhs;
    }

    inline bool operator==(const iterator_test& lhs, const iterator_test& rhs)
    {
        return lhs.m_value == rhs.m_value;
    }

    inline bool operator<(const iterator_test& lhs, const iterator_test& rhs)
    {
        return lhs.m_value < rhs.m_value;
    }
}

namespace xtl
{
    using iterator = adl::iterator_test;
    
    TEST(xiterator_base, increment)
    {
        iterator it;
        ++it;
        EXPECT_EQ(1, *it);
        it++;
        EXPECT_EQ(2, *it);
    }

    TEST(xiterator_base, decrement)
    {
        iterator it;
        --it;
        EXPECT_EQ(-1, *it);
        it--;
        EXPECT_EQ(-2, *it);
    }

    TEST(xiterator_base, plus_assign)
    {
        iterator it;
        ++it;
        it += 5;
        EXPECT_EQ(6, *it);
    }

    TEST(xiterator_base, minus_assign)
    {
        iterator it;
        ++it;
        it -= 5;
        EXPECT_EQ(-4, *it);
    }

    TEST(xiterator_base, plus)
    {
        iterator it;
        ++it;
        iterator it2 = it + 4;
        EXPECT_EQ(5, *it2);

        iterator it3 = 5 + it;
        EXPECT_EQ(6, *it3);
    }

    TEST(xiterator_base, minus)
    {
        iterator it;
        ++it;
        iterator it2 = it - 5;
        EXPECT_EQ(-4, *it2);

        int diff = it - it2;
        EXPECT_EQ(5, diff);
    }

    TEST(xiterator_base, comparison)
    {
        iterator it;
        iterator it2(it);
        ++it;

        EXPECT_TRUE(it == it);
        EXPECT_TRUE(it != it2);
        EXPECT_TRUE(it2 <= it);
        EXPECT_TRUE(it2 < it);
        EXPECT_TRUE(it >= it2);
        EXPECT_TRUE(it > it2);
    }
}

