Getting started
---------------

Compilation requirements
~~~~~~~~~~~~~~~~~~~~~~~~
You will need a toolchain for the target architecture.

* To select the architecture pass **ARCH=<arch>** to make.
* To select the toolchain pass **TOOLCHAIN=<toolchain>** to make.

.. note::

   haruhios only supports x86 at the moment.

Compiling
~~~~~~~~~
To compile the operating system, run::

   make

Pass variables if needed.

Installing in loop device
~~~~~~~~~~~~~~~~~~~~~~~~~
To install haruhios using a loop device, run with root privileges::

   make install_loop

.. note::

   This will reserve /dev/loop42 so make sure its free.


Cleaning
~~~~~~~~
Clean all object and preprocessed files with::

   make clean

