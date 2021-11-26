#ifndef __REFBASE_H___
#define __REFBASE_H___

#include <atomic>
#include <stddef.h>

template <typename T>
class lightBase {
    private:
        std::atomic<std::uint64_t> m_nCount;
    protected:
        ~lightBase() {}
    public:
        lightBase() : m_nCount(0) {}
        void incStrong() { m_nCount++; std::cout << "m_nCount = " << m_nCount << std::endl; }
        void decStrong() { if (--m_nCount == 0) delete static_cast<const T *>(this); } // TODO
        std::uint16_t getCount() { return m_nCount; }
};

template <typename T>
class sp {
    private:
        T *m_ptr;
    public:
        sp() : m_ptr(nullptr) {}
        sp(T *other) : m_ptr(other) { if (other) other->incStrong(); }
        sp(const sp<T>& other) : m_ptr(other.m_ptr) { other.m_ptr->incStrong(); }

        ~sp() { std::cout << "~sp()" << std::endl; if (m_ptr) m_ptr->decStrong(); m_ptr = nullptr; }

        void operator= (T* other) { if (other) { m_ptr = other; other->incStrong(); } }
        void operator= (nullptr_t __p) { if(m_ptr) m_ptr->decStrong(); m_ptr = __p; }
        T& operator* () const { return *m_ptr; }
        T* operator-> () const { return m_ptr; }
        T* get() const { return m_ptr; }
};

#endif
