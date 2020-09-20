# phipsshell - a simple bash-like shell written in C++

## About
I had to write a shell for an uni project a few semesters ago. I did this
in C and the outcome was quite interesting. I learned a lot about `pipes`, `file
descriptors`, `fork`, `exec`, and some other `UNIX` facilities. I wanted to revive
this project and open source it to keep the learnings in my memory and to
share them with other people facing this task. So I took the code from then and
rewrote ugly parts in C++.

**Focus is educational and for personal experience - not a production-ready shell!**

## Code and code quality
I'm not an experienced C++ developer. My testing so far (valgrind) shows I 
have no memory leaks and the overall code quality looks at least "okay" to 
me. At least the important parts! The parsing and validation stuff is not 
really solid, tho. But I spend some time into making the actual execution
and Pipe creation + handling nice.

**Important parts of code**: See `action.cpp: action_command()` and `pipe.class.cpp: Pipe()`.

## Functionality
This shell focuses on **proper user input**! Validation is only very coarse-grained and 
definitely not bullet-proof! The focus here is on understanding pipes and not in writing
a good parser. **Only single spaces** are allowed and **no quote marks!**
`echo "foo  bar"` won't work.

Valid inputs are (subset of bash):
#### simple commands
- `cat file.txt`
- `/usr/bin/cat file.txt`
- `./mybin file.txt`

#### pipes
- `cat file.txt | wc -l`

#### I/O redirection
- `cat < in.txt`
- `cat in.txt > out.txt`
- `cat < in.txt | wc -l > out.txt`
- `cat < in.txt > out.txt` **doesn't work because my whole parsing code is not that good**

#### all in combination
- `cat in.txt | grep -i foo | wc -l > out.file`

## How to use/build phipsshell?
Runs on UNIX systems, like Linux distributions or Mac OS.
#### Linux (Debian, Ubuntu)
- `$ sudo apt install libreadline-dev`
- `$ make && ./phipsshell`
#### Mac OS
- `$ brew install readline` (installs only the runtime library, not the header files; therefore the header files are in ./include)
- `$ make && ./phipsshell`

## Important parts of code
See `action.cpp: action_command()` and `pipe.class.cpp: Pipe()`.

## Why Makefile and CMakeLists.txt?
At the begin there was only the makefile. Because I wanted to use Jetbrains CLion I
also added a CMakeLists.txt. Both files works fine. I keep the Makefile because I 
think it's 'nice' and I don't want to loose it.

## Dependencies
*phipsshell* uses [libreadline](https://tiswww.case.edu/php/chet/readline/rltop.html).
Readline is distributed under a [GPL v3 License](https://www.gnu.org/licenses/gpl-3.0.html).
This repository contains a few header files (copied from the original source) in order to
support compiling on MacOS. That is because `brew install readline` doesn't install header
files.

## Important Keywords for used UNIX facilities
- pipes, file descriptors, waitpid, WNOHANG, dup2

