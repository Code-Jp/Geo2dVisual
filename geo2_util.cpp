#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "geo2_util.h"

namespace Geo2Util {

    /**
     * @brief Convert BoundaryType to string
     * @param t Boundary Type
     * @return A string object containing the representation of BoundaryType
     */
    std::string toString(const BoundaryType& bt) {
        switch (bt) {
            case BoundaryType::Solid : return "0";
            case BoundaryType::Dotted : return "1";
            case BoundaryType::Dashed : return "2";
            default: return "N/A";
        }
    }

    /**
     * @brief Convert color to string in a form of "r, g, b, trans"
     * @param color Color object (r, b, g, trans)
     * @return A string object containing the representation of Color 
     */
    std::string toString(const Color& color)
    {
    return std::to_string(color.r) + " "
                + std::to_string(color.g) + " "
                + std::to_string(color.b) + " "
                + std::to_string(color.trans);
    }

    void printToFile(const std::string& filename, const std::vector<std::string>& geo2_Objects) {

        std::ofstream output(filename);
        output << std::fixed << std::setprecision(10);
        for (int i = 0; i < geo2_Objects.size(); i++) {
            output << geo2_Objects[i] << std::endl;
        }
        output.close();
    }

// Default toString: toString(CGAL::Kernel::Object)
// Default color = Color::OpaqueBlack = Color{0, 0, 0, 255}; default boundary type = BoundaryType::Solid
    /**
     * @brief Convert Point_2 object to string with its x and y coordinate
     * @param p Point_2 object
     * @return A string object containing the representation of Point_2 object
     */
    std::string toString(const Point_2& p) {

        std::ostringstream s;
        s << std::fixed << std::setprecision(10) << "POINT " << p.x() << " " 
            << p.y() << " "
            << toString(Geo2Util::OpaqueBlack) << " "
            << toString(BoundaryType::Solid) << " " 
            << toString(Geo2Util::OpaqueBlack);

        return s.str();
    }

    /**
     * @brief Convert Segment_2 object to string with its source point and target point
     * @param seg Segment_2 object
     * @return A string object containing the representation of Segment_2 object
     */
    std::string toString(const Segment_2& seg) {

        return "LINE_SEGMENT " + toString(Geo2Util::OpaqueBlack) + " " 
                + toString(BoundaryType::Solid) + "\n"
                + toString(seg.source()) + "\n"
                + toString(seg.target());
    }

    /**
     * @brief Convert Circle_2 object to string with its center point and radius
     * @param circ Circle_2 object
     * @return A string object containing the representation of Circle_2 object
     */
    std::string toString(const Circle_2& circ) {
        double raduis = std::sqrt(circ.squared_radius());

        std::ostringstream c;
        c << std::fixed << std::setprecision(10) << "CIRCLE " << raduis << " " 
            << toString(Geo2Util::OpaqueBlack) << " "
            << toString(BoundaryType::Solid) << " "
            << toString(Geo2Util::OpaqueBlack) + "\n"
            << toString(circ.center());

        return c.str();
    }

    /**
     * @brief Convert Triangle_2 object to string with its three vertices
     * @param tri Triangle_2 object
     * @return A string object containing the representation of Triangle_2 object
     */
    std::string toString(const Triangle_2& tri) {

        return "TRIANGLE " + toString(Geo2Util::OpaqueBlack) + " " 
                + toString(BoundaryType::Solid) + " " 
                + toString(Geo2Util::OpaqueBlack) + "\n"
                + toString(tri[0]) + "\n"
                + toString(tri[1]) + "\n"
                + toString(tri[2]);
    }

    /**
     * @brief Convert Iso_rectangle_2 object to string with its diagonal opposite vertices
     * @param rect Iso_rectangle_2 object
     * @return A string object containing the representation of Iso_rectangle_2 object
     */
    std::string toString(const Iso_rectangle_2& rect) {

        return "RECTANGLE " + toString(Geo2Util::OpaqueBlack) + " "
                + toString(BoundaryType::Solid) + " "
                + toString(Geo2Util::OpaqueBlack) + "\n"
                + toString(rect.min()) + "\n"
                + toString(rect.max());
    }

// Customized toString: toString(KernelObject_Visual)
    std::string toString(const Point_2_Visual& pv) {
        std::ostringstream s;
        s << std::fixed << std::setprecision(10) << "POINT " << pv.x() << " " 
            << pv.y() << " "
            << toString(pv.getBondaryColor()) << " " 
            << toString(pv.getBoundaryType()) << " "
            << toString(pv.getInteriorColor());

        return s.str();
    }

    std::string toString(const Segment_2_Visual& segv) {

        return "LINE_SEGMENT " + toString(segv.getBondaryColor()) + " " 
                + toString(segv.getBoundaryType()) + "\n"
                + toString(segv.source()) + "\n"
                + toString(segv.target());
    }

    std::string toString(const Circle_2_Visual& circv) {
        double raduis = std::sqrt(circv.squared_radius());

        std::ostringstream c;
        c << std::fixed << std::setprecision(10) << "CIRCLE " << raduis << " " 
            << toString(circv.getBondaryColor()) << " "
            << toString(circv.getBoundaryType()) << " "
            << toString(circv.getInteriorColor()) + "\n"
            << toString(circv.center());

        return c.str();
    }

    std::string toString(const Triangle_2_Visual& triv) {

        return "TRIANGLE " + toString(triv.getBondaryColor()) + " " 
                + toString(triv.getBoundaryType()) + " " 
                + toString(triv.getInteriorColor()) + "\n"
                + toString(triv[0]) + "\n"
                + toString(triv[1]) + "\n"
                + toString(triv[2]);
    }
    
// Visual Wrapper Classes:
// Point_2_Visual
    Point_2_Visual::Point_2_Visual(const Point_2& p)
        : m_p(p.x(), p.y())
            , m_boundaryColor{OpaqueBlack}
            , m_interiorColor{OpaqueBlack}
            , m_bType {BoundaryType::Solid} {
    }

    Point_2_Visual::Point_2_Visual(const Point_2& p, const Color& boudaryColor, const Color& interiorColor, const BoundaryType& btype) 
        : m_p(p.x(), p.y())
            , m_boundaryColor{boudaryColor}
            , m_interiorColor{interiorColor}
            , m_bType {btype} {
    }

    void Point_2_Visual::setBondaryColor(const Color& color) {
        m_boundaryColor = color;
    }

    Color Point_2_Visual::getBondaryColor() const {
        return m_boundaryColor;
    }

    void Point_2_Visual::setInteriorColor(const Color& color) {
        m_interiorColor = color;
    }

    Color Point_2_Visual::getInteriorColor() const {
        return m_interiorColor;
    }

    void Point_2_Visual::setBoundaryType(const BoundaryType& btype) {
        m_bType = btype;
    }

    BoundaryType Point_2_Visual::getBoundaryType() const {
        return m_bType;
    }

    Point_2 Point_2_Visual::KernelObject() const {
        return Point_2(m_p.x(), m_p.y());
    }

    K::FT Point_2_Visual::x() const {
        return m_p.x();
    }

    K::FT Point_2_Visual::y() const {
        return m_p.y();
    }

// Segment_2_Visual
    Segment_2_Visual::Segment_2_Visual(const Point_2_Visual& s, const Point_2_Visual& t)
        : m_source(s)
            , m_target(t)
            , m_boundaryColor{OpaqueBlack}
            , m_bType {BoundaryType::Solid} {
    }

    Segment_2_Visual::Segment_2_Visual(const Point_2_Visual& s, const Point_2_Visual& t, const Color& boudaryColor, const BoundaryType& btype)
        : m_source(s)
            , m_target(t)
            , m_boundaryColor{boudaryColor}
            , m_bType{btype} {
    }

    void Segment_2_Visual::setBondaryColor(const Color& color) {
        m_boundaryColor = color;
    }

    Color Segment_2_Visual::getBondaryColor() const {
        return m_boundaryColor;
    }

    void Segment_2_Visual::setBoundaryType(const BoundaryType& btype) {
        m_bType = btype;
    }

    BoundaryType Segment_2_Visual::getBoundaryType() const {
        return m_bType;
    }

    Segment_2 Segment_2_Visual::KernelObject() const {
        return Segment_2(m_source.KernelObject(), m_target.KernelObject());
    }

    Point_2_Visual Segment_2_Visual::source() const {
        return m_source;
    }
    Point_2_Visual Segment_2_Visual::target() const {
        return m_target;
    }

// Circle_2_Visual
    Circle_2_Visual::Circle_2_Visual(const Point_2_Visual& center, K::FT squared_radius)
        : m_center(center)
            , m_squaredRadius{squared_radius}
            , m_boundaryColor{OpaqueBlack}
            , m_interiorColor{OpaqueBlack}
            , m_bType{BoundaryType::Solid} {
    }

    Circle_2_Visual::Circle_2_Visual(const Point_2_Visual& center, K::FT squared_radius, const Color& boundaryColor, const Color& interiorColor, const BoundaryType& btype)
        : m_center(center)
            , m_squaredRadius{squared_radius}
            , m_boundaryColor{boundaryColor}
            , m_interiorColor{interiorColor}
            , m_bType{btype} {
    }

    void Circle_2_Visual::setBondaryColor(const Color& color) {
        m_boundaryColor = color;
    }

    Color Circle_2_Visual::getBondaryColor() const {
        return m_boundaryColor;
    }

    void Circle_2_Visual::setInteriorColor(const Color& color) {
        m_interiorColor = color;
    }

    Color Circle_2_Visual::getInteriorColor() const {
        return m_interiorColor;
    }

    void Circle_2_Visual::setBoundaryType(const BoundaryType& btype) {
        m_bType = btype;
    }

    BoundaryType Circle_2_Visual::getBoundaryType() const {
        return m_bType;
    }

    Circle_2 Circle_2_Visual::KernelObject() const {
        return Circle_2(m_center.KernelObject(), m_squaredRadius);
    }

    Point_2_Visual Circle_2_Visual::center() const {
        return m_center;
    }

    K::FT Circle_2_Visual::squared_radius() const {
        return m_squaredRadius;
    }

// Triangle_2_Visual
    Triangle_2_Visual::Triangle_2_Visual(const Point_2_Visual& p, const Point_2_Visual& q, const Point_2_Visual& r) 
        : m_boundaryColor{OpaqueBlack}
            , m_interiorColor{OpaqueBlack}
            , m_bType{BoundaryType::Solid} {
        m_vertices.reserve(3);
        m_vertices.emplace_back(Point_2_Visual(p));
        m_vertices.emplace_back(Point_2_Visual(q));
        m_vertices.emplace_back(Point_2_Visual(r));
    }

    Triangle_2_Visual::Triangle_2_Visual(const Point_2_Visual& p, const Point_2_Visual& q, const Point_2_Visual& r, const Color& boudaryColor, const Color& interiorColor, const BoundaryType& btype) 
        : m_boundaryColor{boudaryColor}
            , m_interiorColor{interiorColor}
            , m_bType{btype} {
        m_vertices.reserve(3);
        m_vertices.emplace_back(Point_2_Visual(p));
        m_vertices.emplace_back(Point_2_Visual(q));
        m_vertices.emplace_back(Point_2_Visual(r));
    }

    void Triangle_2_Visual::setBondaryColor(const Color& color) {
        m_boundaryColor = color;
    }

    Color Triangle_2_Visual::getBondaryColor() const {
        return m_boundaryColor;
    }

    void Triangle_2_Visual::setInteriorColor(const Color& color) {
        m_interiorColor = color;
    }

    Color Triangle_2_Visual::getInteriorColor() const {
        return m_interiorColor;
    }

    void Triangle_2_Visual::setBoundaryType(const BoundaryType& btype) {
        m_bType = btype;
    }

    BoundaryType Triangle_2_Visual::getBoundaryType() const {
        return m_bType;
    }

    Triangle_2 Triangle_2_Visual::KernelObject() const {
        return Triangle_2(m_vertices[0].KernelObject(), m_vertices[1].KernelObject(), m_vertices[2].KernelObject());
    }

    Point_2_Visual Triangle_2_Visual::vertex(int i) const {
        if(i < 0) {
            return m_vertices[3 + i%3];
        }
        return m_vertices[i%3];
    }
} // namespace Geo2Util
