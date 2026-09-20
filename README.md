*This project has been created as part of the 42 curriculum by fasaravi.*

## Description

**Philosophers** is an introduction to concurrent programming in C through the classic **Dining Philosophers Problem**.

A number of philosophers sit around a circular table. Between every pair of philosophers there is one fork, so the number of forks is equal to the number of philosophers. Each philosopher repeatedly alternates between three states:

- **eating**
- **sleeping**
- **thinking**

To eat, a philosopher must hold both adjacent forks. Since forks are shared resources, philosophers must coordinate their access without communicating directly with each other.

## Program arguments

The executable has the following interface:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning |
|---|---|
| `number_of_philosophers` | Number of philosophers and forks. |
| `time_to_die` | Maximum time, in milliseconds, since the beginning of the simulation or the philosopher's last meal before the philosopher dies. |
| `time_to_eat` | Time, in milliseconds, spent eating while holding both forks. |
| `time_to_sleep` | Time, in milliseconds, spent sleeping. |
| `number_of_times_each_philosopher_must_eat` | Optional. If every philosopher reaches this number of meals, the simulation stops. |

If the optional argument is omitted, the simulation ends when a philosopher dies.


## Instructions


### Compile

```bash
make
```

Available targets:

```bash
make
make all
make clean
make fclean
make re
```

### Run

```bash
./philo 4 800 200 200
```

With a meal target:

```bash
./philo 4 800 200 200 7
```

## Output

Every state change is printed using the format required by the subject:

```
timestamp_in_ms philosopher_id action
```

Possible actions are:

```
has taken a fork
is eating
is sleeping
is thinking
died
```

Example:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

Because the execution order is controlled by the operating-system scheduler, the exact ordering of messages may differ between runs.


## Resources

### Dining Philosophers and 42

- [Philosophers 42 Guide — The Dining Philosophers Problem (Medium)](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
- [42 Cursus Guide — Philosophers](https://42-cursus.gitbook.io/guide/3-rank-03/philosophers)
- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

### Threads and synchronization

- [Threads, mutex et programmation concurrente en C — Codequoi](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)
- [Introduction to Threads — YouTube](https://www.youtube.com/watch?v=LOfGJcVnvAk)
- [pthreads(7) — Linux man-pages](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [pthread_create(3) — Linux man-pages](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [pthread_mutex_lock(3p) — POSIX/Linux manual page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)


### Further reading

- [Créer et tuer des processus fils en C — Codequoi](https://www.codequoi.com/creer-et-tuer-des-processus-fils-en-c/)

The process article is useful background material for understanding the distinction between processes and threads and is especially relevant to process-based variants of the problem.


## Use of AI

AI tools were used as a **supporting learning and review tool**, not as a substitute for understanding the implementation.

They were used to:

- discuss and clarify concurrency concepts such as threads, mutexes, deadlocks, starvation, and data races;
- review implementation ideas and help reason about synchronization behavior;
- assist with debugging and code review during development;
- help organize and improve the technical documentation in this README.

All generated suggestions were reviewed against the project subject, the program's actual behavior, and external documentation before being retained.

## Implementation Personal Notes

### Main data structures

The simulation is organized around two main structures.

#### `t_state`

`t_state` owns the global simulation context:

- parsed timing parameters;
- the philosopher array;
- the fork mutex array;
- the common simulation start time;
- start/finish state;
- synchronization counters;
- the print mutex;
- the simulation-state mutex;
- the fork gatekeeper.

There are **no global variables**.

#### `t_philo`

Each philosopher stores:

- its identifier;
- its `pthread_t`;
- pointers to its left and right fork mutexes;
- a mutex protecting its meal-related state;
- its meal count;
- the timestamp of its last meal;
- scheduling information used by the fork gatekeeper;
- a pointer to the shared `t_state`.

## Synchronization strategy

The implementation uses several independent synchronization mechanisms, each with a specific responsibility.

### 1. One mutex per fork

Every physical fork is represented by a `pthread_mutex_t`.

A philosopher must lock both of its adjacent fork mutexes before eating, ensuring that a fork can never be held by two philosophers at the same time.

### 2. Fork gatekeeper

In addition to the fork mutexes, the implementation uses a small scheduling layer named `t_fork_gatekeeper`.

The gatekeeper:

- keeps a logical availability state for every fork;
- protects that state with its own mutex;
- allows a philosopher to reserve both adjacent forks only when both are available;
- tracks philosophers waiting to eat;
- gives precedence to neighboring philosophers that have been waiting longer;
- uses deterministic tie-breaking when requests have the same timestamp.

The gatekeeper does **not** replace the fork mutexes. The forks themselves are still protected individually by mutexes; the gatekeeper only coordinates reservation before the physical locks are taken.

This reduces unfair repeated acquisition and helps avoid starvation scenarios.

### 3. Consistent fork locking order

After successfully reserving its two forks, a philosopher locks the corresponding mutexes in a consistent order.

The lower-addressed fork mutex is locked first and the other one second.

Using a common resource ordering removes the circular-wait pattern responsible for the classical dining-philosophers deadlock.

### 4. Synchronized simulation start

Threads are created before the simulation clock starts.

Each philosopher:

1. reaches a barrier-like waiting phase;
2. increments the shared `ready_count`;
3. waits for the `started` flag.

The main thread waits until every philosopher is ready, initializes a common `start_time`, initializes the first meal timestamps and requests, and finally releases all philosopher threads together.

This avoids giving earlier-created threads an artificial timing advantage.

### 5. Meal-state protection

Each philosopher owns an `eat_lock` mutex protecting values such as:

- `eat_last`;
- `eat_count`.

The monitor and philosopher thread may access these fields concurrently, so they must be synchronized to avoid data races.

### 6. Monitor

The main thread acts as the simulation monitor after all philosopher threads have been started.

It repeatedly checks:

- whether a philosopher exceeded `time_to_die`;
- whether all philosophers reached the optional meal target.

If either stop condition is reached, the shared `finished` state is set and the philosopher threads terminate their routines.

### 7. Serialized output

All simulation messages are protected by `lock_print`.

This prevents output produced by different threads from overlapping and also coordinates the final death message with the simulation stop state.

### 8. Single-philosopher case

With only one philosopher there is only one fork.

The philosopher can take that fork but can never obtain a second one, so the implementation handles this case separately and waits until the monitor detects the philosopher's death.


## Execution flow

```text
main
 |
 +-- parse arguments
 |
 +-- initialize state
 |    |
 |    +-- allocate philosophers
 |    +-- allocate fork mutexes
 |    +-- initialize shared locks
 |    +-- initialize philosopher meal locks
 |    +-- initialize gatekeeper
 |
 +-- create philosopher threads
 |    |
 |    +-- each thread waits at the start barrier
 |
 +-- start simulation
 |    |
 |    +-- wait until all threads are ready
 |    +-- set common start time
 |    +-- initialize meal timestamps
 |    +-- release philosopher threads
 |
 +-- monitor
 |    |
 |    +-- check deaths
 |    +-- check optional meal target
 |
 +-- join all threads
 |
 +-- destroy mutexes and free allocated memory
```

Each philosopher then follows approximately this cycle:

```text
reserve forks
     |
lock both fork mutexes
     |
    eat
     |
unlock both forks
     |
   sleep
     |
   think
     |
    repeat
```
