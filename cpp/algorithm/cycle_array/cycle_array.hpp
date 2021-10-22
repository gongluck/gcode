/*
 * @Author: gongluck
 * @Date: 2021-10-22 14:19:12
 * @Last Modified by: gongluck
 * @Last Modified time: 2021-10-22 14:50:12
 */

#ifndef __CYCLE_ARRAY__HPP__
#define __CYCLE_ARRAY__HPP__

#include <array>

namespace galgorithm
{
    template <class T, size_t size_>
    class cyclearray_iterator
    {
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        typedef size_t size_type;
        typedef cyclearray_iterator self_type;

    private:
        pointer start_;   //内存物理起始
        size_type first_; //内存逻辑起始
        size_type cur_;   //从first_偏移
        size_type len_;   //内存逻辑长度

    public:
        cyclearray_iterator(pointer start, size_type first, size_type cur, size_type len)
            : start_(start), first_(first), cur_(cur), len_(len)
        {
        }

        reference operator*()
        {
            return start_[(first_ + cur_) % size_];
        }
        self_type &operator++()
        {
            ++cur_;
            return *this;
        }
        bool operator==(const self_type other) const
        {
            return this->start_ == other.start_ &&
                   this->first_ == other.first_ &&
                   this->cur_ == other.cur_ &&
                   this->len_ == other.len_;
        }
        bool operator!=(const self_type ohter) const
        {
            return !(*this == ohter);
        }
    };

    template <class T, size_t size_>
    class cycle_array : public std::array<T, size_>
    {
    public:
        typedef size_t size_type;
        typedef cyclearray_iterator<T, size_> iterator;
        typedef std::array<T, size_> base;

    private:
        size_type first_ = 0;
        size_type len_ = 0;

    public:
        iterator begin()
        {
            return iterator(&base::operator[](0), first_, 0, len_);
        }

        iterator end()
        {
            return iterator(&base::operator[](0), first_, len_, len_);
        }

        size_t size()
        {
            return len_;
        }

        bool push(const T &v)
        {
            if (len_ >= size_)
            {
                return false;
            }
            else
            {
                base::operator[]((first_ + len_++) % size_) = v;
                return true;
            }
        }

        bool push(const T *vl, size_t len)
        {
            if (len + len_ > size_)
            {
                return false;
            }
            else
            {
                std::copy(vl, vl + len, end());
                len_ += len;
                return true;
            }
        }

        bool pop(T &v)
        {
            if (len_ <= 0)
            {
                return false;
            }
            else
            {
                v = base::operator[]((first_++) % size_);
                first_ %= size_;
                --len_;
                return true;
            }
        }

        bool pop(T *vl, size_t len)
        {
            if (len > size_)
            {
                return false;
            }
            else
            {
                std::copy_n(begin(), len, vl);
                first_ += len;
                first_ %= size_;
                len_ -= len;
                return true;
            }
        }
    };
} // galgorithm
#endif //__CYCLE_ARRAY__HPP__