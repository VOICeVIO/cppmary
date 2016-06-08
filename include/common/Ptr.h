//
// the code in this file is borrow from opencv
// Created by sooda on 16/6/8.
//


#ifndef CPPMARY_PTR_H
#define CPPMARY_PTR_H


#ifdef __cplusplus

/////// exchange-add operation for atomic operations on reference counters ///////
#if defined __INTEL_COMPILER && !(defined WIN32 || defined _WIN32)   // atomic increment on the linux version of the Intel(tm) compiler
#define XADD(addr,delta) _InterlockedExchangeAdd(const_cast<void*>(reinterpret_cast<volatile void*>(addr)), delta)
#elif defined __GNUC__

#if defined __clang__ && __clang_major__ >= 3 && !defined __ANDROID__ && !defined __EMSCRIPTEN__  && !defined(__CUDACC__)
#ifdef __ATOMIC_SEQ_CST
#define XADD(addr, delta) __c11_atomic_fetch_add((_Atomic(int)*)(addr), (delta), __ATOMIC_SEQ_CST)
#else
#define XADD(addr, delta) __atomic_fetch_add((_Atomic(int)*)(addr), (delta), 5)
#endif
#elif __GNUC__*10 + __GNUC_MINOR__ >= 42

#if !(defined WIN32 || defined _WIN32) && (defined __i486__ || defined __i586__ || \
        defined __i686__ || defined __MMX__ || defined __SSE__  || defined __ppc__) || \
        (defined __GNUC__ && defined _STLPORT_MAJOR) || \
        defined __EMSCRIPTEN__

      #define XADD __sync_fetch_and_add
    #else
      #include <ext/atomicity.h>
      #define XADD __gnu_cxx::__exchange_and_add
    #endif

  #else
    #include <bits/atomicity.h>
    #if __GNUC__*10 + __GNUC_MINOR__ >= 34
      #define XADD __gnu_cxx::__exchange_and_add
    #else
      #define XADD __exchange_and_add
    #endif
#endif

#else
  static inline int XADD(int* addr, int delta)
  { int tmp = *addr; *addr += delta; return tmp; }
#endif

namespace cppmary {
    //opencv2/core/core.hpp
    template<typename _Tp> class Ptr
    {
    public:
        //! empty constructor
        Ptr();
        //! take ownership of the pointer. The associated reference counter is allocated and set to 1
        Ptr(_Tp* _obj);
        //! calls release()
        ~Ptr();
        //! copy constructor. Copies the members and calls addref()
        Ptr(const Ptr& ptr);
        template<typename _Tp2> Ptr(const Ptr<_Tp2>& ptr);
        //! copy operator. Calls ptr.addref() and release() before copying the members
        Ptr& operator = (const Ptr& ptr);
        //! increments the reference counter
        void addref();
        //! decrements the reference counter. If it reaches 0, delete_obj() is called
        void release();
        //! deletes the object. Override if needed
        void delete_obj();
        //! returns true iff obj==NULL
        bool empty() const;

        //! cast pointer to another type
        template<typename _Tp2> Ptr<_Tp2> ptr();
        template<typename _Tp2> const Ptr<_Tp2> ptr() const;

        //! helper operators making "Ptr<T> ptr" use very similar to "T* ptr".
        _Tp* operator -> ();
        const _Tp* operator -> () const;

        operator _Tp* ();
        operator const _Tp*() const;

        _Tp* obj; //< the object pointer.
        int* refcount; //< the associated reference counter
    };


    //include/opencv2/core/operations.hpp
    template<typename _Tp> inline Ptr<_Tp>::Ptr() : obj(0), refcount(0) {}
    template<typename _Tp> inline Ptr<_Tp>::Ptr(_Tp* _obj) : obj(_obj)
    {
        if(obj)
        {
            refcount = (int*)malloc(sizeof(*refcount));
            *refcount = 1;
        }
        else
            refcount = 0;
    }

    template<typename _Tp> inline void Ptr<_Tp>::addref()
    { if( refcount ) XADD(refcount, 1); }

    template<typename _Tp> inline void Ptr<_Tp>::release()
    {
        if( refcount && XADD(refcount, -1) == 1 )
        {
            delete_obj();
            free(refcount);
        }
        refcount = 0;
        obj = 0;
    }

    template<typename _Tp> inline void Ptr<_Tp>::delete_obj()
    {
        if( obj ) delete obj;
    }

    template<typename _Tp> inline Ptr<_Tp>::~Ptr() { release(); }

    template<typename _Tp> inline Ptr<_Tp>::Ptr(const Ptr<_Tp>& _ptr)
    {
        obj = _ptr.obj;
        refcount = _ptr.refcount;
        addref();
    }

    template<typename _Tp> inline Ptr<_Tp>& Ptr<_Tp>::operator = (const Ptr<_Tp>& _ptr)
    {
        if (this != &_ptr)
        {
            int* _refcount = _ptr.refcount;
            if( _refcount )
                XADD(_refcount, 1);
            release();
            obj = _ptr.obj;
            refcount = _refcount;
        }
        return *this;
    }

    template<typename _Tp> inline _Tp* Ptr<_Tp>::operator -> () { return obj; }
    template<typename _Tp> inline const _Tp* Ptr<_Tp>::operator -> () const { return obj; }

    template<typename _Tp> inline Ptr<_Tp>::operator _Tp* () { return obj; }
    template<typename _Tp> inline Ptr<_Tp>::operator const _Tp*() const { return obj; }

    template<typename _Tp> inline bool Ptr<_Tp>::empty() const { return obj == 0; }

    template<typename _Tp> template<typename _Tp2> Ptr<_Tp>::Ptr(const Ptr<_Tp2>& p)
        : obj(0), refcount(0)
    {
        if (p.empty())
            return;

        _Tp* p_casted = dynamic_cast<_Tp*>(p.obj);
        if (!p_casted)
            return;

        obj = p_casted;
        refcount = p.refcount;
        addref();
    }

    template<typename _Tp> template<typename _Tp2> inline Ptr<_Tp2> Ptr<_Tp>::ptr()
    {
        Ptr<_Tp2> p;
        if( !obj )
            return p;

        _Tp2* obj_casted = dynamic_cast<_Tp2*>(obj);
        if (!obj_casted)
            return p;

        if( refcount )
            XADD(refcount, 1);

        p.obj = obj_casted;
        p.refcount = refcount;
        return p;
    }

    template<typename _Tp> template<typename _Tp2> inline const Ptr<_Tp2> Ptr<_Tp>::ptr() const
    {
        Ptr<_Tp2> p;
        if( !obj )
            return p;

        _Tp2* obj_casted = dynamic_cast<_Tp2*>(obj);
        if (!obj_casted)
            return p;

        if( refcount )
            XADD(refcount, 1);

        p.obj = obj_casted;
        p.refcount = refcount;
        return p;
    }

//// specializied implementations of Ptr::delete_obj() for classic OpenCV types
//    template<> CV_EXPORTS void Ptr<CvMat>::delete_obj();
//    template<> CV_EXPORTS void Ptr<IplImage>::delete_obj();
//    template<> CV_EXPORTS void Ptr<CvMatND>::delete_obj();
//    template<> CV_EXPORTS void Ptr<CvSparseMat>::delete_obj();
//    template<> CV_EXPORTS void Ptr<CvMemStorage>::delete_obj();
//    template<> CV_EXPORTS void Ptr<CvFileStorage>::delete_obj();
}

#endif // __cplusplus


#endif //CPPMARY_PTR_H
