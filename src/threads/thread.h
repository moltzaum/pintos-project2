#ifndef THREADS_THREAD_H
#define THREADS_THREAD_H

#include <debug.h>
#include <list.h>
#include <stdint.h>
#include <threads/synch.h>
#include <threads/fixed-point.h>
#include <keyed_hash.h>
#include <hash.h>
#include "threads/synch.h"

/* States in a thread's life cycle. */
enum thread_status
  {
    THREAD_RUNNING,     /* Running thread. */
    THREAD_READY,       /* Not running but ready to run. */
    THREAD_BLOCKED,     /* Waiting for an event to trigger. */
    THREAD_DYING        /* About to be destroyed. */
  };

/* Thread identifier type.
   You can redefine this to whatever type you like. */
typedef int tid_t;
#define TID_ERROR ((tid_t) -1)          /* Error value for tid_t. */

/* Thread priorities. */
#define PRI_MIN 0                       /* Lowest priority. */
#define PRI_DEFAULT 31                  /* Default priority. */
#define PRI_MAX 63                      /* Highest priority. */
/* define niceness boundary values */
#define NICE_MIN -20
#define NICE_DEFAULT 0
#define NICE_MAX 20
/* A kernel thread or user process.

   Each thread structure is stored in its own 4 kB page.  The
   thread structure itself sits at the very bottom of the page
   (at offset 0).  The rest of the page is reserved for the
   thread's kernel stack, which grows downward from the top of
   the page (at offset 4 kB).  Here's an illustration:

        4 kB +---------------------------------+
             |          kernel stack           |
             |                |                |
             |                |                |
             |                V                |
             |         grows downward          |
             |                                 |
             |                                 |
             |                                 |
             |                                 |
             |                                 |
             |                                 |
             |                                 |
             |                                 |
             +---------------------------------+
             |              magic              |
             |                :                |
             |                :                |
             |               name              |
             |              status             |
        0 kB +---------------------------------+

   The upshot of this is twofold:

      1. First, `struct thread' must not be allowed to grow too
         big.  If it does, then there will not be enough room for
         the kernel stack.  Our base `struct thread' is only a
         few bytes in size.  It probably should stay well under 1
         kB.

      2. Second, kernel stacks must not be allowed to grow too
         large.  If a stack overflows, it will corrupt the thread
         state.  Thus, kernel functions should not allocate large
         structures or arrays as non-static local variables.  Use
         dynamic allocation with malloc() or palloc_get_page()
         instead.

   The first symptom of either of these problems will probably be
   an assertion failure in thread_current(), which checks that
   the `magic' member of the running thread's `struct thread' is
   set to THREAD_MAGIC.  Stack overflow will normally change this
   value, triggering the assertion. */
/* The `elem' member has a dual purpose.  It can be an element in
   the run queue (thread.c), or it can be an element in a
   semaphore wait list (synch.c).  It can be used these two ways
   only because they are mutually exclusive: only a thread in the
   ready state is on the run queue, whereas only a thread in the
   blocked state is on a semaphore wait list. */
struct thread
  {
    /* Owned by thread.c. */
    tid_t tid;                          /* Thread identifier. */
    struct hash_elem hash_elem;         /* For use in the keyed_hash */
    enum thread_status status;          /* Thread state. */
    char name[16];                      /* Name (for debugging purposes). */
    uint8_t *stack;                     /* Saved stack pointer. */
    int priority;                       /* Priority. */
    int niceness;                       /* Thread's nice value, for MLFQS */
    fixed_point recent_cpu;             /* keep track of the current thread's CPU time */
    int64_t thread_wake_tick;           /* The tick the thread should wake up on */
    
    struct list donators;
    struct list_elem donor_elem;        /* donators */
    struct list_elem waiting_elem;      /* For use in timer_sleep */
    struct semaphore thread_sema;
    
    /* Shared between thread.c and synch.c. */
    struct list_elem elem;              /* ready_list and for semaphores */
    struct list_elem allelem;           /* all_list */
    
/* Owned by userprog/process.c. */
#ifdef USERPROG
    uint32_t *pagedir;
    
    struct hash children_hash;
    struct semaphore dying_sema;
    
    int exit_status;
    struct semaphore status_sema;
#endif
    
    /* File descriptor ids will be specific per process. The only fds that
     * aren't specific to a process are stdin and stdout. By having `fd_counter`
     * as a member of thread.h, we won't have to worry about synchronization
     * between different processes. */
    int next_fd;

    struct hash open_files_hash;
    struct list open_files;
    
    /* Owned by thread.c. */
    unsigned magic;                     /* Detects stack overflow. */
  };

/* If false (default), use round-robin scheduler.
   If true, use multi-level feedback queue scheduler.
   Controlled by kernel command-line option "-o mlfqs". */
extern bool thread_mlfqs;

void thread_init (void);
void thread_start (void);

void thread_hash_init (void);

void thread_tick (void);
void thread_print_stats (void);

typedef void thread_func (void *aux);
tid_t thread_create (const char *name, int priority, thread_func *, void *);

void thread_block (void);
void thread_unblock (struct thread *);

struct thread *thread_current (void);
tid_t thread_tid (void);
const char *thread_name (void);

void thread_exit (void) NO_RETURN;
void thread_yield (void);

/* Performs some operation on thread t, given auxiliary data AUX. */
typedef void thread_action_func (struct thread *t, void *aux);
void thread_foreach (thread_action_func *, void *);

/* Like thread_get_priority, but for any thread. */
int
get_effective_priority (struct thread *t);

int thread_get_priority (void);
void thread_set_priority (int);

bool donate_priority_less (const struct list_elem *a,
                           const struct list_elem *b,
                           void* aux);

/* This matches the typedef defined in list.h for a
 * comparator function. */
bool thread_priority_less (const struct list_elem *a,
                           const struct list_elem *b,
                           void* aux);

int highest_ready_priority (void);
void recalc_load_avg (void); //student created
int thread_get_nice (void);
void thread_set_nice (int);
int thread_get_recent_cpu (void);
int thread_get_load_avg (void);
void thread_recalc_recent_cpu (struct thread *t, void *aux);
void thread_recalc_priority (struct thread *t, void *aux);
#endif /* threads/thread.h */
