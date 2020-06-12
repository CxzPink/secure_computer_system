/*************************************************************************\
  All the code was completed by June 1, 2020

  The author(CHEN Xingzhou) may be contacted via:

  EMail:               3170101630@zju.edu.cn

  Phone:               18888921302
\**************************************************************************/
#ifndef _CXZ_POINT_H_
#define _CXZ_POINT_H_

namespace cxz
{
    // finite field points
    struct Point
    {
        int x;
        int y;
        Point();
        Point(const int &xx,const int &yy);
    };
    bool operator == (const Point &p1,const Point &p2);
}

#endif