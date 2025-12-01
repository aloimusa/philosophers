# philosophers
works with tight timings

![demo](https://i.imgur.com/FNAP1Eq.gif)
## what is this

42 project.  the dining philosophers problem but make it thread-safe. 

basically philosophers sit at a table, they need two forks to eat, and they die if they don't eat in time. classic synchronization problem. 

## implementation

- pthreads for threading
- mutexes for fork synchronization
- precise timing with gettimeofday
- no data races, no deadlocks (hopefully)

built this to understand multithreading better.  learned a lot about race conditions the hard way.  
