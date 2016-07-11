// Copyright (c) 2009-2016 The Regents of the University of Michigan
// This file is part of the HOOMD-blue project, released under the BSD 3-Clause License.


/*! \file upp11_config.h
    \brief Helps unit tests setup the upp11 unit testing framework
    \details much of this is replicated from the old boost files, future unit
    tests are welcome to include only standard usage
    \note This file should be included only once and by a file that will
        compile into a unit test executable
*/

#include "hoomd/HOOMDMath.h"
#include <cmath>
#include "hoomd/extern/upp11/upp11.h"

// ******** helper macros
#define CHECK_CLOSE(a,b,c) UP_ASSERT((abs(a-b) <= (c * abs(a))) && (abs(a-b) <= (c * abs(b))))
#define CHECK_SMALL(a,c) UP_ASSERT(abs(a) < c)
//! Helper macro for checking if two numbers are close
#define MY_CHECK_CLOSE(a,b,c) UP_ASSERT(abs(a - Scalar(b)) < Scalar(c))
//! Helper macro for checking if a number is small
#define MY_CHECK_SMALL(a,c) CHECK_SMALL( a, Scalar(c))
//! Need a simple define for checking two values which are unsigned
#define CHECK_EQUAL_UINT(a,b) UP_ASSERT_EQUAL(a,(unsigned int)(b))

#define MY_ASSERT_EQUAL(a,b) UP_ASSERT(a == b)

//! Tolerance setting for near-zero comparisons
const Scalar tol_small = Scalar(1e-3);

//! Tolerance setting for comparisons
const Scalar tol = Scalar(1e-2);

//! Loose tolerance to be used with randomly generated and unpredictable comparisons
Scalar loose_tol = Scalar(10);

// helper functions to set up MPI environment
#include "MPITestSetup.h"
