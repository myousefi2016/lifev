//@HEADER
/*
*******************************************************************************

    Copyright (C) 2004, 2005, 2007 EPFL, Politecnico di Milano, INRIA
    Copyright (C) 2010 EPFL, Politecnico di Milano, Emory University

    This file is part of LifeV.

    LifeV is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    LifeV is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with LifeV.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************
*/
//@HEADER

/*!
    @file BareMesh.hpp
    @brief Contains utility for importing meshes 

    @date 16 Aug 2011
    @author: luca formaggia
*/

#include <life/lifecore/LifeV.hpp>
#include <map>
#include <vector>
#include <life/lifemesh/ElementShapes.hpp>
#include <life/lifearray/ArraySimple.hpp>

#ifndef BAREMESH_HPP_
#define BAREMESH_HPP_

namespace LifeV
{

//! A struct for a bare mesh
/**
 * A very simple struct which stores an mesh as read from a file, ready to be imported in
 * a regionmesh
 * All SimpleArray have the first dimension the "shortest" one
 */
template <typename GeoShape>
struct RegionMeshBare{
    UInt nDimensions;
    ReferenceShapes refShape;
    ReferenceShapes bRefShape;
    ArraySimple<Real> points;
    std::vector<ID> pointsMarkers;
    ArraySimple<UInt> edges;
    std::vector<ID> edgesMarkers;
    UInt numBoundaryFaces;
    ArraySimple<UInt> faces;
    std::vector<ID> facesMarkers;
    ArraySimple<UInt> elements;
    std::vector<ID> elementsMarkers;

    void clear();
};

template <typename GeoShape>
void RegionMeshBare<GeoShape>::clear()
{
    clearVector ( points );
    clearVector ( pointsMarkers );
    clearVector ( edges );
    clearVector ( edgesMarkers );
    clearVector ( faces );
    clearVector ( facesMarkers );
    clearVector ( elements );
    clearVector ( elementsMarkers );
}

}

#endif /* BAREMESH_HPP_ */