//
// Created by sooda on 16/6/30.
//
#include <cassert>
#include "common/ReferenceCounted.h"

namespace cppmary {
    ReferenceCounted::ReferenceCounted() :
        ReferenceCount_(new ReferenceCount())
    {
        // Hold a weak ref to self to avoid possible double delete of the ReferenceCount
        (ReferenceCount_->weakRefs_)++;
    }

    ReferenceCounted::~ReferenceCounted()
    {
        assert(ReferenceCount_);
        assert(ReferenceCount_->refs_ == 0);
        assert(ReferenceCount_->weakRefs_ > 0);

        // Mark object as expired, release the self weak ref and delete the ReferenceCount if no other weak refs exist
        ReferenceCount_->refs_ = -1;
        (ReferenceCount_->weakRefs_)--;
        if (!ReferenceCount_->weakRefs_)
            delete ReferenceCount_;

        ReferenceCount_ = 0;
    }

    void ReferenceCounted::AddRef()
    {
        //std::cout << ReferenceCount_->refs_ << std::endl;
        assert(ReferenceCount_->refs_ >= 0);
        (ReferenceCount_->refs_)++;
    }

    void ReferenceCounted::ReleaseRef()
    {
        //std::cout << ReferenceCount_->refs_ << std::endl;
        assert(ReferenceCount_->refs_ > 0);
        (ReferenceCount_->refs_)--;
        if (!ReferenceCount_->refs_) {
            delete this;
        }
    }

    int ReferenceCounted::Refs() const
    {
        return ReferenceCount_->refs_;
    }

    int ReferenceCounted::WeakRefs() const
    {
        // Subtract one to not return the internally held reference
        return ReferenceCount_->weakRefs_ - 1;
    }

}
