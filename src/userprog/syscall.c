#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{
  printf ("system call!\n");
  
  //print information about the interrupt frame:
  //intr_dump_frame (f);
  
  //calling this seems to create an infinite loop
  //intr_handler (f);
  
  printf ("now going to loop until exit\n");
  thread_exit ();
}
