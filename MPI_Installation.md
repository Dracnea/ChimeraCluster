# Installation Guide for MPI Based Software

## What is MPI?

MPI is a group of softwares used within computer clusters or other groups of computers to pass messages between each node (computer) to allow for the full cluster to run a given piece of code or application. There are different versions of OpenMP based on what languages you plan to have the clustered computer running. These different softwares can be run side by side in order to allow for a variety of programming langauges to be used over the clusters combined computing power.

## Prerequisites

The following should be done before performing any installations:

First make sure that all current apt's are up to date in order to grab the most recent versions for compilers and openMP software.
THIS MAY BREAK RPI4 AS IT HAS LITTLE OS / BOOT FILE SUPPORT AS OF 8/26/19.

`sudo apt-get update` <br />
`sudo apt-get upgrade` <br />
`sudo reboot` <br />

Ensure that you have Make installed.

`sudo apt-get install make` <br />

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

The Basic Installation is the simpliest and recommended way to add openMP software to your device. This will grab the latest build that is stable based on your OS and Processor type. This may mean that your installed version will not be the latest OpenMP version but this is fine.

### On Standard Linux Flavors

#### Installation of OpenMPI:
For C/C++/Fortran <br />
`sudo apt-get install openmpi-bin` <br />

#### Installation of MPI4PY:
For Python <br />
`sudo apt-get install python-mpi4py` <br />

### On Gentoo and Similar Flavors

#### Installation of OpenMPI:
For C/C++/Fortran <br />
`sudo emerge --ask --autounmask-write sys-cluster/openmpi` <br />

#### Installation of MPI4PY:
For Python <br />
`sudo emerge --ask --autounmask-write dev-python/mpi4py` <br />

Both commands should then be followed by
`sudo dispatch-conf` <br />
Followed by entering 'u' to use the new config. Then rerun the original command without the `--autounmask-write` tag.

Installing hpl may also be benficial depending on cluster use: <br />
`sudo emerge --ask --autounmask-write sys-cluster/hpl` <br />

## Basic Testing

Once all OpenMP software has been installed it can be tested using the command mpiexec. Here are some examples:

With a Compiled C Program <br />
`mpiexec ./helloWorld`<br />

With a Python Script <br />
`mpiexec python test.py`<br />

## Advanced Installation

You may also choose to locally build and install a more recent version of any of the OpenMP software. It is not recommended that you replace any current versions of OpenMP installed using the Command Line or that came prepackaged with your OS as they may be vital or are the most recent stable version based on your OS and Processor. Locally building newer versions of OpenMP software may work on your computer but, even if they fully work, please keep in mind that they are not considered stable or supported.

#### Initial Setup

Before you begin you will want to create the following directories: <br />
`sudo mkdir /usr/local/openMPI` <br />
`sudo mkdir /usr/local/openMPI-dl` <br />
`sudo mkdir /usr/local/openMPI-build` <br />

#### Local OpenMPI Installation

Begin by moving to your openMPI download folder: <br />
`cd /usr/local/openMPI-dl` <br />

Download the most recent version of OpenMPI: (This example shows Version 4.0.1) <br />
`sudo wget https://download.open-mpi.org/release/open-mpi/v4.0/openmpi-4.0.1.tar.gz`<br />

Extract the file from the tar.gz: <br />
`sudo tar zxcf openmpi-4.0.1.tar.gz` <br />

Move to your build folder: <br />
`cd /usr/local/openMPI-build` <br />

Run the Configuration Process: (This will take some time.) <br />
`sudo /usr/local/openMPI-dl/openmpi-4.0/configure –prefix=/usr/local/openMPI` <br />

Make the build: (This will take a very long time.) <br />
`sudo make` <br />

Install the build: <br />
`sudo make all install`

#### Local Version Testing

Now you will want to test the locally installed version of OpenMPI. 
Run the following command: <br />
`/usr/local/openMPI/bin/mpiexec -n 1 date` <br />
So long as this returns the date once than this local version of mpi is installed.

MPI4PY can also be tested on this locally run OpenMPI version by first making sure that MPI4PY is installed via: <br />
`sudo apt-get install python-mpi4py` <br />
OR <br />
`sudo apt install python-pip python-dev libopenmpi-dev`<br />
`sudo apt-get install pip` <br />
`sudo pip install mpi4py` <br />
followed by the command with a valid Python file: <br />
`/usr/local/openMPI/bin/mpiexec -n 4 python test.py` <br />

## Final Setups

Now we need to make sure that the master node can access all of the other nodes.
Proceed to make a file called nodeips (a txt) with a list of just the ips for each node.

We also need to exchange ssh keys between the systems to allow the nodes to be accessed without the need for a password.
This should all be done through the master.
To generate the key: <br />
`ssh-keygen -t rsa1` <br />

Transfer the key to all nodes 1 at a time: <br />
`scp /home/USERNAME/.ssh/id_rsa.pub USERNAME@EXA.MPL.E.*:/home/USERNAME/master.pub` <br />

Then ssh into each node: <br />
`ssh USERNAME@EXA.MPL.E.*` <br />
And Enter the Following: <br />
`cat master.pub >> .ssh/authorized_keys` <br />
`exit` <br />

Now you should be able to connect to each node without a password and can check this by re-sshing into each node.

#### Cluster Usage

OpenMPI uses the following syntax for taking in a hostname file to access each node. <br />
Note that this first example will return the hostname of each node. <br />
`mpiexec -n 2 --hostfile ~/nodeips.txt hostname` <br />
Example of how to give mpiexec a machine file (executable) to run <br />
`mpiexec -n 2 --hostfile ~/nodeips.txt --machinefile ./HelloWorld`<br />
