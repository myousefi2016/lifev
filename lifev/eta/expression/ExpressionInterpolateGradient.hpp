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
    @file
    @brief File for the definition of the expression used to interpolate FE functions.

    @author Samuel Quinodoz <samuel.quinodoz@epfl.ch>

    @date 07-2011
 */

#ifndef EXPRESSION_INTERPOLATE_GRADIENT_HPP
#define EXPRESSION_INTERPOLATE_GRADIENT_HPP

#include <lifev/core/LifeV.hpp>

#include <lifev/core/array/VectorEpetra.hpp>

#include <lifev/eta/expression/ExpressionBase.hpp>

#include <lifev/eta/fem/ETFESpace.hpp>

#include <boost/shared_ptr.hpp>

#include <iostream>

namespace LifeV
{

namespace ExpressionAssembly
{

//! class ExpressionInterpolateGradient Class representing an interpolation in an expression.
/*!
  @author Samuel Quinodoz <samuel.quinodoz@epfl.ch>

  This class is meant to be used only in the expression tree, it does not perform
  any computation.

  <b> Template parameters </b>

  <i>MeshType</i>: The type of the mesh

  <i>MapType</i>: The type of the algebraic map (for parallel computations)

  <i>SpaceDim</i>: The ambiant space (for the finite element space)

  <i>FieldDim</i>: The dimension of the field to interpolate (scalar vs vectorial)

  <b> Template requirements </b>

  <i>MeshType</i>: Same as in LifeV::ETFESpace

  <i>MapType</i>: Same as in LifeV::ETFESpace

*/
template<typename MeshType, typename MapType, UInt SpaceDim, UInt FieldDim>
class ExpressionInterpolateGradient
    : public ExpressionBase<ExpressionInterpolateGradient < MeshType, MapType, SpaceDim, FieldDim > >
{
public:

    //! @name Public Types
    //@{

    // Base class, used only to make the code cleaner
    typedef ExpressionBase<ExpressionInterpolateGradient < MeshType, MapType, SpaceDim, FieldDim > > base_Type;

    //! Type of the finite element space
    typedef ETFESpace<MeshType, MapType, SpaceDim, FieldDim> fespace_Type;

    //! Type for the pointer on the finite element space
    typedef std::shared_ptr<fespace_Type> fespacePtr_Type;

    //! Data vector type
    typedef VectorEpetra vector_Type;

    //@}


    //! @name Constructors & Destructor
    //@{

    //! Constructor using the finite element space and the data vector
    ExpressionInterpolateGradient (fespacePtr_Type fespace, const vector_Type& vector, const UInt& offset)
        : base_Type(), M_fespace (fespace), M_vector (vector), M_offset (offset) {}

    //! Copy constructor
    ExpressionInterpolateGradient (const ExpressionInterpolateGradient<MeshType, MapType, SpaceDim, FieldDim>& expr)
        : base_Type(), M_fespace (expr.M_fespace), M_vector (expr.M_vector), M_offset (expr.M_offset) {}

    //! Destructor
    ~ExpressionInterpolateGradient() {}

    //@}


    //! @name Methods
    //@{

    //! Display method
    static void display (std::ostream& out = std::cout)
    {
        out << "interpolated_grad[" << FieldDim << "] ";
    }

    //@}


    //! @name Get Methods
    //@{

    //! Getter for the finite element space
    fespacePtr_Type fespace() const
    {
        return M_fespace;
    }

    //! Getter for the data vector
    const vector_Type vector() const
    {
        return M_vector;
    }

    //! Getter for the data vector
    const UInt offset() const
    {
        return M_offset;
    }

    // @}

private:

    //! @name Private Methods
    //@{

    //! No default constructor
    ExpressionInterpolateGradient();

    //@}

    // Storage for the finite element space
    fespacePtr_Type M_fespace;

    // Storage for the data vector
    vector_Type M_vector;

    //Offset to pick up the right portion of the vector
    UInt M_offset;
};

//! Simple function to be used in the construction of an expression
/*!
  @author Samuel Quinodoz <samuel.quinodoz@epfl.ch>

  <b> Template parameters </b>

  <i>MeshType</i>: The type of the mesh stored in the finite element space

  <i>MapType</i>: The type of map used in the finite element space

  <i>SpaceDim</i>: The dimension of the ambient space.

  <i>FieldDim</i>: The dimension of the finite element space (scalar vs vectorial)

  <b> Template requirements </b>

  <i>MeshType</i>: Same as in LifeV::ETFESpace

  <i>MapType</i>: Same as in LifeV::ETFESpace

*/
template<typename MeshType, typename MapType, UInt SpaceDim, UInt FieldDim>
inline ExpressionInterpolateGradient<MeshType, MapType, SpaceDim, FieldDim>
grad (
    std::shared_ptr< ETFESpace<MeshType, MapType, SpaceDim, FieldDim> > fespace,
    const VectorEpetra& vector,
    const UInt& offset = 0
)
{
    return ExpressionInterpolateGradient<MeshType, MapType, SpaceDim, FieldDim> (fespace, vector, offset);
}


} // Namespace ExpressionAssembly

} // Namespace LifeV

#endif
