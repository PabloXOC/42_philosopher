# 42 Philosopher

This project simulates the classical **Dining Philosophers Problem**, a concurrency problem illustrating resource allocation in multithreaded systems. The program is implemented using threads and mutexes to ensure proper synchronization and prevent race conditions.

## Description
The simulation involves:
- A set of philosophers sitting around a circular table.
- Each philosopher alternates between thinking, eating, and sleeping.
- To eat, a philosopher must pick up two forks (one on their left and one on their right).
- Philosophers must avoid starving while ensuring proper usage of shared resources (forks).

The program respects the following constraints:
- Each philosopher is represented by a thread.
- Forks between philosophers are shared and protected using mutexes.
- Proper logging is implemented for each philosopher's actions.
- The simulation ends either when a philosopher dies or when all philosophers have eaten a specified number of times (if provided).

## Features
- **Thread Synchronization:** Each philosopher is managed as a thread.
- **Mutex Protection:** Forks are protected with mutexes to prevent concurrent access.
- **Custom Logging:** All state changes (thinking, eating, sleeping, fork pickup, and death) are logged with timestamps.
- **Dynamic Stopping Conditions:** The simulation can stop based on a configurable number of meals per philosopher or when a philosopher dies.

## Usage
### Compilation
Use the provided `Makefile` to compile the program.
```bash
make
```
This will generate an executable named `philosopher`.


### Execution
Run the program with the following arguments:
```bash
./philosopher number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- `number_of_philosophers`: Number of philosophers (and forks).
- `time_to_die`: Time (in milliseconds) a philosopher can survive without eating.
- `time_to_eat`: Time (in milliseconds) it takes for a philosopher to eat.
- `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): If provided, the simulation ends when all philosophers have eaten this many times. If omitted, the simulation runs until a philosopher dies.

### Example
```bash
./philosopher 5 800 200 150
```
Simulates 5 philosophers with:
- 800 ms time to die.
- 200 ms time to eat.
- 150 ms time to sleep.

### Cleaning Up
Use the following commands for cleanup:

- `make clean`: Remove object files.
- `make fclean`: Remove object files and the executable.
- `make re`: Rebuild the library from scratch.


## Logging Format
Each state change is logged in the following format:
```plaintext
[timestamp_in_ms] X has taken a fork
[timestamp_in_ms] X is eating
[timestamp_in_ms] X is sleeping
[timestamp_in_ms] X is thinking
[timestamp_in_ms] X died
```
- `timestamp_in_ms`: Time since the start of the simulation (in milliseconds).
- `X`: Philosopher number (1 to `number_of_philosophers`).


## Timing Accuracy

The standard usleep function has limited accuracy due to system scheduling and potential delays under high system load. To address this limitation, I implemented a custom timing mechanism that ensures significantly more precise delays for philosopher actions. This improvement ensures better simulation consistency and adherence to specified timing constraints, regardless of system conditions. Program is still subject to error from gettimeofday function.

## License
This project is licensed under the MIT License.

## Author
[Your Name](https://github.com/yourgithubusername)

