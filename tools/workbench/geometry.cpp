/* A tool for collecting, visualizing and annotating 3D Interaction data
 *
 * Copyright (C) 2017-2019 University of Illinois at Chicago
 *
 * Author: Harish G. Naik <hnaik2@uic.edu>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "geometry.h"

#include <GL/glut.h>

namespace ipme::wb {
void Geometry::draw_circle(const core::Point3f& point, float radius,
                           const Color& color)
{
    static constexpr int iteration_count = 40;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(color.r, color.g, color.b, color.a);
    glVertex3f(point.x(), point.y(), point.z());

    for(int i = 0; i <= iteration_count; ++i) {
        const float x = radius * std::cos(i * two_pi / iteration_count);
        const float y = radius * std::sin(i * two_pi / iteration_count);
        glVertex3f(point.x() + x, point.y() + y, 0.f);
    }
    glEnd();
}

core::Polygon3f
Geometry::construct_circle_as_polygon(const core::Point3f& center, float radius)
{
    std::vector<core::Point3f> points;
    static constexpr int iteration_count = 40;
    for(int i = 0; i < iteration_count; ++i) {
        float angle = -1 * i * two_pi / iteration_count;
        const float x = center.x() + radius * std::cos(angle);
        const float y = center.y() + radius * std::sin(angle);
        points.push_back(core::Point3f{x, y, 0});
    }

    return core::construct_polygon(points);
}

void Geometry::draw_square(const core::Point3f& point, float side,
                           const Color& color)
{
    const float offset = side * .5f;

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POLYGON);
    glVertex3f(point.x() + offset, point.y() + offset, point.z());
    glVertex3f(point.x() + offset, point.y() - offset, point.z());
    glVertex3f(point.x() - offset, point.y() - offset, point.z());
    glVertex3f(point.x() - offset, point.y() + offset, point.z());
    glEnd();
}

void Geometry::draw_eq_triangle(const core::Point3f& /* point */,
                                float /* side */, const Color& /* color */)
{
}

void Geometry::draw_line(const core::Point3f& point, float length, float angle,
                         const Color& color)
{
    glBegin(GL_LINES);
    glColor3f(color.r, color.g, color.b);

    glVertex3f(point.x(), point.y(), point.z());
    glVertex3f(point.x() + (length * std::cos(angle)),
               point.y() + (length * std::sin(angle)), point.z());

    glEnd();
}

void Geometry::draw_segment(const core::Point3f& point, float length,
                            float angle, const Color& color)
{
    glBegin(GL_TRIANGLES);
    glColor4f(color.r, color.g, color.b, .1f);

    glVertex3f(point.x(), point.y(), point.z());

    const auto left_angle = angle - half_segment_angle;
    glVertex3f(point.x() + (length * std::cos(left_angle)),
               point.y() + (length * std::sin(left_angle)), point.z());

    const auto right_angle = angle + half_segment_angle;
    glVertex3f(point.x() + (length * std::cos(right_angle)),
               point.y() + (length * std::sin(right_angle)), point.z());

    glEnd();
}

void Geometry::draw_polygon(const core::Polygon3f& polygon, const Color& color)
{
    glBegin(GL_TRIANGLES);
    glColor4f(color.r, color.g, color.b, .1f);

    for(const auto& point : polygon.outer()) {
        glVertex3f(point.x(), point.y(), point.z());
    }

    glEnd();
}

} // namespace ipme::wb
