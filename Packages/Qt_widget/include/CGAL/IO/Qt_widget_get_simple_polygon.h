// Copyright (c) 1997-2000  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source$
// $Revision$ $Date$
// $Name$
//
// Author(s)     : Laurent Rineau && Radu Ursu

#ifndef CGAL_QT_WIDGET_GET_SIMPLE_POLYGON_H
#define CGAL_QT_WIDGET_GET_SIMPLE_POLYGON_H

#include <CGAL/IO/Qt_widget_get_polygon.h>
#include <CGAL/Segment_2_Segment_2_intersection.h>  
#include <list>

#include <qcursor.h>

namespace CGAL {
template <class Polygon>
class Qt_widget_get_simple_polygon : public Qt_widget_get_polygon<Polygon>
{
public:
  typedef Qt_widget_get_polygon<Polygon>  Get_polygon;
  typedef typename Polygon::Point_2       Point_2;
  typedef typename Polygon::Segment_2     Segment_2;
  typedef typename Polygon::Edge_const_iterator  ECI;

  Qt_widget_get_simple_polygon(const QCursor
                               c=QCursor(Qt::crossCursor),QObject*
                               parent = 0, const char* name = 0)
    : Qt_widget_get_polygon<Polygon>(c, parent, name){}
  
protected:

  void mousePressEvent(QMouseEvent *e)
  {
    if(e->button() == Qt::RightButton && is_pure(e->state()))
    {
      if (active) {
        if(!poly.is_simple()) return;
        if(poly.is_clockwise_oriented())
          poly.reverse_orientation ();
        assert( ! poly.is_clockwise_oriented());
      }
    }
    Get_polygon::mousePressEvent(e);
  }; 

private:
  bool is_simple()
  {
    Segment_2 rubber_segment(rubber, last_of_poly);
    if(poly.size() > 1)
    {
      ECI before_last_it = poly.edges_end();
      --before_last_it;
      --before_last_it;
      ECI it;
      for(it = poly.edges_begin(); it != before_last_it; it++)
      {
        if(do_intersect(*it, rubber_segment))
        return false;
      }
      //if I'm out of this means that all the edges, 
      //didn't intersect the last one
      ++it;
      Object o = intersection(*it, rubber_segment);
      Point_2 p;
      if(assign(p, o))
        return true;
      else
        return false;
    }
    else
      return true;
  }
};

} // namespace CGAL

#endif // CGAL_QT_WIDGET_GET_SIMPLE_POLYGON_H
