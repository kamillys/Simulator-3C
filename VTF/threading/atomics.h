#pragma once

#include <VTF/Traits>
#include <boost/atomic.hpp>

namespace VTF {

class AtomicCounter
{
    NONCOPYABLE(AtomicCounter)

    mutable boost::atomic<int> m_counter;
public:
    AtomicCounter();
    int incrementAndGet() const;
    int decrementAndGet() const;
    int get() const;
};

}
