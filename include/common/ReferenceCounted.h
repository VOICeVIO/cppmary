//
// Created by sooda on 16/6/30.
//

#ifndef CPPMARY_REFERENCECOUNT_H
#define CPPMARY_REFERENCECOUNT_H

namespace cppmary {
    /// Reference count structure.
    struct ReferenceCount
    {
        /// Construct.
        ReferenceCount() :
            refs_(0),
            weakRefs_(0)
        {
        }

        /// Destruct.
        ~ReferenceCount()
        {
            // Set reference counts below zero to fire asserts if this object is still accessed
            refs_ = -1;
            weakRefs_ = -1;
        }

        /// Reference count. If below zero, the object has been destroyed.
        int refs_;
        /// Weak reference count.
        int weakRefs_;
    };

/// Base class for intrusively reference-counted objects. These are noncopyable and non-assignable.
    class ReferenceCounted {
    public:
        /// Construct. Allocate the reference count structure and set an initial self weak reference.
        ReferenceCounted();
        /// Destruct. Mark as expired and also delete the reference count structure if no outside weak references exist.
        virtual ~ReferenceCounted();

        /// Increment reference count. Can also be called outside of a SharedPtr for traditional reference counting.
        void AddRef();
        /// Decrement reference count and delete self if no more references. Can also be called outside of a SharedPtr for traditional reference counting.
        void ReleaseRef();
        /// Return reference count.
        int Refs() const;
        /// Return weak reference count.
        int WeakRefs() const;

        /// Return pointer to the reference count structure.
        ReferenceCount* ReferenceCountPtr() { return ReferenceCount_; }

    private:
        /// Prevent copy construction.
        ReferenceCounted(const ReferenceCounted& rhs);
        /// Prevent assignment.
        ReferenceCounted& operator =(const ReferenceCounted& rhs);

        /// Pointer to the reference count structure.
        ReferenceCount* ReferenceCount_;
    };
}


#endif //CPPMARY_REFERENCECOUNT_H
