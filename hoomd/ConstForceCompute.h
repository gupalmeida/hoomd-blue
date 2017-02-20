// Copyright (c) 2009-2016 The Regents of the University of Michigan
// This file is part of the HOOMD-blue project, released under the BSD 3-Clause License.


// Maintainer: joaander

#include "ForceCompute.h"
#include "ParticleGroup.h"

#include <memory>

/*! \file ConstForceCompute.h
    \brief Declares a class for computing constant forces
*/

#ifdef NVCC
#error This header cannot be compiled by nvcc
#endif

#include <hoomd/extern/pybind/include/pybind11/pybind11.h>

#ifndef __CONSTFORCECOMPUTE_H__
#define __CONSTFORCECOMPUTE_H__

//! Adds a constant force to a number of particles
/*! \ingroup computes
*/
class ConstForceCompute : public ForceCompute
    {
    public:
        //! Constructs the compute
        ConstForceCompute(std::shared_ptr<SystemDefinition> sysdef, Scalar fx, Scalar fy, Scalar fz, 
                                                                    Scalar tx=0, Scalar ty=0, Scalar tz=0);
        ConstForceCompute(std::shared_ptr<SystemDefinition> sysdef, std::shared_ptr<ParticleGroup> group, Scalar fx, Scalar fy, Scalar fz, 
                                                                                                      Scalar tx=0, Scalar ty=0, Scalar tz=0);

        //! Destructor
        ~ConstForceCompute();

        //! Set the force to a new value
        void setForce(Scalar fx, Scalar fy, Scalar fz, Scalar tx=0, Scalar ty=0, Scalar tz=0);

        //! Set the force for an individual particle
        void setParticleForce(unsigned int i, Scalar fx, Scalar fy, Scalar fz, Scalar tx=0, Scalar ty=0, Scalar tz=0);

        //! Set force for a particle group
        void setGroupForce(std::shared_ptr<ParticleGroup> group, Scalar fx, Scalar fy, Scalar fz, Scalar tx=0, Scalar ty=0, Scalar tz=0);

    protected:

        //! Function that is called on every particle sort
        void rearrangeForces();

        //! Actually compute the forces
        virtual void computeForces(unsigned int timestep);

    private:

        Scalar m_fx; //!< Constant force in x-direction
        Scalar m_fy; //!< Constant force in y-direction
        Scalar m_fz; //!< Constant force in z-direction
        Scalar m_tx; //!< x-component of torque vector
        Scalar m_ty; //!< y-component of torque vector
        Scalar m_tz; //!< z-component of torque vector

        //! Group of particles to apply force to
        std::shared_ptr<ParticleGroup> m_group;
    };

//! Exports the ConstForceComputeClass to python
void export_ConstForceCompute(pybind11::module& m);

#endif
