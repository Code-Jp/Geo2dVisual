#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <string>
#include <vector>

namespace Geo2Util {
    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef K::Point_2 Point_2;
    typedef K::Segment_2 Segment_2;
    typedef K::Circle_2 Circle_2;
    typedef K::Triangle_2 Triangle_2;
    typedef K::Iso_rectangle_2 Iso_rectangle_2;

    struct Color {
        short r;
        short g;
        short b;
        short trans = 255;
    };
    const Color OpaqueBlack = {0, 0, 0, 255};
    
    enum class BoundaryType : short {
        Solid = 0,
        Dotted = 1,
        Dashed = 2
    };

    // Core Data:
    // point: Point_2(x, y)
    // segment: source() point, target() point
    // circle: center() point, squared_radius
    // triangle: p:point[0], q:point[1], r:point[2]
    // rectangle: low left point:min(), upper right point:max()
    // polygon: a list of points:vector<Point_2> (assuming)

    // Wrapper classes for visulization: "KernelObject_Visual"
    // Only Allow to manipulate visual properties (color and boundary type)
    // Core properties (coordinates of vertices, squared_raduis, etc.) are Read_Only
        // ctor: Only accept core data or its related wrapper classes
        // m_boundaryColor operations
        // m_interiorColor operations
        // m_bType operations
        // Retriece core data 
        // Optional: KernelObject() -- return a plain CGAL kernel object of the same type
        // ~~toString() -- Object serialization~~ (Deprecated; use toString(KernelObject_Visual) instead for unify toString API)

// Wrapper classes for visualization
    class Point_2_Visual {
    private:
        Color m_boundaryColor;
        Color m_interiorColor;
        BoundaryType m_bType;

        Point_2 m_p;
    public:
        // Constructors
        Point_2_Visual(const Point_2& p);
        Point_2_Visual(const Point_2& p, const Color& boudaryColor, const Color& interiorColor, const BoundaryType& btype);

        // Visual manipulation
        void setBondaryColor(const Color& color);
        Color getBondaryColor() const;
        void setInteriorColor(const Color& color);
        Color getInteriorColor() const;
        void setBoundaryType(const BoundaryType& btype);
        BoundaryType getBoundaryType() const;

        // Return CGAL Kernel object
        Point_2 KernelObject() const;

        // Return core data
        K::FT x() const;
        K::FT y() const;
    };

    class Segment_2_Visual {
    private:
        Color m_boundaryColor;
        BoundaryType m_bType;

        Point_2_Visual m_source;
        Point_2_Visual m_target;
    public:
        // Constructors
        Segment_2_Visual(const Point_2_Visual& s, const Point_2_Visual& t);
        Segment_2_Visual(const Point_2_Visual& s, const Point_2_Visual& t, const Color& boudaryColor, const BoundaryType& btype);

        // Visual manipulation
        void setBondaryColor(const Color& color);
        Color getBondaryColor() const;
        void setBoundaryType(const BoundaryType& btype);
        BoundaryType getBoundaryType() const;

        // Return CGAL Kernel object
        Segment_2 KernelObject() const;

        // Return core data 
        Point_2_Visual source() const;
        Point_2_Visual target() const;
    };

    class Circle_2_Visual {
    private:
        Color m_boundaryColor;
        Color m_interiorColor;
        BoundaryType m_bType;

        Point_2_Visual m_center;
        K::FT m_squaredRadius;
    public:
        // Constructors
        Circle_2_Visual(const Point_2_Visual& center, K::FT squared_radius);
        Circle_2_Visual(const Point_2_Visual& center, K::FT squared_radius, const Color& boudaryColor, const Color& interiorColor, const BoundaryType& btype);

        // Visual manipulation
        void setBondaryColor(const Color& color);
        Color getBondaryColor() const;
        void setInteriorColor(const Color& color);
        Color getInteriorColor() const;
        void setBoundaryType(const BoundaryType& btype);
        BoundaryType getBoundaryType() const;

        // Return CGAL Kernel object
        Circle_2 KernelObject() const;

        // Return core data
        Point_2_Visual center() const;
        K::FT squared_radius() const;
    };

    class Triangle_2_Visual {
    private:
        Color m_boundaryColor;
        Color m_interiorColor;
        BoundaryType m_bType;

        std::vector<Point_2_Visual> m_vertices; // will be initialized with size of 3
    public:
        // Constructors
        Triangle_2_Visual(const Point_2_Visual& p, const Point_2_Visual& q, const Point_2_Visual& r);
        Triangle_2_Visual(const Point_2_Visual& p, const Point_2_Visual& q, const Point_2_Visual& r, const Color& boudaryColor, const Color& interiorColor, const BoundaryType& btype);

        // Visual manipulation
        void setBondaryColor(const Color& color);
        Color getBondaryColor() const;
        void setInteriorColor(const Color& color);
        Color getInteriorColor() const;
        void setBoundaryType(const BoundaryType& btype);
        BoundaryType getBoundaryType() const;

        // Return CGAL Kernel object
        Triangle_2 KernelObject() const;

        // Return core data
        Point_2_Visual vertex(int i) const;
    };

    class Iso_rectangle_2_Visual {
    private:
        Color m_boundaryColor;
        Color m_interiorColor;
        BoundaryType m_bType;

        Point_2_Visual m_lowerLeft;
        Point_2_Visual m_upperRight;
    public:
        // Constructors
        Iso_rectangle_2_Visual(const Point_2_Visual& p, const Point_2_Visual& q);
        Iso_rectangle_2_Visual(const Point_2_Visual& p, const Point_2_Visual& q, const Color& boudaryColor, const Color& interiorColor, const BoundaryType& btype);

        // Visual manipulation
        void setBondaryColor(const Color& color);
        Color getBondaryColor() const;
        void setInteriorColor(const Color& color);
        Color getInteriorColor() const;
        void setBoundaryType(const BoundaryType& btype);
        BoundaryType getBoundaryType() const;

        // Return CGAL Kernel object
        Iso_rectangle_2 KernelObject() const;

        // Return core data
        Point_2_Visual min() const;
        Point_2_Visual max() const;
    };
// EOF Wrapper classes for visualization

    std::string toString(const Color& color);
    std::string toString(const BoundaryType& bt);

// Default toString
    std::string toString(const Point_2& p);
    std::string toString(const Segment_2& seg);
    std::string toString(const Circle_2& circ);
    std::string toString(const Triangle_2& tri);
    std::string toString(const Iso_rectangle_2& rect);
// EOF Default toString

// Customized toString
    std::string toString(const Point_2_Visual& pv);
    std::string toString(const Segment_2_Visual& segv);
    std::string toString(const Circle_2_Visual& circv);
    std::string toString(const Triangle_2_Visual& triv);
    std::string toString(const Iso_rectangle_2_Visual& rectv);
// EOF Customized toString
    void printToFile(const std::string& filename, const std::vector<std::string>& geo2_Objects);
} // namespace Geo2Util