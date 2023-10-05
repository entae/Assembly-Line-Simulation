#ifndef SDDS_ORDEREDCOLLECTION_H
#define SDDS_ORDEREDCOLLECTION_H

#include "Collection.h"

namespace sdds {
    template <typename T>
    class OrderedCollection : public Collection<T, 72> {
    public:
        OrderedCollection() : Collection<T, 72>() {};
        OrderedCollection(const OrderedCollection &OC) = delete;
        ~OrderedCollection() = default;

        bool operator+=(const T& item) {
            bool added = false;
            if (this->size() < this->capacity()) {
                this->incrSize();

                if (item > this->getLargestItem()) {
                    this->operator[](this->size() - 1) = item;
                    this->setLargestItem(item);
                } else {
                    unsigned int targetIndex = 0;
                    bool target = false;
                    for (unsigned i = 0; i < this->size() && !target; i++) {
                        if (this->operator[](i) > item) {
                            targetIndex = i;
                            target = true;
                        }
                    }
                    for (unsigned i = (this->size() - 1); i > targetIndex; i--) {
                        this->operator[](i) = this->operator[](i - 1);
                    }
                    this->operator[](targetIndex) = item;
                }
                this->setSmallestItem(item);
                added = true;
            }
            return added;
        }
    };
}

#endif // SDDS_ORDEREDCOLLECTION_H
