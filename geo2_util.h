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

    namespace {
        struct Color {
            short r;
            short g;
            short b;
            short trans;
        };
        const Color OpaqueBlack = {0, 0, 0, 255};
        std::string toString(const Color& color);
        
        enum class BoundaryType : short {
            Solid = 0,
            Dotted = 1,
            Dashed = 2
        };
    }

    // Core Data:
    // point: x, y
    // segment: source point, target point
    // circle: center point, squared_radius
    // triangle: p:point[0], q:point[1], r:point[2]
    // rectangle: low left point:min(), upper right point:max()
    // polygon: a list of points:vector<Point_2> (assuming)

    // Wrapper classes for visulization: "KernelObject_Visual"
    // Only Allow to manipulate visual properties (color and boundary type)
    // Core properties (coordinates of vertices, squared_raduis, etc.) are Read_Only
        // ctor: Only accept object of its Kernel type
        // m_boundaryColor operations
        // m_interiorColor operations
        // m_bType operations
        // Retriece core data 
        // Optional: KernelObject() -- return a plain CGAL kernel object of the same type
        
    class Point_2_Visual {
    private:
        Color m_boundaryColor;
        Color m_interiorColor;
        BoundaryType m_bType;

        Point_2 m_p;
    public:
        // Constructors
        Point_2_Visual (const Point_2& p);
        Point_2_Visual (const Point_2& p, const Color& boudaryColor, const Color& interiorColor, const BoundaryType& btype);

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

        std::string toString(const Point_2_Visual& p_visual) const;
    };

    class Segment_2_Visual {
    private:
        Color m_boundaryColor;
        BoundaryType m_bType;

        Point_2_Visual m_source;
        Point_2_Visual m_target;
    public:
        // Constructors
        Segment_2_Visual (const Segment_2& seg);
        Segment_2_Visual (const Segment_2& seg, const Color& boudaryColor, const BoundaryType& btype);

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

        std::string toString(const Segment_2_Visual& seg_visual) const;
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
        Circle_2_Visual (const Circle_2& p);
        Circle_2_Visual (const Circle_2& p, const Color& boudaryColor, const Color& interiorColor, const BoundaryType& btype);

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

        std::string toString(const Circle_2_Visual& circ_visual) const;
    };

    class Triangle_2_Visual {
    private:
        Color m_boundaryColor;
        Color m_interiorColor;
        BoundaryType m_bType;

        std::vector<Point_2_Visual> m_vertices; // will be initialized with size of 3
    public:
        // Constructors
        Triangle_2_Visual (const Triangle_2& p);
        Triangle_2_Visual (const Triangle_2& p, const Color& boudaryColor, const Color& interiorColor, const BoundaryType& btype);

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

        std::string toString(const Triangle_2_Visual& tri_visual) const;
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
        Iso_rectangle_2_Visual (const Iso_rectangle_2& p);
        Iso_rectangle_2_Visual (const Iso_rectangle_2& p, const Color& boudaryColor, const Color& interiorColor, const BoundaryType& btype);

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

        std::string toString(const Iso_rectangle_2_Visual& rect_visual) const;
    };
    // EOF Wrapper classes for visualization

    // original version of toString
    std::string toString(const BoundaryType& t);

    std::string toString(const Point_2& p);
    std::string toString(const Segment_2& seg);
    std::string toString(const Circle_2& circ);
    std::string toString(const Triangle_2& tri);
    std::string toString(const Iso_rectangle_2& rect);
    // EOF original version of toString
    void printToFile(const std::string& filename, const std::vector<std::string>& geo2_Objects);
}