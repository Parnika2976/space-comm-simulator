# 🚀 Space Communication Packet Simulator

A beginner-friendly C project that simulates satellite communication by managing packets using a circular queue. It allows you to create packets, simulate their transmission, and log the results into a file.

---

## Features

- Create data packets (e.g., Telemetry, Command, Image)
- Simulate packet transmission with 80% success rate
- Store sent/lost packets into a log file (`spacelog.txt`)
- View current queue of waiting/sent/lost packets

---

##Concepts Used

- Circular Queue using arrays
- File handling in C (`fopen`, `fgets`, `fprintf`, `fclose`)
- Random number generation (`rand()`)
- Status tracking using integers

---

## How to Compile and Run

```bash
gcc space_comm_simulator.c -o simulator
simulator      # On Windows
./simulator    # On Linux/macOS
```
---

```markdown
---

## Files

- `space_comm_simulator.c` → Main source code
- `spacelog.txt` → Log file automatically created to store packet transmission results

---

##  Made By

**Parnika Siri Mora**  
Electronics and Communication Engineering student at SNIST  
Passionate about space, communication systems, and building from scratch using C.

---

## Future Improvements

- Add retransmission of lost packets  
- Visualize queue status  
- Use structs and files to mimic a deeper communication protocol  
```
