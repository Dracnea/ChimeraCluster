# Installation Guide for OpenMP Based Software

## Prerequisites

The following should be done before performing any installations:

First make sure that all current apt's are up to date in order to grab the most recent versions for compilers and openMP software.
THIS MAY BREAK RPI4 AS IT HAS LITTLE OS / BOOT FILE SUPPORT AS OF 8/26/19.

`sudo apt-get update` <br />
`sudo apt-get upgrade` <br />
`sudo reboot` <br />

Ensure that gcc, g++ and gfortran are all installed for C, C++ and Fortran compiler support. Most systems should at least initially have gcc.

`sudo apt-get install gcc` <br />
`sudo apt-get install g++` <br />
`sudo apt-get install gfortran` <br />

Check to see if any openMP related software is already installed and what version it currently is.

For C/C++/Fortran <br />
`sudo openmpi-bin_info` <br />
For Python <br />
`sudo python-mpi4py_info` <br />

## Basic Installation

The Basic Installation is the simpliesta dn most recommended way to add openMP software to your device. This will grab the latest build that is stable based on your OS and Processor type. This may mean that your installed version will not be the latest OpenMP version but this is fine.

#### Installation of OpenMPI:
For C/C++/Fortran <br />
`sudo apt-get install openmpi-bin` <br />

#### Installation of MPI4PY:
For Python <br />
`sudo apt-get install python-mpi4py` <br />

## Basic Testing

Once all OpenMP software has been installed it can be tested using the command mpiexec. Here are some examples:

With a Compiled C Program <br />
`mpiexec ./helloWorld`<br />

With a Python Script <br />
`mpiexec python test.py`<br />
