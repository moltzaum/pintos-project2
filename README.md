### README for Project 1: Threads

#### Design Document

The design document can be found in *DOC_P1.md* in the same 
folder as this _README_

#### Group Participants
 
Matthew Moltzau <matthew.moltzau@ucdenver.edu>  
Michael Hedrick <michael.hedrick@ucdenver.edu>

#### Common Commands to Run

##### Compiling the Kernel Manually
> cd $PINTOS_ROOT/src/threads  
> make

##### Running a Single Test 
> pintos -v -- run *test_name*  

##### Running the Testing Script  
The script will run tests as they appear in the script 
internally. We have two separate scripts 1) The original
_and_ 2) The one accessible from any place in the commandline
provided src/utils is in $PATH. This version may also accept 
"debug" as an argument, which passes --gdb when running the pintos kernel.
> p1-thread-tests

_OR_
> cd $PINTOS_ROOT/src/threads  
> bash pintos-p1-tests.sh

#### _TODO_

_Alarm:_  
The alram may need to be updated. See details in the design doc.

*DOC_P1:*  
There are just a couple loose strings in the design doc.

Run the tests for Project 2: User Programs

_Note: Project 2 does not need any of the functionality implemented in Project 1. In particular, all threads are created with priority `PRI_DEFAULT` and the scheduler runs simple round-robin. So, if you passed all tests in Project 1, you can just continue working in your current install. Or, you can start with a new raw Pintos install._

1. Make sure you run a top-level clean (of `threads`) before you build for `userprog`.

```
cd ~/pintos
make clean
```

2. In the Perl script `src/utils/pintos`, change `kernel.bin` on line **257** to `/home/pintos/pintos/src/userprog/build/kernel.bin`.

3. In the Perl script `src/utils/Pintos.pm`, change `kernel.bin` on line **362** to `/home/pintos/pintos/src/userprog/build/loader.bin`.

4. Build the project.

```
cd src/utils
make
cd src/userprog
make
cd build
```

5. Create a filesystem disk for `userprog`. _(Assumes the kernel was built under `userprog/`. Similarly, for `vm` and `filesys`.)_

```
cd ~/pintos/src/userprog/build
pintos-mkdisk filesys.dsk --filesys-size=2
```

6. Format the disk with a filesystem partition. _(Assumes the kernel was built under `userprog/`. Similarly, for `vm` and `filesys`.)_

```
pintos -f -q
```

7. Run the tests.

```
cd ~/pintos/src/userprog/build
make check VERBOSE=1
```

8. To load and run the example user programs, you need to build them first.

```
cd ~/pintos/src/examples
make
cd ~/pintos/userprog/build
pintos -p ../../examples/echo -a echo -- -q
pintos -q run ’echo x’
```

