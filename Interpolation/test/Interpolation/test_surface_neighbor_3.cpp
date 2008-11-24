// Copyright (c) 2003   INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Julia Floetotto

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Triangulation_hierarchy_3.h>
#include <CGAL/aff_transformation_tags.h>

#include <CGAL/_test_surface_neighbors_3.cpp>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_3<K>                   Dt;

typedef CGAL::Exact_predicates_exact_constructions_kernel K2;
typedef CGAL::Delaunay_triangulation_3<K2>                   Dt2;

//Hierarchy with exact pred exact const. kernel:
typedef CGAL::Triangulation_vertex_base_3<K2>             Vb;
typedef CGAL::Triangulation_hierarchy_vertex_base_3<Vb>  Vbh;
typedef CGAL::Triangulation_data_structure_3<Vbh>        Tds;
typedef CGAL::Delaunay_triangulation_3<K2,Tds>            Dt1;
typedef CGAL::Triangulation_hierarchy_3<Dt1>              Dh;


// Aff_transformation:
typedef CGAL::Aff_transformation_3<K2>                   Transformation;

int main()
{
  std::cout << "Using Exact_predicates_inexact_constructions_kernel: " << std::endl ;
  std::cout << "Testing surface_neighbors_3 on a sphere ";
  _test_surface_neighbors_3_sphere( Dt() );
  std::cout << " done." << std::endl << std::endl;


  std::cout << "Using Exact_predicates_exact_constructions_kernel: "
	    << std::endl;

  //AXIS ALIGNED CUBE
  Transformation identity(CGAL::IDENTITY);
  std::cout << "Testing surface_neighbors_3 on a cube with axis : "
	    << identity(K2::Vector_3(0,0,1)) << ",  "
	    << identity(K2::Vector_3(0,1,0))<< ",  "
	    << identity(K2::Vector_3(1,0,0))
	    << std::endl;
  std::cout << " with grid sample points";
  _test_surface_neighbors_3_cube(Dt2(),identity, 75, K2::FT(1e-29));
  std::cout << " done." << std::endl;

  std::cout << " with random sample points";
  _test_surface_neighbors_3_cube( Dt2(), identity,150, K2::FT(1e-2),false);
  std::cout << " done." << std::endl << std::endl;

  //ROTATED CUBE
  Transformation rotate(K2::RT(1),K2::RT(0),K2::RT(0),K2::RT(0),
			K2::RT(0),K2::RT(0.9063),K2::RT(-0.42261826),K2::RT(0),
			K2::RT(0),K2::RT(0.42261826),K2::RT(0.9063),K2::RT(0));
  std::cout << "Testing surface_neighbors_3 on a ROTATED cube "<< std::endl;
  std::cout << " with grid sample points";
  _test_surface_neighbors_3_cube(Dh(),rotate, 75, K2::FT(1e-2), true);
  std::cout << " done." << std::endl << std::endl;

//  //undersampled rotated cube
//   Transformation  rotate3(K2::RT(0.1),K2::RT(0.4),K2::RT(0.6),K2::RT(0),
// 			  K2::RT(0.3),K2::RT(0.5),K2::RT(0.1),K2::RT(0),
// 			  K2::RT(0.5),K2::RT(0.9),K2::RT(0.8),K2::RT(0));
//   std::cout << "Testing surface_neighbors_3 on an undersampled ROTATED cube "
// 	    << std::endl;
//   std::cout << " with grid sample points";
//   _test_surface_neighbors_3_cube(Dh(),rotate3,75, K2::FT(9), true);
//   std::cout << " done." << std::endl << std::endl;

  return 0;
}
