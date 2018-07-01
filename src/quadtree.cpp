#include "quadtree.hpp"

#include "rect.hpp"

template <>
void Quadtree<Rect>::splitAndRenderChilds(Screen & screen)
{
    float sub_width = (float)data_.w() / 2 + 0.5f;
    float sub_height = (float)data_.h() / 2 + 0.5f;

    for(int j = 0; j < 2; ++j)
    {
        for(int i = 0; i < 2; ++i)
        {
            if(sub_width > 1 && sub_height > 1)
            {
                Rect child_rect(data_.getSurface(), data_.x() + ((sub_width - 0.5f) * i),
                                        data_.y() + ((sub_height - 0.5f) * j),
                                        sub_width,
                                        sub_height);

                child_rect.render(screen.renderer());
                leafs_.push_back(Quadtree(child_rect, level_ + 1));
            }
        }
    }
}