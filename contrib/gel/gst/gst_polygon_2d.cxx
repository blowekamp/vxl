/*
  crossge@crd.ge.com
*/
#ifdef __GNUC__
#pragma implementation "gst_polygon_2d"
#endif

#include <gst/gst_vertex_2d_ref.h>

#include "gst_polygon_2d.h"


bool gst_polygon_2d::check_validity() const
{
  // no edge list
  if( edges_.size()<1)
    return false;

  // cycle through edges, looking for a completed polygon
  gst_vertex_2d_ref start= edges_[0]->get_start();
  gst_vertex_2d_ref end  = edges_[0]->get_end();

  // length of cycle
  int clen= 1;

  while( end.ptr()!= start.ptr())
    {
      // next edge
      bool found= false;

      for( int i=0; ((i< edges_.size()) && !found); i++)
	{
	  if( edges_[i]->get_start().ptr()== end.ptr())
	    {
	      found= true;
	      end= edges_[i]->get_end();
	    }
	}
      
      // if !found then the cycle isn't closed
      if( !found) return false;

      clen++;
    }

  // check we have looked at all the edges
  if( clen== edges_.size()) return true;

  return false;
}

// returns the centroid
double gst_polygon_2d::get_centroid_x() const
{
  double xsum= 0;

  for( int i=0; i< edges_.size(); i++)
    {
      xsum+= edges_[i]->get_start()->get_x();
    }

  return xsum/edges_.size();
}

double gst_polygon_2d::get_centroid_y() const
{
  double ysum= 0;

  for( int i=0; i< edges_.size(); i++)
    {
      ysum+= edges_[i]->get_start()->get_y();
    }

  return ysum/edges_.size();
}


// returns the area (signed)
//        2 A( P ) = sum_{i=0}^{n-1} (x_i y_{i+1} - y_i x_{i+1}).
double gst_polygon_2d::area() const
{
  double a= 0;

  for( int i=0; i< edges_.size(); i++)
    {
      int ip1=((i+1)==edges_.size())?0:(i+1);

      double dp= edges_[i]->get_start()->get_x()* edges_[ip1]->get_start()->get_y()
               - edges_[i]->get_start()->get_x()* edges_[ip1]->get_start()->get_x();

      a+= dp;
    }

  return (a/2);
}


// simple and efficient point in polygon test.
//   from comp.graphics.algorithms faq
//   should only call if validity passes (no check
//   for efficiency)
bool gst_polygon_2d::inside( const double x, const double y) const
{
  bool c= false;

  for( int i=0, j= edges_.size()-1; i< edges_.size(); j= i++)
    {
      if ((((edges_[i]->get_start()->get_y()<= y) && 
	    (y< edges_[j]->get_start()->get_y())) ||
	   ((edges_[j]->get_start()->get_y()<= y) && 
	    (y< edges_[i]->get_start()->get_y()))) &&
	  (x< (edges_[j]->get_start()->get_x() - 
	       edges_[i]->get_start()->get_x()) * (y - 
						   edges_[i]->get_start()->get_y()) / 
	   (edges_[j]->get_start()->get_y() - edges_[i]->get_start()->get_y()) + 
	   edges_[i]->get_start()->get_x()))
	{
	  c=!c;
	}
      
    }
  
  return c;
}

bool gst_polygon_2d::inside( const gst_vertex_2d_ref v) const
{
  return inside( v->get_x(), v->get_y());
}


ostream &operator<<( ostream &os, gst_polygon_2d &p)
{
  for( int i=0; i< p.edges_.size(); i++)
    {
      os << (*p.edges_[i]) << " ";
    }

  return os << endl;
}
