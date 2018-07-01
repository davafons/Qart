#pragma once

#include <vector>

#include "screen.hpp"

template <class T>
class Quadtree
{
    public:
        Quadtree(const T & data = T(), int level = 0);
        
        T data() const { return data_; }

        void clear();

        void insert(const T & data);

        Quadtree<T> * findHighest();

        virtual void splitAndRenderChilds(Screen & screen);

    private:
        T data_;
        int level_;

        std::vector<Quadtree<T> > leafs_;
};


template <class T>
Quadtree<T>::Quadtree(const T & data, int level) :
    data_(data),
    level_(level)
{
}


template <class T>
void Quadtree<T>::clear()
{
    leafs_.clear();
}


template <class T>
void Quadtree<T>::insert(const T & data)
{
    data_ = data;
}


template <class T>
Quadtree<T> * Quadtree<T>::findHighest()
{
    if(leafs_.empty())
        return this;

    Quadtree * highest_qtree = nullptr;

    for(auto & leaf : leafs_)
    {
        Quadtree * temp_qtree = leaf.findHighest();

        if(temp_qtree != nullptr && highest_qtree < temp_qtree)
            highest_qtree = temp_qtree;
    }

    return highest_qtree;
}



