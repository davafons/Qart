#include "core.hpp"

Core::Core(const char * title, int width, int height) :
    currentState_(State::PAUSED),
    mainScreen_(Screen(title, width, height)),
    image_(),
    iterations_(0),
    rectangles_()
{
}


Core::~Core()
{
    IMG_Quit();
    SDL_Quit();
}


void Core::execute()
{
    while(!mainScreen_.isClosed())
    {
        handleInput();

        if(currentState_ == State::RUNNING && !rectangles_.empty())
        {
            ++iterations_;
            splitAndRenderChilds();
            mainScreen_.setWindowTitle("Qart - Iterations: " + std::to_string(iterations_) + 
                                        ". Rects: " + std::to_string((iterations_ * 3) + 1));
        }
        else
            currentState_ = State::PAUSED;
    }
}



void Core::splitAndRenderChilds()
{
    // The std::set is ordered from lower to higher, so the last element will be the one with the highest error
    std::set<Rect>::const_iterator highestErrorRect = std::prev(rectangles_.end());
    
    float sub_width = (float)highestErrorRect->w() / 2;
    float sub_height = (float)highestErrorRect->h() / 2;

    for(int y = 0; y < 2; ++y)
    {
        for(int x = 0; x < 2; ++x)
        {
            if(sub_width > 1 && sub_height > 1) // This line prevents division-by-zero errors
            {
                Rect child_rect(image_, highestErrorRect->x() + (sub_width * x),
                                        highestErrorRect->y() + (sub_height * y),
                                        sub_width + 0.5f,
                                        sub_height + 0.5f);

                child_rect.render(mainScreen_.renderer());
                rectangles_.insert(child_rect);
            }
        }
    }

    rectangles_.erase(highestErrorRect);
}


void Core::handleInput()
{
 SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
            mainScreen_.close();

        else if(e.type == SDL_DROPFILE)
        {
            image_.load(e.drop.file);

            reset();
            start();
        }

        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    mainScreen_.close();
                    break;

                case SDLK_d: // Show borders
                    if(Rect::show_borders()) Rect::show_borders() = false;
                    else Rect::show_borders() = true;

                case SDLK_r: // Reset
                    reset();
                    start();
                    break;
                                        
                case SDLK_s: // Resume-Pause
                    if(currentState_ == State::RUNNING)
                        currentState_ = State::PAUSED;
                    else
                        currentState_ = State::RUNNING;
                    break;
            }
        }
    }
}


void Core::start()
{
    rectangles_.emplace(image_, 0, 0, image_.width(), image_.height());
    currentState_ = State::RUNNING;
}


void Core::reset()
{
    mainScreen_.setWindowSize(image_.width(), image_.height());
    rectangles_.clear();
    mainScreen_.clear();
    iterations_ = 0;
}