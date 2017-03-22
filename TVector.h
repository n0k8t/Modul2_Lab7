#ifndef MODUL2_LAB7_TVECTOR_H
#define MODUL2_LAB7_TVECTOR_H

#include <iostream>

template<typename T>
class TVector
{
public:
    using value_type = int;
    using size_type = size_t;
    using iterator = value_type *;
    using reference = value_type&;
    using const_reference = const value_type&;


private:
    value_type * Ptr;
    size_type Count;
    size_type InternalCapacity;
public:
    TVector()
            : Ptr(nullptr)
            , Count(0)
            , InternalCapacity(0)
    { }

    TVector(size_type capacity)
            : Count(0)
            , InternalCapacity(capacity)
    {
        Ptr = new value_type[InternalCapacity];
    }

    ~TVector()
    {
        delete[] Ptr;
    }

    bool empty() const throw()
    {
        return size() == 0;
    }

    size_type size() const throw()
    {
        return Count;
    }

    size_type capacity() const throw()
    {
        return InternalCapacity;
    }

    iterator begin() const throw()
    {
        return Ptr;
    }

    iterator end() const throw()
    {
        return Ptr + Count;
    }


    // impl start
    void reserve(size_type size)
    {
        if (size < InternalCapacity)
        {
            return;
        }

        value_type * ptr = new value_type[size];
        if(Ptr != nullptr)
        {
            memcpy(ptr, Ptr, Count * sizeof(value_type));
            delete[] Ptr;
        }
        Ptr = ptr;
        InternalCapacity = size;

    }

    TVector(const TVector& rhs)
    {
        this->reserve(rhs.InternalCapacity);
        memcpy(Ptr, rhs.Ptr, rhs.Count * sizeof(size_type));
    }

    TVector& operator=(const TVector& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        this->reserve(rhs.InternalCapacity);
        memcpy(Ptr, rhs.Ptr, rhs.Count * sizeof(size_type));
        Count = rhs.Count;

        return *this;
    }

    void push_back(const value_type& value)
    {
        if(InternalCapacity == 0)
            this->reserve(16);

        if(InternalCapacity <= Count)
            this->reserve(InternalCapacity * 2);

        Ptr[Count] = value;
        Count++;
    }

    reference at(size_type index)
    {
        if (index < 0 || index >= Count)
        {
            throw std::out_of_range("Out of range");
        }

        return Ptr[index];
    }

    value_type at(size_type index) const
    {
        if (index < 0 || index >= Count)
        {
            throw std::out_of_range("Out of range");
        }

        return Ptr[index];
    }

    reference operator[](size_type index)
    {
        return Ptr[index];
    }

    const_reference operator[](size_type index) const
    {
        return Ptr[index];
    }

    reference front()
    {
        if (Ptr == nullptr)
        {
            throw std::out_of_range("Out of range");
        }

        return Ptr[0];
    }

    const_reference front() const
    {
        if (Ptr == nullptr)
        {
            throw std::out_of_range("Out of range");
        }

        return Ptr[0];
    }

    reference back()
    {
        if (Ptr == nullptr)
        {
            throw std::out_of_range("Out of range");
        }

        return Ptr[Count - 1];
    }

    const_reference back() const
    {
        if (Ptr == nullptr)
        {
            throw std::out_of_range("Out of range");
        }

        return Ptr[Count - 1];
    }

    void clear()
    {
        delete[] Ptr;
        Count = 0;
        InternalCapacity = 0;
    }

    void pop_back()
    {
        if(Count == 0)
        {
            throw std::out_of_range("Out of range");
        }

        Count--;
    }

    void swap(TVector& other) throw()
    {
        std::swap(Ptr, other.Ptr);
        std::swap(Count, other.Count);
        std::swap(InternalCapacity, other.InternalCapacity);
    }

    void resize(size_type count, value_type value = value_type())
    {
        size_type k = Count;
        Count = count;
        if (count > InternalCapacity)
            this->reserve(count);

        for (k; k < Count; k++)
            Ptr[k] = value;
    }

    iterator insert(iterator pos, const value_type& value)
    {
        if ( pos > Ptr + Count)
        {
            throw std::out_of_range("Out of Range");
        }

        Count++;
        if(InternalCapacity < Count)
            this->reserve(InternalCapacity * 2);


        for (size_type k = Count - 1; k >= *pos; k--)
        {
            Ptr[k] = Ptr[k - 1];
        }
        Ptr[*pos - 1] = value;

        return pos;
    }

    void insert(iterator pos, size_type count, const value_type& value)
    {
        if ( pos > Ptr + Count)
        {
            throw std::out_of_range("Out of Range");
        }

        Count += count;

        if(InternalCapacity < Count)
            this->reserve(InternalCapacity * 2);

        for (size_type k = Count - 1; k >= pos - Ptr + count - 1; k--)
        {
            Ptr[k] = Ptr[k - count];
        }
        for (size_t k = 0; k < count; k++)
        {
            Ptr[pos - Ptr + k] = value;
        }
    }

    iterator erase(iterator pos)
    {
        if (pos >= Ptr + Count)
        {
            throw std::out_of_range("Out of range");
        }

        for (size_type i = 0; pos + i < Ptr + Count - 1; i++)
        {
            *(pos + i) = *(pos + i + 1);
        }
        Count--;

        return pos;
    }

    iterator erase(iterator first, iterator last)
    {
        if (last >= Ptr + Count)
        {
            throw std::out_of_range("Out of range");
        }

        for (size_type i = 0; (last + i) < (Ptr + Count); i++)
        {
            *(first + i) = *(last + i);
        }
        Count -= (last - first);

        return first;
    }
    // impl finish
};

#endif //MODUL2_LAB7_TVECTOR_H
