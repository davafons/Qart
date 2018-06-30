#include <iostream>
#include <set>

#include "screen.hpp"
#include "surface.hpp"
#include "rect.hpp"


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

        std::set<Rect> rectangles_;

        void splitAndRenderChilds();

        void handleInput();
        
        void start();
        void reset();
};