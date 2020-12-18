# Critical-Section-Problem
This project simulates one of the classical synchronization problems in order to see how the (semi) critical section problem could be implemented using binary and counting semaphores.

5 processes are characterized by 3 readers and 2 writers.
Up to two reader processes can be inside their critical section without any writer process. For writer process to go into its critical section, it checks whether there is any reader or writer process is in the critical section.

Critical section in this problem is reading shared data buffer for reader and updating shared data buffer for writer processes.

* When reader or writer enters its critical section, it reports whether there are any reader(s) or writer(s) other than itself.
* It prints out the data you read or write when you implement real buffer.
* It prints out “Panic Messages” when the rules behind this semi critical section problem are not observed.

In the main program, it runs the random number generator function to choose process to execute. The chosen process starts (resumes) execution and after one instruction, it will be returned. (It forces each process run exactly one instruction then returns and waiting for its turn.)

# Skill

C++

# Output Images

<img width="671" alt="Screen Shot 2020-12-18 at 3 06 31 PM" src="https://user-images.githubusercontent.com/34990882/102656880-a3ff5a00-4142-11eb-8c99-054818d7daa7.png">
