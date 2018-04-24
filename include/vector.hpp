#ifndef GATOOLS_VECTOR_HPP
#define GATOOLS_VECTOR_HPP

#include <initializer_list>

#include <cstring> // memmove, memcpy
#include <algorithm> // std::copy
#include <utility> // std::move, std::forward, std::exchange

namespace gatools
{
    typedef unsigned int size_type;
    static const size_type DEFAULT_CAPACITY = 1;

    template <typename T>
    class vector
    {
    private:
        T* mData;
        size_type mLength;
        size_type mCapacity;

    public:
        /* Constructors */

        /** Default constructor */
        vector()
            : mLength(0)
            , mCapacity(DEFAULT_CAPACITY)
        {
            mData = new T[mCapacity];
        }

        /** Copy constructor
         * @param aOther Vector to copy
         */
        vector(const vector<T>& aOther)
            : mCapacity(aOther.mCapacity)
            , mLength(aOther.mLength)
        {
            mData = new T[mCapacity];

            for (size_type i = 0; i < mLength; ++i) {
                mData[i] = aOther.mData[i];
            }
        }

        /** Move constructor
         * @param aOther Vector to move
         */
        vector(vector<T>&& aOther)
            : mCapacity(aOther.mCapacity)
            , mLength(aOther.mLength)
            , mData(aOther.mData)
        {
            /* Fallback after move */
            aOther.mCapacity = DEFAULT_CAPACITY;
            aOther.mLength = 0;
            aOther.mData = new T[aOther.mCapacity];
        }

        /** Constructs with count copies of elements with value value.
         * @param aCount Values count
         * @param aValue Value
         */
        vector(size_type aCount, const T& aValue)
            : mCapacity(aCount)
            , mLength(aCount)
        {
            mData = new T[mCapacity];

            for (size_type i = 0; i < mLength; ++i) {
                mData[i] = aValue;
            }
        }

        /* Brace-enclosed initializer list constructor
         * @param aInit Initialize list
         */
        vector(std::initializer_list<T> aInit)
            : mCapacity(aInit.size())
            , mLength(aInit.size())
        {
            mData = new T[mCapacity];

            std::copy(aInit.begin(), aInit.end(), mData);
        }

        /* Destructor */
        ~vector()
        {
            delete [] mData;
        }

        /* Operators */

        /** Copy operator
         * @param aOther Other vector to copy
         */
        vector& operator = (const vector& aOther)
        {
            if (this != &aOther) { // self-assignment check expected
                delete[] mData;
                mCapacity = aOther.mCapacity;
                mLength = aOther.mLength;

                for (size_type i = 0; i < mLength; ++i) {
                    mData[i] = aOther.mData[i];
                }
            }

            return *this;
        }

        /** Move operator
         * @param aOther Other vector to move
         */
        vector& operator = (vector&& aOther)
        {
            if(this != &aOther) { // no-op on self-move-assignment
                delete[] mData;
                mCapacity = aOther.mCapacity;
                mLength = aOther.mLength;

                mData = aOther.mData;

                /* Fallback after move */
                aOther.mCapacity = DEFAULT_CAPACITY;
                aOther.mLength = 0;
                aOther.mData = new T[aOther.mCapacity];
            }

            return *this;
        }

        /** Modify element by index
         * @param aIndex Index
         */
        T& operator [] (size_type aIndex)
        {
            return mData[aIndex];
        }

        /** Get value by index
         * @param aIndex Index
         */
        const T& operator [] (size_type aIndex) const
        {
            return mData[aIndex];
        }

        /* Methods */

        /** Reserve memory for data
         * @param aCapacity Size to reserve
         */
        void reserve(size_type aCapacity)
        {
            if (aCapacity > mCapacity) {
                T*const oldData = mData;

                mCapacity = aCapacity;
                mData = new T[mCapacity];

                memcpy(mData, oldData, sizeof(T) * mLength);

                delete [] oldData;
            }
        }

        /** Get vector capacity */
        size_type capacity() const
        {
            return mCapacity;
        }

        /** Get vector size */
        size_type size() const
        {
            return mLength;
        }

        /** Check if vector is empty */
        bool empty() const
        {
            return mLength == 0;
        }

        /** Clear vector */
        void clear()
        {
            //memset(0, mData);
            mLength = 0;
        }

        /** Insert value at position
         * @param aPosition Index position to insert
         * @param aValue Value to insert
         */
        void insert(size_type aPosition, const T& aValue)
        {
            if (aPosition >= mLength) { /* Push back if index more then vector length */
                push_back(aValue);
            } else if (mLength < mCapacity) { /* Check if capacity available */
                for (size_type i = mLength; i >= aPosition; --i) {
                    mData[i] = mData[i - 1];
                }
                mData[aPosition] = aValue;
                ++mLength;
            } else { /* Increase capacity */
                reserve(mCapacity * 2);
                insert(aPosition, aValue);
            }
        }

        /** Push value at the end of vector
         * @param aValue Value to push at the end
         */
        void push_back(const T& aValue)
        {
            if (mLength < mCapacity) { /* Check if capacity available */
                mData[mLength] = aValue;
                ++mLength;
            } else { /* Increase capacity */
                reserve(mCapacity * 2);
                push_back(aValue);
            }
        }

        /** Move value at the end of vector
         * @param aValue Value to push at the end
         */
        void push_back(T&& aValue)
        {
            if (mLength < mCapacity) { /* Check if capacity available */
                mData[mLength] = aValue;
                ++mLength;
            } else { /* Increase capacity */
                reserve(mCapacity * 2);
                push_back(std::move(aValue));
            }
        }

        /** Remove last vector value */
        void pop_back()
        {
            if (mLength > 0) {
                --mLength;
            }
        }


        /** Modify element by index
         * @param aIndex Index
         */
        T& at(size_type aPosition)
        {
            return mData[aPosition];
        }

        /** Get value by index
         * @param aIndex Index
         */
        const T& at(size_type aPosition) const
        {
            return mData[aPosition];
        }

        /** Modify first element */
        T& front()
        {
            return mData[0];
        }

        /** Get first element */
        const T& front() const
        {
            return mData[0];
        }

        /** Modify last element */
        T& back()
        {
            return mData[mLength - 1];
        }

        /** Get last element */
        const T& back() const
        {
            return mData[mLength - 1];
        }

        /** Access internal data */
        T* data()
        {
            return mData;
        }

        /** Get internal data */
        const T* data() const
        {
            return mData;
        }
    }; /* end of vector class */
} /* end of gatools namespace */

#endif /* GATOOLS_VECTOR_HPP */
