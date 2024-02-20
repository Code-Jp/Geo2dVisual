
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "geo2_util.h"

using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Circle_2 Circle_2;
typedef K::Iso_rectangle_2 Iso_rectangle_2;
typedef K::Triangle_2 Triangle_2;
typedef K::Segment_2 Segment_2;


int main()
{
    // Point_2 p0(12, -15), p1(-10, -25.3), p2(-0.01, 0.2);

    // Point_2 s1(10, 10), s2(40, 40);
    // Segment_2 seg(s1, s2);

    // Point_2 p(10, 10), q(20, 15), s(10, 15);
    // Triangle_2 tri(p, q, s);

    // Circle_2 circ(p, 4);

    // Iso_rectangle_2 rect(p, q);


    // std::vector<std::string> geomObjectArray;
    // geomObjectArray.reserve(7); // only for observation purpose in this case; can be deleted

    // geomObjectArray.push_back(Geo2Util::toString(p0));
    // geomObjectArray.push_back(Geo2Util::toString(p1));
    // geomObjectArray.push_back(Geo2Util::toString(p2));
    // geomObjectArray.push_back(Geo2Util::toString(seg));

    // //geomObjectArray[0] = Geo2Util::toString(p0);
    // //geomObjectArray[1] = Geo2Util::toString(p1);
    // //geomObjectArray[2] = Geo2Util::toString(p2);
    // //geomObjectArray[3] = Geo2Util::toString(seg); 
    // //geomObjectArray[4] = Geo2Util::toString(s1);
    // //geomObjectArray[5] = Geo2Util::toString(s2);

    // geomObjectArray.push_back(Geo2Util::toString(circ));

    // //geomObjectArray[6] = Geo2Util::toString(circ);
    // //geomObjectArray[7] = Geo2Util::toString(p);

    // geomObjectArray.push_back(Geo2Util::toString(tri));

    // //geomObjectArray[8] = Geo2Util::toString(tri);
    // //geomObjectArray[9] = Geo2Util::toString(p);
    // //geomObjectArray[10] = Geo2Util::toString(q);
    // //geomObjectArray[11] = Geo2Util::toString(s);

    // geomObjectArray.push_back(Geo2Util::toString(rect));

    // //geomObjectArray[12] = Geo2Util::toString(rect);
    // //geomObjectArray[13] = Geo2Util::toString(p);
    // //geomObjectArray[14] = Geo2Util::toString(q);
  
   
    // Geo2Util::printToFile("test.txt", geomObjectArray);
    cout << Geo2Util::OpaqueBlack.r << "\n"
            << Geo2Util::OpaqueBlack.g << "\n"
            << Geo2Util::OpaqueBlack.b << "\n"
            << Geo2Util::OpaqueBlack.trans << "\n";
}
