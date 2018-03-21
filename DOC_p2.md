		     +--------------------------+
		     | PROJECT 2: USER PROGRAMS |
		     |     DESIGN DOCUMENT      |
		     +--------------------------+

__---- GROUP ----__

Matthew Moltzau  
Michael Hedrick  

ARGUMENT PASSING
----------------

__---- DATA STRUCTURES ----__

##### A1: Copy here the declaration of each new or changed `struct` or `struct` member, global or static variable, `typedef`, or enumeration. Identify the purpose of each in 25 words or less.

```c 
//TODO
```

__---- ALGORITHMS ----__

##### A2: Briefly describe how you implemented argument parsing.  How do you arrange for the elements of argv[] to be in the right order? How do you avoid overflowing the stack page?

__---- RATIONALE ----__

##### A3: Why does Pintos implement strtok_r() but not strtok()?

`strtok_r` is the reentrant version of `strtok`, which means it can be resumed
after being interrupted. It is the thread-safe version. We will be dealing with
a lot of interrupts in the kernel so it very important that our methods are safe
to use at all times.

##### A4: In Pintos, the kernel separates commands into a executable name and arguments. In Unix-like systems, the shell does this separation. Identify at least two advantages of the Unix approach.

SYSTEM CALLS
------------

__---- DATA STRUCTURES ----__

##### B1: Copy here the declaration of each new or changed `struct` or `struct` member, global or static variable, `typedef`, or enumeration.  Identify the purpose of each in 25 words or less.

```c 
//TODO
```

##### B2: Describe how file descriptors are associated with open files. Are file descriptors unique within the entire OS or just within a single process?

A file descriptor is a unique identifier for an open file. A file opened multiple
times is associated with multiple file descriptors, so it is important to note
that there is a difference between a "file" and an "open file". Two different
open files may reference the same file. Note: `file` as it is defined in file.c
is an "open file". It is easier to see the relationship when you realize a file
holds a pointer to an inode, while that inode has a variable `open_cnt` to see
how many times that particular file is open. Different "open files" also have
different file positions.

I decided to make file descriptors unique just within a single process. I thought
about doing it statically, but then we'd have to synchronize incrementing it.
Organizing file descriptors makes it so that processes cannot share the same
"open files", which I am fine with. I guess one exception would be stdin and
stdout, which have the same fd for all processes.

__---- ALGORITHMS ----__

##### B3: Describe your code for reading and writing user data from the kernel.

##### B4: Suppose a system call causes a full page (4,096 bytes) of data to be copied from user space into the kernel.  What is the least and the greatest possible number of inspections of the page table (e.g. calls to pagedir_get_page()) that might result?  What about for a system call that only copies 2 bytes of data?  Is there room for improvement in these numbers, and how much?

##### B5: Briefly describe your implementation of the "wait" system call and how it interacts with process termination.

##### B6: Any access to user program memory at a user-specified address can fail due to a bad pointer value.  Such accesses must cause the process to be terminated.  System calls are fraught with such accesses, e.g. a "write" system call requires reading the system call number from the user stack, then each of the call's three arguments, then an arbitrary amount of user memory, and any of these can fail at any point.  This poses a design and error-handling problem: how do you best avoid obscuring the primary function of code in a morass of error-handling?  Furthermore, when an error is detected, how do you ensure that all temporarily allocated resources (locks, buffers, etc.) are freed?  In a few paragraphs, describe the strategy or strategies you adopted for managing these issues.  Give an example.

__---- SYNCHRONIZATION ----__

##### B7: The "exec" system call returns -1 if loading the new executable fails, so it cannot return before the new executable has completed loading.  How does your code ensure this?  How is the load success/failure status passed back to the thread that calls "exec"?

##### B8: Consider parent process P with child process C.  How do you ensure proper synchronization and avoid race conditions when P calls wait(C) before C exits?  After C exits?  How do you ensure that all resources are freed in each case?  How about when P terminates without waiting, before C exits?  After C exits?  Are there any special cases?

__---- RATIONALE ----__

##### B9: Why did you choose to implement access to user memory from the kernel in the way that you did?

##### B10: What advantages or disadvantages can you see to your design for file descriptors?

##### B11: The default tid_t to pid_t mapping is the identity mapping. If you changed it, what advantages are there to your approach?