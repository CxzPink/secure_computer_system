#include "../inc/point.h"

cxz::Point::Point()
{
    x=0;
    y=0;
}

cxz::Point::Point(const int &xx,const int &yy)
{
    x=xx;
    y=yy;
}

bool cxz::operator == (const Point &p1,const Point &p2)
{
    if(p1.x==p2.x && p1.y==p2.y)
        return 1;
    return 0;
}