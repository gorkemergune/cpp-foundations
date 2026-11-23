# C++ Foundations

> An open notebook for learning C++ from scratch — lecture notes, code examples, labs, and projects from CSE 211 at Yeditepe University, kept public for the students who come after.

## Start Here

| | What it is | Open |
| --- | --- | --- |
| 🧪 **Lab Camp** | 12 weeks of CSE 211: 46 PDF labs, 11 challenge sets, 6 small projects — each with starter files, tests and step-by-step solutions | [lab-camp/README.md](lab-camp/README.md) · [first lab (PDF)](lab-camp/week01/L01-vector-first-steps/L01-vector-first-steps.pdf) |
| 📦 **Course materials** | the CSE 211 slides with a topic/slide index, labworks, assignments, practice labs, lecture code and midterm notes — every question with a compiled, tested solution | [materials/README.md](materials/README.md) · [slide index](materials/slides/README.md) |
| 🎯 **Midterm camp** | 30 questions on linked lists, stacks and queues with the same test runner | [practice/midterm-camp/README.md](practice/midterm-camp/README.md) |

<details>
<summary><b>How do I start? (click)</b></summary>

1. Install a C++ compiler (see [Getting Started](#getting-started)).
2. Open the [Lab Camp index](lab-camp/README.md) and expand **Week 1**.
3. Read the first PDF, write your code in `lab01.cpp`, then run the tests from the `lab-camp` folder: `.\run.ps1 L01` (PowerShell) or `./run.sh L01` (Git Bash).
4. When a topic needs the original course files (a slide, a labwork, an assignment), every PDF links to them under `materials/`.

</details>

## Overview

This repository is where I start learning **C++** from the ground up. It is the sister repository to [c-foundations](https://github.com/gorkemergune/c-foundations), and it continues the same idea: a public, continuously updated learning log built to serve both as a personal record of my progress and as a study aid for future students.

The repository is at an early stage. Right now it collects the weekly lecture notes, worked examples, labs, and projects that make up the course, and it will keep growing as I move through the material.

---

## Learning Path

This repository is the second step in a broader undergraduate learning path focused on low-level and systems programming.

| Course               | Institution         | Status      | Repository                                                    |
| -------------------- | ------------------- | ----------- | ------------------------------------------------------------- |
| Programming with C   | Yeditepe University | Completed   | [c-foundations](https://github.com/gorkemergune/c-foundations) |
| Programming with C++ | Yeditepe University | In progress | this repository                                               |

---

## Repository Structure

```
cpp-foundations/
├── lab-camp/          # 12-week lab camp: weekly PDFs, starter files, tests, solutions
│   ├── week01 … week12/   # labs L01–L46, 11 challenge sets (C01–C12), projects P01–P06
│   ├── solutions/         # reference solutions
│   └── run.ps1, run.sh    # compile and test:  ./run.ps1 L01
├── materials/         # CSE 211 slides (with a topic/slide index), labworks, assignments, practice labs,
│                      # lecture code, midterm notes, C++ reading notes; a tested solution for every question
├── practice/
│   └── midterm-camp/  # 30-question midterm camp (linked list, stack, queue) with tests
└── README.md
```

---

## Getting Started

You only need a C++ compiler to run everything here. A single-file example can be compiled and run in two commands.

### Using g++ or clang++

```bash
g++ file_name.cpp -o program
./program
```

The examples target **C++11 or newer**. If your compiler defaults to an older standard, ask for a modern one explicitly:

```bash
g++ file_name.cpp -std=c++17 -o program
./program
```

### On Windows

[MinGW-w64](https://www.mingw-w64.org/) and [MSYS2](https://www.msys2.org/) both provide `g++` and work with the commands above. Everything also works out of the box with Visual Studio Code and the official C/C++ extension. On Windows the output file is `program.exe`, run it with `./program.exe`.

### Recommended Flags While Learning

- `-Wall -Wextra` — enable most warnings
- `-std=c++17` — use a modern standard (`-std=c++11` if a chapter requires it)
- `-g` — include debug symbols for use with `gdb`
- `-fsanitize=address,undefined` — catch memory errors and undefined behavior early (GCC/Clang)

---

## Resources

A short list of materials I have found most useful while getting started with C++.

- [cppreference.com](https://en.cppreference.com/) — the authoritative reference for the language and standard library
- [learncpp.com](https://www.learncpp.com/) — a thorough, beginner-friendly tutorial series
- [W3Schools — C++ Tutorial](https://www.w3schools.com/cpp/) — a quick first pass on syntax
- [The Cherno — C++ Series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb) — clear, practical video explanations

---

## Academic Integrity and Disclaimer

All notes and my own code here reflect my understanding at the time of writing and should be read as a learning log, not a canonical reference. The material is shared strictly for educational reference. It is not intended to be copied into submitted coursework; students are expected to solve their assignments themselves and to use this repository only as a study aid.

---

_This repository is a living document. It is updated continuously as new topics, labs, and projects are covered._
