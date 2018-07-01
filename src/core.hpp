#pragma once

#include <iostream>
#include <set>

#include "screen.hpp"
#include "surface.hpp"
#include "rect.hpp"
#include "quadtree.hpp"


class Core
{
    public:
        Core(const char * title, int width, int height);
        ~Core();

        void execute();

    private:
        enum class State { PAUSED, RUNNING, RESET };
        State currentState_;

        Screen mainScreen_;
        Surface image_;

        int iterations_;

        //using Data_Type = std::set<Rect>;
        using Data_Type = Quadtree<Rect>;
        Data_Type rectangles_;


        void splitAndRenderChilds(Quadtree<Rect> & quadtree);
        void splitAndRenderChilds(std::set<Rect> & rectangles);

        void handleInput();
        
        void start();
        void reset();
};