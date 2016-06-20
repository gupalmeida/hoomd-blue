// Copyright (c) 2009-2016 The Regents of the University of Michigan
// This file is part of the HOOMD-blue project, released under the BSD 3-Clause License.

#include "hoomd/ParticleGroup.h"
#include "hoomd/Updater.h"
#include <cfloat>
#include <boost/shared_ptr.hpp>

/*! \file MuellerPlatheFlow.h

    \brief Declares a class to exchange velocities of
           different spatial region, to create a flow.
*/


//!Indicate a direction in a simulation box.
enum Direction
    {
    X=0,//!< X-direction
    Y,//!< Y-direction
    Z//!< Z-direction
    };
extern const unsigned int INVALID_TAG;
extern const Scalar INVALID_VEL;


//Above this line shared constructs can be declared.
#ifndef NVCC

#ifndef __MUELLER_PLATHE_FLOW_H__
#define __MUELLER_PLATHE_FLOW_H__

//! Applys a constraint force to keep a group of particles on a Ellipsoid
/*! \ingroup computes
*/
class MuellerPlatheFlow : public Updater
    {
    public:
        //! Constructs the compute
        //!
        //! \param direction Indicates the normal direction of the slabs.
        //! \param N_slabs Number of total slabs in the simulation box.
        //! \param min_slabs Index of slabs, where the min velocity is searched.
        //! \param max_slabs Index of slabs, where the max velocity is searched.
        //! \note N_slabs should be a multiple of the DomainDecomposition boxes in that direction.
        //! If it is not, the number is rescaled and the user is informed.
        MuellerPlatheFlow(boost::shared_ptr<SystemDefinition> sysdef,
                            boost::shared_ptr<ParticleGroup> group,
                            const unsigned int direction,
                            const unsigned int N_slabs,
                            const unsigned int min_slab,
                            const unsigned int max_slab);

        //! Destructor
        virtual ~MuellerPlatheFlow(void);

        //! Take one timestep forward
        virtual void update(unsigned int timestep);
        virtual Scalar summed_exchanged_momentum(void) const{return m_exchanged_momentum;}

        unsigned int get_N_slabs(void)const{return m_N_slabs;}
        unsigned int get_min_slab(void)const{return m_min_slab;}
        unsigned int get_max_slab(void)const{return m_max_slab;}

        void set_min_slab(const unsigned int slab_id);
        void set_max_slab(const unsigned int slab_id);

        //! Determine, whether this part of the domain decomposition
        //! has particles in the min slab.
        bool has_min_slab(void)const{return m_has_min_slab;}
        //! Determine, whether this part of the domain decomposition
        //! has particles in the max slab.
        bool has_max_slab(void)const{return m_has_max_slab;}

        //! Call function, if the domain decomposition has changed.
        void update_domain_decomposition(void);
    protected:
        //! Group of particles, which are searched for the velocity exchange
        boost::shared_ptr<ParticleGroup> m_group;

        virtual void search_min_max_velocity(void);
        virtual void update_min_max_velocity(void);

        //!Temporary variables to store last found min vel;
        Scalar_Int m_last_min_vel;
        //!Temporary variables to store last found max vel;
        Scalar_Int m_last_max_vel;
    private:
        enum Direction m_direction;
        unsigned int m_N_slabs;
        unsigned int m_min_slab;
        unsigned int m_max_slab;

        Scalar m_exchanged_momentum;

        bool m_has_min_slab;
        bool m_has_max_slab;
#ifdef ENABLE_MPI
        struct MPI_SWAP{
            MPI_Comm comm;
            int rank;
            int size;
            int gbl_rank; //!< global rank of zero in the comm.
            };
        struct MPI_SWAP m_min_swap;
        struct MPI_SWAP m_max_swap;
        void init_mpi_swap(struct MPI_SWAP* ms,const int color);
        void bcast_vel_to_all(struct MPI_SWAP*ms,Scalar_Int*vel,const MPI_Op op);
        void mpi_exchange_velocity(void);
#endif//ENABLE_MPI
    };

//! Exports the MuellerPlatheFlow class to python
void export_MuellerPlatheFlow();

#endif//NVCC
#endif//__MUELLER_PLATHE_FLOW_H__
