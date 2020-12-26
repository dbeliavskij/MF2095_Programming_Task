# MF2095_Programming_Task

A program is written as part of the C programming for embedded systems course

# Program description
Program that keeps a record of measured and reported temperatures over time, according to the following requirements:
- The program obtains the temperatures to log via standard input, temperature input standart: “T<some number>”.
- The log is expected to automatically expand if initial log size (set by user) is full.
- Program is expected to perform different functions according to input command
  
Additional requirements propose that program in the future might need to receive temperature measurements over a network, instead of via standard input. In preparation for that, the standard input format used is similar to a network message, which is packaged as a 32‐bit word according to the following structure:
| Bit nr. | 31-29 | 28-26 | 25-0 |
|:---:|:---:|:---:|:---:|
| | Reserved | Type | Data|

Available type of messages:

| Value | Function |
|:---:|:---:|
| 000 | Represents a temperature value |
| 001 | Represents a humidity value |
| 010 | Output the average of the temperature values measured so far |
| 011 | Output the minimum temperature values so far. |
| 100 | Output the maximum temperature values so far |
| 101 | Output a list of all temperature values recorded so far |
| 110 | Quit the program |
| 111 | Cotrols a size of the log, log can be expanded afterwards manually or will expand automatically |


