#pragma once

#include <netdb.h>
#include <cstddef>
#include <iterator>

class AddrInfoIterator
{
public:
    using self = AddrInfoIterator;
    using difference_type = std::ptrdiff_t;
    using value_type = struct addrinfo;

    AddrInfoIterator(value_type* pointer): current{pointer} {};
    AddrInfoIterator(const AddrInfoIterator& iterator): current{iterator.current} {};
    AddrInfoIterator(): current{nullptr} {};

    value_type operator*() const {
        return *current;
    };
 
    self& operator++() {
        current = current->ai_next;
        return *this;
    };
 
    self operator++(int)
    {
        auto tmp = *this;
        ++*this;
        return tmp;
    }
    bool operator==(const self& other) const{
        return other.current == current;
    };
    bool operator!=(const self& other) const{
        return other.current != current;
    };

private:
    value_type* current;
};

static_assert(std::input_iterator<AddrInfoIterator>);


struct AddrInfoAdapter : public addrinfo {
    AddrInfoIterator begin() { return AddrInfoIterator(this); }
    AddrInfoIterator end()   { return AddrInfoIterator(nullptr); }
};


