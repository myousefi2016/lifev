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

/**
   @file user_fun.cpp
   @author L. Oldani <luca.oldani@mail.polimi.it>
   @date 2014-09-20
*/

#ifndef __user_fun_H
#define __user_fun_H 1

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <boost/numeric/ublas/matrix.hpp>

#pragma GCC diagnostic warning "-Wunused-variable"
#pragma GCC diagnostic warning "-Wunused-parameter"

#include <lifev/core/LifeV.hpp>

#include <lifev/core/mesh/RegionMesh.hpp>
#include <lifev/core/mesh/RegionMesh2DStructured.hpp>

#include <lifev/core/fem/HyperbolicGodunovFlux.hpp>

#include <lifev/core/solver/MultirateSolver.hpp>

namespace DataProblem
{

using namespace LifeV;

// ===================================================
//!                   Typedef
// ===================================================

typedef LinearQuad geoElement_Type;
typedef RegionMesh < geoElement_Type > regionMesh_Type;
typedef boost::shared_ptr < regionMesh_Type > regionMeshPtr_Type;

typedef MeshPartitioner < regionMesh_Type > meshPartitioner_Type;

typedef boost::shared_ptr < meshPartitioner_Type > meshPartitionerPtr_Type;

typedef MapEpetra map_Type;

typedef FESpace < regionMesh_Type, map_Type > fESpace_Type;
typedef boost::shared_ptr < fESpace_Type > fESpacePtr_Type;

typedef FEVectorField < regionMesh_Type, map_Type > vectorField_Type;
typedef boost::shared_ptr < vectorField_Type > vectorFieldPtr_Type;

typedef FEFunction < regionMesh_Type, map_Type, Vector > vectorFct_Type;
typedef boost::shared_ptr < vectorFct_Type > vectorFctPtr_Type;


// ===================================================
//!                  User defined flux
// ===================================================

const Real k=1;
const Real mu=0.085;
const Real phi=0.018;
const Real g=0.098;
const Real gradP=0.0001;

class
HyperbolicUserFlux : public HyperbolicPhysicalFlux<HyperbolicUserFlux>
{

friend class HyperbolicPhysicalFlux<HyperbolicUserFlux>;

protected:

//    Vector3D flux_impl ( const UInt& /*flag*/, const Vector3D& /*P*/, const Real& /*time*/, const Real& u ) const
//    {
//        return Vector3D ( 0 , 2*u + u*u*u - u * u, 0. );	
//    
//    } // flux_impl

//    Vector3D fluxPrime_impl ( const UInt& /*flag*/, const Vector3D& /*P*/, const Real& /*time*/, const Real& u ) const
//    {
//     	return Vector3D( 0  , 2+3*u*u- 2*u, 0. );    
//
//    } // fluxPrime_impl 

//    Vector3D flux_impl ( const UInt& /*flag*/, const Vector3D& /*P*/, const Real& /*time*/, const Real& u ) const
//    {
//        return Vector3D ( 2*u*u+1*cos(u*3.14/2) , 2*u*u+1*cos(u*3.14/2), 0. );	
//    
//    } // flux_impl

//    Vector3D fluxPrime_impl ( const UInt& /*flag*/, const Vector3D& /*P*/, const Real& /*time*/, const Real& u ) const
//    {
//     	return Vector3D( 4*u + 1*3.14/2*(sin(u*3.14/2))  , 4*u + 1*3.14/2*(sin(u*3.14/2)), 0. );    

//    } // fluxPrime_impl 



    Vector3D flux_impl ( const UInt& /*flag*/, const Vector3D& /*P*/, const Real& /*time*/, const Real& u ) const
    {
        return Vector3D ( u * u / 2 , 0. , 0. );
    
    } // flux_impl

    Vector3D fluxPrime_impl ( const UInt& /*flag*/, const Vector3D& /*P*/, const Real& /*time*/, const Real& u ) const
    {
     	return Vector3D( u , 0. , 0. );

    } // fluxPrime_impl 

//    Real maxAbsFluxPrimeDotNormal_impl ( const UInt& /*iElem*/, const Vector3D& /*P*/, const Real& /*time*/,
/*                                         const Real& leftState, const Real& rightState,
                                         const Vector3D& normal ) const
    {
        return std::fabs( normal(0) * std::max( leftState, rightState ) );
    } // maxAbsFluxPrimeDotNormal_impl
*/
//    Real computeRiemannSolver_impl ( const UInt& /*elemCurrent*/, const UInt& /*elemNeighbor*/,
//                                     const Vector3D& /*P*/, const Real& /*time*/,
/*                                     const Real& stateCurrent, const Real& stateNeighbor,
                                     const Vector3D& normal ) const
    {
        return 0.5 * normal ( 0 ) * ( ( normal(0) > 0 )? stateCurrent * stateCurrent: stateNeighbor * stateNeighbor );
    } // computeRiemannSolver_impl
*/
};

typedef MultirateSolver< regionMesh_Type, HyperbolicGodunovFlux<HyperbolicUserFlux>, HyperbolicUserFlux > multirateSolver_Type;

typedef multirateSolver_Type::data_Type multirateData_Type;
typedef multirateSolver_Type::dataPtr_Type multirateDataPtr_Type;

typedef multirateSolver_Type::vector_Type vector_Type;
typedef multirateSolver_Type::vectorPtr_Type vectorPtr_Type;

typedef multirateSolver_Type::scalarField_Type scalarField_Type;
typedef multirateSolver_Type::scalarFieldPtr_Type scalarFieldPtr_Type;

typedef multirateSolver_Type::scalarFct_Type scalarFct_Type;
typedef multirateSolver_Type::scalarFctPtr_Type scalarFctPtr_Type;

typedef multirateSolver_Type::bcHandler_Type bcHandler_Type;
typedef multirateSolver_Type::bcHandlerPtr_Type bcHandlerPtr_Type;

typedef HyperbolicUserFlux physicalFlux_Type;


// ===================================================
//!                    Problem data
// ===================================================

// Initial time condition
class initialCondition : public scalarFct_Type
{
public:
    virtual Real eval ( const UInt& iElem, const Vector3D& P, const Real& time = 0. ) const;
};

// Mass function
class massTerm : public scalarFct_Type
{
public:
    virtual Real eval ( const UInt& iElem, const Vector3D& P, const Real& time = 0. ) const;
};

// ===================================================
//!                    Boundary data
// ===================================================

void setBoundaryConditions ( bcHandlerPtr_Type & bcHyperbolic ) ;

// Boundary condition of Dirichlet
Real dirichletL ( const Real& t, const Real& x, const Real& y, const Real& z, const ID& ic );
// Boundary condition of Dirichlet
Real dirichletB ( const Real& t, const Real& x, const Real& y, const Real& z, const ID& ic );

// ===================================================
//!                 Analytical solution
// ===================================================

// Analytical solution
Real analyticalSolution ( const Real& t, const Real& x, const Real& y, const Real& z, const ID& ic );

} // Namespace DataProblem

#endif /* __user_fun_H */