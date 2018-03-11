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

_(How does make all change things? I'm wondering because Peter's script calls it.)_  
A. Brian told me he used make all because it was convenient after calling make clean. I would like to avoid using make clean, but he also mentioned that make all affected BUILD_SUCCESS in that it would only run tests if everything was in order.

Note: In the case make clean is called, it may be 
relevant to know that src/utils has a make target.

1) Building the kernel.

```
cd src/userprog
make
```

2) Create a filesystem disk for `userprog`. _(Assumes the kernel was built under `userprog`)_ The disk name must be "filesys.dsk", otherwise the kernel will panic. Also, even though it would be nice, the --fs-disk=n option (which would remove this step) for pintos does not seem to work as it is described in the manual.

```
cd ~/pintos/src/userprog/build
pintos-mkdisk filesys.dsk --filesys-size=2
```

3) Format the disk with a filesystem partition. _(Assumes the kernel was built under `userprog`.)_

```
pintos -f -q
```

4) Run the tests. This is what the grader will use. If possible, I would prefer a testing script like one that Brian made. He has one for pintos 2, but as far as I know it doesn't work 100% yet.

```
cd ~/pintos/src/userprog/build
make check VERBOSE=1
```
5) Building, then loading example programs into the already-existing filesys.dsk disk. _Current Confusion:_ There appears to be no difference in the run whether or not the program is actually loaded. It will produce no output and no page faults. Am I using the wrong quotes?

```
cd ~/pintos/src/examples
make
cd ~/pintos/userprog/build
pintos -p ../../examples/echo -a echo -- -q
pintos -q run ’echo x’
```

