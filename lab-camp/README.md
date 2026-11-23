# CSE 211 Lab Camp · C++ and Data Structures

A 12-week, PDF-based study camp for CSE 211: **46 labs**, **11 challenge sets** (LeetCode medium/hard) and **6 small projects** (60–100 lines each). Every lab is built like a 30–50 minute university lab session and comes with starter files and ready-made tests.

> **Quick start:** open [Week 1 → Lab 01](week01/L01-vector-first-steps/L01-vector-first-steps.pdf), write your code in `lab01.cpp`, then run `.\run.ps1 L01`.

<table>
<tr>
<td><b>📚 46 labs</b><br>one per study day, 3–4 per week; the 4th lab of a week is usually timed</td>
<td><b>🧠 11 challenge sets</b><br>three LeetCode medium/hard problems per topic, with hints and full solutions</td>
<td><b>🛠️ 6 projects</b><br>60–100 lines of your own code that turn into a real, runnable program</td>
</tr>
</table>

## Contents

Click a heading to jump there. Inside [Weekly index](#weekly-index), click a week to expand its table.

1. [What is inside one lab?](#what-is-inside-one-lab)
2. [How do I work on a lab?](#how-do-i-work-on-a-lab)
3. [Weekly index](#weekly-index) — every PDF, linked
4. [Midterm topics: where each one is practised](#midterm-topics-where-each-one-is-practised)
5. [Course labworks and assignments: where they are](#course-labworks-and-assignments-where-they-are)
6. [The course's own function names](#the-courses-own-function-names)
7. [Review plan](#review-plan)
8. [Folder layout and building the PDFs](#folder-layout-and-building-the-pdfs)

## What is inside one lab?

The camp starts C++ from scratch with `std::vector` and follows the order of the course: vector → arrays → strings → linked list → stack → queue → (midterm mocks) → graph → tree → hash → heap. The course's own classes and special functions (`pushToStack`, `popFromStack`, `dequeue(out)`, `addToTail`, `heapRebuild` …) are used in the week they are needed, with the exact signatures from the slides and the course archive. Every question of the labworks, the assignments and the midterm notes appears as part of some lab.

Each PDF has the same structure:

| Part | Language | What you get |
| --- | --- | --- |
| **Lab question** (first pages) | English | problem statement, scenario, the given header with the exact signatures, rules, constraints, a worked example, the test table |
| **Explanation** (after the banner) | Turkish | what the question really asks, “ask yourself” questions, step-by-step drawings of the data structure |
| **Reference solution** (next page) | Turkish notes | the solution code, why this approach (allowed functions, cost), an alternative and which lab rule it would break |
| **Memory variant** (last box) | — | a short variant to write from memory 48 hours later |

<details>
<summary><b>Question IDs inside a lab (click)</b></summary>

| ID | Meaning |
| --- | --- |
| **A, B** | short warm-up exercises |
| **M** (or M1, M2 …) | the main problem(s) |
| **X** | optional LeetCode / GeeksforGeeks adaptation |
| **V** | memory variant, to write without looking |
| **A, B, C** in timed labs and mocks | the parts of the exam, with points |

The summary line of the test runner counts only the required questions.

</details>

<details>
<summary><b>L, C and P: the three kinds of PDFs (click)</b></summary>

| Prefix | Kind | When |
| --- | --- | --- |
| **L** | daily lab | 3–4 per week; the “Day” column gives the order |
| **C** | challenge set | after the week's labs; give every problem at least 25 minutes before you read the hints |
| **P** | small project | after the challenge set; a ready `main_demo.cpp` turns your class into a program (the build command is on its first line) |

</details>

## How do I work on a lab?

1. Open the lab's PDF and solve the **English lab question** first.
2. The first weeks have a warm-up program: write its output on paper, then compile it (`g++ -std=c++17 -Wall warmup.cpp -o warmup.exe`).
3. In `labXX.cpp`, delete the `TODO();` line of a function and write its body. Do not edit `labXX.h`.
4. Run the tests. Every row of the PDF's test table is a test; most questions then run 200 random inputs.
5. When the tests are green (or your time is up), read the Turkish part. The reference solution starts on the next page.

```powershell
cd lab-camp
.\run.ps1                 # list the labs
.\run.ps1 L01             # every question of Lab 01
.\run.ps1 L01 L01-M       # a single question
.\run.ps1 L01 -Solution   # the same tests against the reference solution
.\run.ps1 C09             # a challenge set;  .\run.ps1 P04  a project
```

In Git Bash: `./run.sh L01`, `./run.sh L01 L01-M`, `./run.sh L01 --solution`

<details>
<summary><b>What the test output means (click)</b></summary>

| Mark | Meaning |
| --- | --- |
| `✓ 206/206` | every check passed |
| `✗ 3/8` | some rows are wrong; the input, the expected value and your result are printed |
| `· not written yet` | the `TODO();` is still there |
| `· needs L03-A first` | your function calls another function that is not written yet |
| `💥` | crash: index outside the array, null pointer or a deleted node |
| `⏱` | did not finish in 3 seconds, most likely an infinite loop |

</details>

## Weekly index

Move on to the next topic after you have ticked the checklist at the end of the previous week's last PDF. The “Course material” line of each week links into [`../materials`](../materials/README.md); every PDF also names the exact slide numbers.

<details>
<summary><b>Week 1 · <code>std::vector</code></b> — L01–L04, C01</summary>

Course material: [06-arrays-and-vectors](../materials/slides/06-arrays-and-vectors.ppt), [05-functions](../materials/slides/05-functions.ppt) (reference parameters), C++ basics in [cpp-reference](../materials/cpp-reference/).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L01 | 1 | First Steps with `std::vector`: Running Totals | 35 min | `std::vector<int>`, `push_back`, `size`, `[]`, range-for, compiling a C++ file, passing a vector by value | [LC 1480](https://leetcode.com/problems/running-sum-of-1d-array/) · [LC 1929](https://leetcode.com/problems/concatenation-of-array/) | [📄 PDF](week01/L01-vector-first-steps/L01-vector-first-steps.pdf) · [📁 files](week01/L01-vector-first-steps/) |
| L02 | 2 | References: Removing and Inserting Inside a Vector | 45 min | pass by value vs. `&` vs. `const&`, `int&` in range-for, `size` vs. `capacity`, `reserve`/`resize`, `at()` vs. `[]`, shifting elements by index | [LC 27](https://leetcode.com/problems/remove-element/) | [📄 PDF](week01/L02-references-and-in-place-edits/L02-references-and-in-place-edits.pdf) · [📁 files](week01/L02-references-and-in-place-edits/) |
| L03 | 3 | Two Indexes: Reversing Alternate Groups of Three | 45 min | two indexes moving toward each other, `std::swap`, inclusive ranges, loop bounds for groups, the `size_t` underflow trap | [LC 344](https://leetcode.com/problems/reverse-string/) | [📄 PDF](week01/L03-two-index-reversal/L03-two-index-reversal.pdf) · [📁 files](week01/L03-two-index-reversal/) |
| L04 | 4 | Timed Lab: Compacting and Rotating a Vector | 50 min, timed | everything from Labs 01–03: `const&` vs. `&`, building a new vector, in-place index work, `%` for wrapping indexes, two-index reversal | [LC 283](https://leetcode.com/problems/move-zeroes/) · [LC 189](https://leetcode.com/problems/rotate-array/) | [📄 PDF](week01/L04-timed-lab-rotate/L04-timed-lab-rotate.pdf) · [📁 files](week01/L04-timed-lab-rotate/) |
| C01 | C | Thinking Problems on Vectors | 60–90 min | prefix/suffix products, two pointers with a proof, in-place index placement (cyclic sort) | [LC 238](https://leetcode.com/problems/product-of-array-except-self/) · [LC 11](https://leetcode.com/problems/container-with-most-water/) · [LC 41](https://leetcode.com/problems/first-missing-positive/) | [📄 PDF](week01/C01-challenge-vector/C01-challenge-vector.pdf) · [📁 files](week01/C01-challenge-vector/) |

</details>

<details>
<summary><b>Week 2 · C arrays, <code>std::array</code>, pointers</b> — L05–L08, C02</summary>

Course material: [06-arrays-and-vectors](../materials/slides/06-arrays-and-vectors.ppt), [07-pointers](../materials/slides/07-pointers.ppt).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L05 | 1 | C-Style Arrays: Passing an Array and Its Length | 40 min | `int a[N]`, initialization, `sizeof`, array-to-pointer decay, passing `(const int a[], int n)`, `int&` output parameters, returning `bool` for “no answer” | [GfG Min and Max in Array](https://www.geeksforgeeks.org/problems/find-minimum-and-maximum-element-in-an-array4428/1) (L05-X) · [GfG Second Largest](https://www.geeksforgeeks.org/problems/second-largest3735/1) (L05-V) | [📄 PDF](week02/L05-c-style-arrays/L05-c-style-arrays.pdf) · [📁 files](week02/L05-c-style-arrays/) |
| L06 | 2 | std::array and Your First Function Template | 45 min | `std::array<T, N>`, `.size()`, `.at()`, copying arrays, `struct` return values, function templates `template <typename T>` and `template <std::size_t N>`, why templates live in headers | [LC 1550](https://leetcode.com/problems/three-consecutive-odds/) (L06-X) | [📄 PDF](week02/L06-std-array-and-templates/L06-std-array-and-templates.pdf) · [📁 files](week02/L06-std-array-and-templates/) |
| L07 | 3 | Pointers Into Arrays and 2-D Arrays | 45 min | pointer arithmetic (`p + k`, `p - q`, `*p`, `p++`), half-open ranges `[begin, end)`, `nullptr`, 2-D arrays `int m[R][C]` and how they are passed | [LC 1572](https://leetcode.com/problems/matrix-diagonal-sum/) (M1) · [LC 867](https://leetcode.com/problems/transpose-matrix/) (L07-X) | [📄 PDF](week02/L07-pointers-into-arrays/L07-pointers-into-arrays.pdf) · [📁 files](week02/L07-pointers-into-arrays/) |
| L08 | 4 | Timed Lab: Merging Sorted Arrays | 50 min, timed | two-index merge, filling from the back, intersection of sorted ranges, C arrays and `std::vector` in one lab | [LC 88](https://leetcode.com/problems/merge-sorted-array/) (Part B, same signature) · [LC 977](https://leetcode.com/problems/squares-of-a-sorted-array/) (L08-X) | [📄 PDF](week02/L08-timed-lab-merge/L08-timed-lab-merge.pdf) · [📁 files](week02/L08-timed-lab-merge/) |
| C02 | C | Thinking Problems on Matrices | 60–90 min | boundary-shrinking loops, rotation as transpose + reverse, using the input itself as marker storage | [LC 54](https://leetcode.com/problems/spiral-matrix/) · [LC 48](https://leetcode.com/problems/rotate-image/) · [LC 73](https://leetcode.com/problems/set-matrix-zeroes/) | [📄 PDF](week02/C02-challenge-matrix/C02-challenge-matrix.pdf) · [📁 files](week02/C02-challenge-matrix/) |

</details>

<details>
<summary><b>Week 3 · <code>std::string</code>, <code>getline</code>, classes and <code>.h/.cpp</code></b> — L09–L12, C03, P01</summary>

Course material: [01-intro-to-cpp](../materials/slides/01-intro-to-cpp.ppt), [02-classes-and-objects](../materials/slides/02-classes-and-objects.ppt), [2017 AS4 calendar classes](../materials/assignments/2017-spring/as4-calendar-classes/).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L09 | 1 | Strings: Indexing, find and substr | 40 min | `std::string` vs. `char[]`, `+=`, `s[i]`, `find`/`npos`, `substr`, comparing strings, `<cctype>` with `unsigned char` | [LC 125](https://leetcode.com/problems/valid-palindrome/) (M2) · [LC 344](https://leetcode.com/problems/reverse-string/) (L09-X) | [📄 PDF](week03/L09-strings/L09-strings.pdf) · [📁 files](week03/L09-strings/) |
| L10 | 2 | Reading Lines: getline and istringstream | 45 min | `cin >> x` vs. `getline`, the leftover newline, `in.ignore`, `std::istringstream` to split a line, testing `if (in >> x)`, `std::istream&` parameters | [LC 2042](https://leetcode.com/problems/check-if-numbers-are-ascending-in-a-sentence/) (L10-X) | [📄 PDF](week03/L10-reading-lines/L10-reading-lines.pdf) · [📁 files](week03/L10-reading-lines/) |
| L11 | 3 | Header and Source: Your First Class | 45 min | `class`, `public`/`private`, constructor with initializer list, `const` member functions, `ClassName::member` definitions in a `.cpp`, include guards, compiling several files, objects passed by reference | [LC 58](https://leetcode.com/problems/length-of-last-word/) (L11-X) | [📄 PDF](week03/L11-header-and-source-class/L11-header-and-source-class.pdf) · [📁 files](week03/L11-header-and-source-class/) |
| L12 | 4 | Timed Lab: Word Processing | 50 min, timed | everything from Labs 09–11: `istringstream`, building strings with `+=`, runs of equal characters, reference outputs | [LC 151](https://leetcode.com/problems/reverse-words-in-a-string/) (Part A) · [LC 14](https://leetcode.com/problems/longest-common-prefix/) (L12-X) | [📄 PDF](week03/L12-timed-lab-words/L12-timed-lab-words.pdf) · [📁 files](week03/L12-timed-lab-words/) |
| C03 | C | Thinking Problems on Strings | 60–90 min | sliding window with a “last seen” table, expanding around a centre, careful parsing with overflow checks | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · [LC 5](https://leetcode.com/problems/longest-palindromic-substring/) · [LC 8](https://leetcode.com/problems/string-to-integer-atoi/) | [📄 PDF](week03/C03-challenge-strings/C03-challenge-strings.pdf) · [📁 files](week03/C03-challenge-strings/) |
| P01 | P | Gradebook: Read, Validate, Report | 90–120 min | a class over a `std::vector` of structs, input validation with `istringstream`, `getline` loops over a stream, `const` member functions, formatted output with `<iomanip>`, building a small command-line program from tested parts | — | [📄 PDF](week03/P01-gradebook-project/P01-gradebook-project.pdf) · [📁 files](week03/P01-gradebook-project/) |

</details>

<details>
<summary><b>Week 4 · Pointers and singly linked lists</b> — L13–L16, C04</summary>

Course material: [08-linked-lists](../materials/slides/08-linked-lists.ppt), [Labwork 1](../materials/labworks/lw1-singly-linked-list/), [Practice Lab 2](../materials/practice-labs/pl2-linked-list/), [2021 A1](../materials/assignments/2021-fall/a1-sll-sort-swap/), [2017 AS1](../materials/assignments/2017-spring/as1-grades-linked-list/).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L13 | 1 | Paper Lab: Tracing Nodes and Arrows | 40 min | `struct Node` with a constructor, `new` / `delete`, `nullptr`, `->`, walking a list, reading `next` before `delete`, `Node*&` to change the caller's head | [LC 1290](https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/) (L13-X) | [📄 PDF](week04/L13-paper-lab-nodes/L13-paper-lab-nodes.pdf) · [📁 files](week04/L13-paper-lab-nodes/) |
| L14 | 2 | pushBack(Node*& head, int value): Positions in a List | 45 min | `Node*` vs. `Node*&` parameters, the empty-list case, walking to the node before a position, unlink then `delete`, returning a new head vs. changing it by reference | [GfG Linked List End Insertion](https://www.geeksforgeeks.org/problems/linked-list-insertion-1587115620/1) (L14-X) | [📄 PDF](week04/L14-pushback-and-node-ref/L14-pushback-and-node-ref.pdf) · [📁 files](week04/L14-pushback-and-node-ref/) |
| L15 | 3 | The Course Class IntSLList | 50 min | a list class with `head` and `tail`, keeping both correct after every operation, preconditions (`isEmpty()` before `delete…`), destructor, `const` member functions | [LC 203](https://leetcode.com/problems/remove-linked-list-elements/) (L15-X, on IntSLList) | [📄 PDF](week04/L15-course-class-intsllist/L15-course-class-intsllist.pdf) · [📁 files](week04/L15-course-class-intsllist/) |
| L16 | 4 | Timed Lab: Reverse, Remove, Find the Middle | 50 min, timed | three-pointer reversal, removal with a predecessor, slow/fast pointers | [LC 206](https://leetcode.com/problems/reverse-linked-list/) (A) · [LC 876](https://leetcode.com/problems/middle-of-the-linked-list/) (C) · [LC 234](https://leetcode.com/problems/palindrome-linked-list/) (L16-X) | [📄 PDF](week04/L16-timed-lab-reverse-remove/L16-timed-lab-reverse-remove.pdf) · [📁 files](week04/L16-timed-lab-reverse-remove/) |
| C04 | C | Thinking Problems on Linked Lists | 60–90 min | dummy (sentinel) head node, carry propagation, a gap of n between two pointers, split + reverse + merge | [LC 2](https://leetcode.com/problems/add-two-numbers/) · [LC 19](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) · [LC 143](https://leetcode.com/problems/reorder-list/) | [📄 PDF](week04/C04-challenge-linked-list/C04-challenge-linked-list.pdf) · [📁 files](week04/C04-challenge-linked-list/) |

</details>

<details>
<summary><b>Week 5 · Doubly and circular linked lists</b> — L17–L20, C05, P02</summary>

Course material: [08-linked-lists](../materials/slides/08-linked-lists.ppt), [Labwork 2](../materials/labworks/lw2-doubly-linked-list/), [term project (text editor)](../materials/assignments/2021-fall/term-project-text-editor/).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L17 | 1 | The Doubly Linked List Template | 50 min | class templates (`template <class T>` before every member definition), `prev` and `next` kept consistent, `O(1)` removal at both ends, unlinking a node from the middle, in-place reversal | [LC 707](https://leetcode.com/problems/design-linked-list/) (same operations, as practice on the site) | [📄 PDF](week05/L17-doubly-linked-list-template/L17-doubly-linked-list-template.pdf) · [📁 files](week05/L17-doubly-linked-list-template/) |
| L18 | 2 | Delete the Middle Node | 40 min | slow/fast pointers with an offset, stopping one node before a target, unlink + `delete`, the 0-, 1- and 2-node edge cases | [LC 2095](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/) (M and L18-X) | [📄 PDF](week05/L18-delete-middle-node/L18-delete-middle-node.pdf) · [📁 files](week05/L18-delete-middle-node/) |
| L19 | 3 | A Circular List Kept by last | 45 min | circular lists, keeping only `last`, `do … while` for one full round, the one-node circle (`last->next == last`), `Node*& last` | — | [📄 PDF](week05/L19-circular-list-last/L19-circular-list-last.pdf) · [📁 files](week05/L19-circular-list-last/) |
| L20 | 4 | Timed Lab: Merging and Cleaning Lists | 50 min, timed | deleting in place without moving forward, merging by relinking with a dummy node, Floyd's cycle detection | [LC 83](https://leetcode.com/problems/remove-duplicates-from-sorted-list/) (A) · [LC 21](https://leetcode.com/problems/merge-two-sorted-lists/) (B) · [LC 141](https://leetcode.com/problems/linked-list-cycle/) (C) | [📄 PDF](week05/L20-timed-lab-merge-lists/L20-timed-lab-merge-lists.pdf) · [📁 files](week05/L20-timed-lab-merge-lists/) |
| C05 | C | Thinking Problems on Linked Lists II | 60–100 min | the math behind Floyd's algorithm, reversing a sub-list between two boundary nodes, interleaving copies to avoid a hash map | [LC 142](https://leetcode.com/problems/linked-list-cycle-ii/) · [LC 25](https://leetcode.com/problems/reverse-nodes-in-k-group/) · [LC 138](https://leetcode.com/problems/copy-list-with-random-pointer/) | [📄 PDF](week05/C05-challenge-linked-list-2/C05-challenge-linked-list-2.pdf) · [📁 files](week05/C05-challenge-linked-list-2/) |
| P02 | P | Playlist on a Doubly Linked List | 90–120 min | a doubly linked list hidden inside a class, a third pointer (`cur`) that must stay valid, relinking two neighbours, formatting time | — | [📄 PDF](week05/P02-playlist-project/P02-playlist-project.pdf) · [📁 files](week05/P02-playlist-project/) |

</details>

<details>
<summary><b>Week 6 · Stack</b> — L21–L24, C06</summary>

Course material: [09-stacks](../materials/slides/09-stacks.ppt), [Labwork 3](../materials/labworks/lw3-stack-palindrome/), [2021 A2 codeStack](../materials/assignments/2021-fall/a2-code-stack-undo/), [2017 AS3](../materials/assignments/2017-spring/as3-stack-expressions/), [lecture code week04](../materials/lecture-code/week04/).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L21 | 1 | std::stack and the Slides' Stack: empty() vs. !empty() | 40 min | LIFO, `std::stack` (`push`, `top`, `pop` returning `void`, `empty`), the slides' `bool` API (`pop()`, `pop(item&)`, `getTop(item&)`), guarding every read with an emptiness check | [LC 20](https://leetcode.com/problems/valid-parentheses/) (M1, M2) · [LC 1047](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/) (L21-X) | [📄 PDF](week06/L21-std-stack-and-slides-stack/L21-std-stack-and-slides-stack.pdf) · [📁 files](week06/L21-std-stack-and-slides-stack/) |
| L22 | 2 | Your Own LLStack<T> | 50 min | a class template over a linked list, the course names `pushToStack` / `popFromStack` (returns the value), exceptions for an empty stack, destructor, moving a node between two stacks, copy constructor (rule of three) | [LC 155](https://leetcode.com/problems/min-stack/) (next lab) · [LC 232](https://leetcode.com/problems/implement-queue-using-stacks/) (Lab 23) | [📄 PDF](week06/L22-your-own-llstack/L22-your-own-llstack.pdf) · [📁 files](week06/L22-your-own-llstack/) |
| L23 | 3 | Two Stacks | 45 min | moving elements between stacks, how pouring reverses order, comparing two stacks top by top, amortized analysis of a two-stack queue | [LC 232](https://leetcode.com/problems/implement-queue-using-stacks/) (M2) · [LC 946](https://leetcode.com/problems/validate-stack-sequences/) (L23-X) | [📄 PDF](week06/L23-two-stacks/L23-two-stacks.pdf) · [📁 files](week06/L23-two-stacks/) |
| L24 | 4 | Timed Lab: Postfix and Min Stack | 50 min, timed | postfix evaluation (operand order!), a second stack for extra information, operator precedence with a stack (shunting-yard) | [LC 150](https://leetcode.com/problems/evaluate-reverse-polish-notation/) (A) · [LC 155](https://leetcode.com/problems/min-stack/) (B) · [LC 682](https://leetcode.com/problems/baseball-game/) (L24-X) | [📄 PDF](week06/L24-timed-lab-postfix-minstack/L24-timed-lab-postfix-minstack.pdf) · [📁 files](week06/L24-timed-lab-postfix-minstack/) |
| C06 | C | Thinking Problems on Stacks | 60–100 min | monotonic stacks (“who is waiting for a bigger value?”), a stack of partial results for nested brackets, left/right boundaries found by one stack | [LC 739](https://leetcode.com/problems/daily-temperatures/) · [LC 394](https://leetcode.com/problems/decode-string/) · [LC 84](https://leetcode.com/problems/largest-rectangle-in-histogram/) | [📄 PDF](week06/C06-challenge-stack/C06-challenge-stack.pdf) · [📁 files](week06/C06-challenge-stack/) |

</details>

<details>
<summary><b>Week 7 · Queue</b> — L25–L28, C07</summary>

Course material: [10-queues](../materials/slides/10-queues.ppt), [lecture code week05](../materials/lecture-code/week05/), [Labwork 5](../materials/labworks/lw5-priority-queue/).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L25 | 1 | std::queue and the Slides' Queue | 45 min | FIFO, `std::queue` (`push`, `front`, `back`, `pop` returning `void`), the slides' `bool` API: `dequeue()` only removes, `dequeue(item&)` reads and removes, `getFront(item&)` only reads; copy constructor | [LC 933](https://leetcode.com/problems/number-of-recent-calls/) (M1) · [LC 1700](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/) (L25-X) | [📄 PDF](week07/L25-std-queue-and-slides-queue/L25-std-queue-and-slides-queue.pdf) · [📁 files](week07/L25-std-queue-and-slides-queue/) |
| L26 | 2 | LLQueue<T> and the Circular Array Queue | 50 min | two ends of a linked list (`front`, `rear`), resetting `rear` when the queue empties, a value-returning `dequeue()`, an array whose indexes wrap around with `%`, telling “full” from “empty” with a counter | [LC 622](https://leetcode.com/problems/design-circular-queue/) (M2) · [LC 2073](https://leetcode.com/problems/time-needed-to-buy-tickets/) (L26-X) | [📄 PDF](week07/L26-llqueue-and-circular-array/L26-llqueue-and-circular-array.pdf) · [📁 files](week07/L26-llqueue-and-circular-array/) |
| L27 | 3 | Alternate Triples With a Queue and a Stack | 45 min | the rotation pattern (process exactly `n` elements by moving them to the back), a stack to reverse a group, counting groups without indexes | [GfG Reverse First K of Queue](https://www.geeksforgeeks.org/problems/reverse-first-k-elements-of-queue/1) (B and L27-X) | [📄 PDF](week07/L27-alternate-triples-queue-stack/L27-alternate-triples-queue-stack.pdf) · [📁 files](week07/L27-alternate-triples-queue-stack/) |
| L28 | 4 | Delete the Middle, Build a Queue | 45 min | combining two structures: a linked list of `char` and the slides' `Queue`; middle deletion (Lab 18) + FIFO output; freeing everything at the end | [LC 2095](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/) · [GfG Queue using Linked List](https://www.geeksforgeeks.org/problems/implement-queue-using-linked-list/1) (L28-X) | [📄 PDF](week07/L28-delete-middle-build-queue/L28-delete-middle-build-queue.pdf) · [📁 files](week07/L28-delete-middle-build-queue/) |
| C07 | C | Thinking Problems on Queues and Deques | 60–100 min | simulating rounds with two queues, a circular array with insertions at both ends, a monotonic deque | [LC 649](https://leetcode.com/problems/dota2-senate/) · [LC 641](https://leetcode.com/problems/design-circular-deque/) · [LC 239](https://leetcode.com/problems/sliding-window-maximum/) | [📄 PDF](week07/C07-challenge-queue/C07-challenge-queue.pdf) · [📁 files](week07/C07-challenge-queue/) |

</details>

<details>
<summary><b>Week 8 · Midterm mocks (three timed exams) and a project</b> — L29–L31, P03</summary>

Course material: [midterm notes](../materials/exams/vize-notlari.txt), the older [midterm camp](../practice/midterm-camp/) (30 questions, same test runner).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L29 | 1 | Midterm Mock A: Lists and Stacks | 50 min, timed | the midterm topics in new clothes: two stacks with the slides' API, `empty()`/`!empty()`, deleting the middle of a doubly linked list | — | [📄 PDF](week08/L29-midterm-mock-a/L29-midterm-mock-a.pdf) · [📁 files](week08/L29-midterm-mock-a/) |
| L30 | 2 | Midterm Mock B: Strings, Stacks, Queues | 50 min, timed | the midterm topics with harder input and the course's own APIs: numbers inside text, two slides' stacks, alternate groups with the slides' queue and stack | — | [📄 PDF](week08/L30-midterm-mock-b/L30-midterm-mock-b.pdf) · [📁 files](week08/L30-midterm-mock-b/) |
| L31 | 3 | Midterm Mock C: Variants With Your Own Classes | 50 min, timed | the same midterm topics, one step away from what you practised: a different node of the circle, the camp's value-returning APIs, a different output queue | — | [📄 PDF](week08/L31-midterm-mock-c/L31-midterm-mock-c.pdf) · [📁 files](week08/L31-midterm-mock-c/) |
| P03 | P | Browser: History With Two Stacks, Downloads in a Queue | 90–120 min | two stacks as “past” and “future”, clearing a stack, reading a stack without changing it (work on a copy), a FIFO queue with partial progress on its front element | [LC 1472](https://leetcode.com/problems/design-browser-history/) (part B) | [📄 PDF](week08/P03-browser-project/P03-browser-project.pdf) · [📁 files](week08/P03-browser-project/) |

</details>

<details>
<summary><b>Week 9 · Graph</b> — L32–L35, C09, P04</summary>

Course material: [12-graphs](../materials/slides/12-graphs.pptx), [11-algorithm-analysis](../materials/slides/11-algorithm-analysis.pptx), [Labwork 6](../materials/labworks/lw6-graph-degrees/), [2021 A3](../materials/assignments/2021-fall/a3-directed-graph/), [Practice Lab 4](../materials/practice-labs/pl4-campus-friends/), [2017 AS2](../materials/assignments/2017-spring/as2-algorithm-analysis/).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L32 | 1 | Adjacency Matrix and Adjacency List | 40 min | vertices and edges, directed vs. undirected, the two representations and their costs, degrees from rows and columns, counting edges | [LC 997](https://leetcode.com/problems/find-the-town-judge/) (L32-X) | [📄 PDF](week09/L32-adjacency-matrix-and-list/L32-adjacency-matrix-and-list.pdf) · [📁 files](week09/L32-adjacency-matrix-and-list/) |
| L33 | 2 | Breadth-First and Depth-First Traversal | 45 min | BFS with a queue, DFS recursively and with a stack, the visited array, shortest paths in edges, connected components | [LC 1971](https://leetcode.com/problems/find-if-path-exists-in-graph/) (L33-X) · [GfG BFS of graph](https://www.geeksforgeeks.org/problems/bfs-traversal-of-graph/1) · [GfG DFS of Graph](https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1) | [📄 PDF](week09/L33-bfs-dfs/L33-bfs-dfs.pdf) · [📁 files](week09/L33-bfs-dfs/) |
| L34 | 3 | Topological Sorting and Cycles | 45 min | directed acyclic graphs, the slides' `topSort1`, Kahn's algorithm with a queue, detecting a cycle with a three-colour DFS | [LC 1557](https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/) (L34-X) · [GfG Topological sort](https://www.geeksforgeeks.org/problems/topological-sort/1) · [GfG Detect cycle in a directed graph](https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1) | [📄 PDF](week09/L34-topological-sort/L34-topological-sort.pdf) · [📁 files](week09/L34-topological-sort/) |
| L35 | 4 | Spanning Trees and Prim's Algorithm | 45 min | spanning trees from DFS and BFS, weighted graphs as matrices, the minimum spanning tree, Prim's algorithm with `best`/`from` arrays | [LC 1584](https://leetcode.com/problems/min-cost-to-connect-all-points/) (L35-X) · [GfG Minimum Spanning Tree](https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1) | [📄 PDF](week09/L35-spanning-trees-prim/L35-spanning-trees-prim.pdf) · [📁 files](week09/L35-spanning-trees-prim/) |
| C09 | C | Thinking Problems on Graphs | 60–100 min | recognising a graph inside a story: prerequisites as a directed graph, a grid as a graph, two-colouring with BFS | [LC 207](https://leetcode.com/problems/course-schedule/) · [LC 994](https://leetcode.com/problems/rotting-oranges/) · [LC 785](https://leetcode.com/problems/is-graph-bipartite/) | [📄 PDF](week09/C09-challenge-graph/C09-challenge-graph.pdf) · [📁 files](week09/C09-challenge-graph/) |
| P04 | P | Metro Route Planner | 90–120 min | a graph whose vertices have names (`std::map` name → number), edges that carry data, BFS with a `parent` array to rebuild the path, distances | [LC 815](https://leetcode.com/problems/bus-routes/) (the hard version: fewest buses instead of fewest stops) | [📄 PDF](week09/P04-metro-project/P04-metro-project.pdf) · [📁 files](week09/P04-metro-project/) |

</details>

<details>
<summary><b>Week 10 · Trees and BSTs</b> — L36–L39, C10, P05</summary>

Course material: [13-trees](../materials/slides/13-trees.pptx); reading: [14-avl-trees](../materials/slides/14-avl-trees.pptx), [15-2-3-trees-red-black](../materials/slides/15-2-3-trees-red-black.pptx); [Labwork 7](../materials/labworks/lw7-bst-queries/), [2021 A4](../materials/assignments/2021-fall/a4-tree-functions/), [2017 AS5](../materials/assignments/2017-spring/as5-trees-graphs-heaps/).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L36 | 1 | Binary Trees: Counting, Traversals, Height | 45 min | binary tree terminology, recursion on trees (base case = empty tree), preorder/inorder/postorder, height, level order with a queue, freeing a tree in postorder | [LC 102](https://leetcode.com/problems/binary-tree-level-order-traversal/) · [LC 104](https://leetcode.com/problems/maximum-depth-of-binary-tree/) · [LC 226](https://leetcode.com/problems/invert-binary-tree/) (L36-X) | [📄 PDF](week10/L36-binary-tree-traversals/L36-binary-tree-traversals.pdf) · [📁 files](week10/L36-binary-tree-traversals/) |
| L37 | 2 | Binary Search Trees | 45 min | the BST property, insert and search along one path (`O(h)`), min/max, checking the property with ranges, treesort, printing a tree's shape | [LC 98](https://leetcode.com/problems/validate-binary-search-tree/) · [LC 700](https://leetcode.com/problems/search-in-a-binary-search-tree/) · [LC 108](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/) (L37-X) | [📄 PDF](week10/L37-binary-search-tree/L37-binary-search-tree.pdf) · [📁 files](week10/L37-binary-search-tree/) |
| L38 | 3 | Deleting From a Binary Search Tree | 45 min | the three cases of deletion (leaf, one child, two children), the inorder successor and predecessor, deletion by copying vs. by merging, pointer-to-pointer links | [LC 450](https://leetcode.com/problems/delete-node-in-a-bst/) · [LC 669](https://leetcode.com/problems/trim-a-binary-search-tree/) (L38-X) | [📄 PDF](week10/L38-bst-deletion/L38-bst-deletion.pdf) · [📁 files](week10/L38-bst-deletion/) |
| L39 | 4 | Tree Questions From the Course Archive | 50 min | inorder with a counter, pruning a BST search, height-balance in one pass, sibling checks, rebuilding a tree from two traversals | [LC 230](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) · [LC 110](https://leetcode.com/problems/balanced-binary-tree/) · [LC 105](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) · [LC 1382](https://leetcode.com/problems/balance-a-binary-search-tree/) (L39-X) | [📄 PDF](week10/L39-tree-archive-questions/L39-tree-archive-questions.pdf) · [📁 files](week10/L39-tree-archive-questions/) |
| C10 | C | Thinking Problems on Binary Trees | 60–100 min | returning information upward from subtrees, carrying information downward (prefix sums), the difference between “the best answer” and “what the parent may use” | [LC 236](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) · [LC 437](https://leetcode.com/problems/path-sum-iii/) · [LC 124](https://leetcode.com/problems/binary-tree-maximum-path-sum/) | [📄 PDF](week10/C10-challenge-tree/C10-challenge-tree.pdf) · [📁 files](week10/C10-challenge-tree/) |
| P05 | P | Phone Book on a Binary Search Tree | 90–120 min | a BST class with string keys and a value, private recursive helpers, `Entry**` links, deletion by copying, a pruned range query, saving in preorder, the rule of three | [LC 208](https://leetcode.com/problems/implement-trie-prefix-tree/) (the structure made for prefix searches) | [📄 PDF](week10/P05-phonebook-project/P05-phonebook-project.pdf) · [📁 files](week10/P05-phonebook-project/) |

</details>

<details>
<summary><b>Week 11 · Hashing</b> — L40–L42, C11</summary>

Course material: [17-hash-tables](../materials/slides/17-hash-tables.pptx), [2021 A5](../materials/assignments/2021-fall/a5-hashing/).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L40 | 1 | Hash Functions and Separate Chaining | 45 min | hash tables, hash functions for strings (sum, Horner with 37), collisions, separate chaining with `std::list`, the load factor, negative keys and `%` | [LC 705](https://leetcode.com/problems/design-hashset/) · [LC 1](https://leetcode.com/problems/two-sum/) (L40-X) | [📄 PDF](week11/L40-hash-functions-chaining/L40-hash-functions-chaining.pdf) · [📁 files](week11/L40-hash-functions-chaining/) |
| L41 | 2 | Open Addressing: Linear, Quadratic, Double Hashing | 45 min | probe sequences, primary clustering, why quadratic probing can miss free slots, double hashing, the three slot states and why deletion needs a DELETED mark | [LC 706](https://leetcode.com/problems/design-hashmap/) · [GfG Linear Probing in Hashing](https://www.geeksforgeeks.org/problems/linear-probing/1) | [📄 PDF](week11/L41-open-addressing/L41-open-addressing.pdf) · [📁 files](week11/L41-open-addressing/) |
| L42 | 3 | unordered_map, unordered_set and map | 45 min | the library's hash tables, `operator[]` vs `find`/`count`, counting with a map, “last index seen”, sliding windows, `std::map` when the order matters | [LC 387](https://leetcode.com/problems/first-unique-character-in-a-string/) · [LC 219](https://leetcode.com/problems/contains-duplicate-ii/) · [LC 242](https://leetcode.com/problems/valid-anagram/) · [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · [LC 205](https://leetcode.com/problems/isomorphic-strings/) (L42-X) | [📄 PDF](week11/L42-unordered-map-set/L42-unordered-map-set.pdf) · [📁 files](week11/L42-unordered-map-set/) |
| C11 | C | Thinking Problems on Hashing | 60–90 min | choosing the key of a hash map (a canonical form), “is this the start of a run?”, prefix sums counted in a map | [LC 49](https://leetcode.com/problems/group-anagrams/) · [LC 128](https://leetcode.com/problems/longest-consecutive-sequence/) · [LC 560](https://leetcode.com/problems/subarray-sum-equals-k/) | [📄 PDF](week11/C11-challenge-hash/C11-challenge-hash.pdf) · [📁 files](week11/C11-challenge-hash/) |

</details>

<details>
<summary><b>Week 12 · Heaps and priority queues</b> — L43–L46, C12, P06</summary>

Course material: [16-heaps](../materials/slides/16-heaps.pptx), [Labwork 8](../materials/labworks/lw8-min-heap/), [Labwork 5](../materials/labworks/lw5-priority-queue/), [2017 AS5 Q4](../materials/assignments/2017-spring/as5-trees-graphs-heaps/).

| No | Day | Title | Time | Topics | Related problems | Open |
| --- | --- | --- | --- | --- | --- | --- |
| L43 | 1 | The Slides' Max-Heap in an Array | 45 min | complete binary trees stored in arrays, the heap property, trickle up (insert), trickle down (rebuild a semiheap), delete the root, bottom-up heap construction in `O(n)` | [LC 1046](https://leetcode.com/problems/last-stone-weight/) (L43-X) · [GfG Does array represent Heap](https://www.geeksforgeeks.org/problems/does-array-represent-heap/1) | [📄 PDF](week12/L43-max-heap/L43-max-heap.pdf) · [📁 files](week12/L43-max-heap/) |
| L44 | 2 | Min-Heap Questions From the Archive | 45 min | a min-heap in a 1-based array (children 2i and 2i+1), percolate down with a loop, bottom-up construction, delete-min, insert, reading a heap's shape from its preorder | [GfG Heap Sort](https://www.geeksforgeeks.org/problems/heap-sort/1) · [LC 1046](https://leetcode.com/problems/last-stone-weight/) | [📄 PDF](week12/L44-min-heap-archive/L44-min-heap-archive.pdf) · [📁 files](week12/L44-min-heap-archive/) |
| L45 | 3 | Heapsort and std::priority_queue | 45 min | heapsort in place (`O(n log n)`, no extra array), the library's heap `std::priority_queue` (max by default, min with `greater`, custom comparators), “keep the best k” with a heap of size k | [LC 215](https://leetcode.com/problems/kth-largest-element-in-an-array/) · [GfG Nearly sorted](https://www.geeksforgeeks.org/problems/nearly-sorted-1587115620/1) · [LC 973](https://leetcode.com/problems/k-closest-points-to-origin/) (L45-X) | [📄 PDF](week12/L45-heapsort-priority-queue/L45-heapsort-priority-queue.pdf) · [📁 files](week12/L45-heapsort-priority-queue/) |
| L46 | 4 | Priority Queues at Work | 50 min | a stable priority queue with arrival numbers, Dijkstra's shortest paths, Prim with a heap (`O(E log V)`), simulating a scheduler, lazy deletion (“skip stale entries”) | [LC 743](https://leetcode.com/problems/network-delay-time/) · [LC 1834](https://leetcode.com/problems/single-threaded-cpu/) · [LC 1642](https://leetcode.com/problems/furthest-building-you-can-reach/) (L46-X) | [📄 PDF](week12/L46-priority-queue-applications/L46-priority-queue-applications.pdf) · [📁 files](week12/L46-priority-queue-applications/) |
| C12 | C | Thinking Problems on Heaps | 60–100 min | a heap of list heads, two heaps that balance each other, counting with a map then keeping the best k | [LC 23](https://leetcode.com/problems/merge-k-sorted-lists/) · [LC 295](https://leetcode.com/problems/find-median-from-data-stream/) · [LC 347](https://leetcode.com/problems/top-k-frequent-elements/) | [📄 PDF](week12/C12-challenge-heap/C12-challenge-heap.pdf) · [📁 files](week12/C12-challenge-heap/) |
| P06 | P | Emergency Room Triage on Your Own Heap | 100–120 min | a heap of structs with a two-level priority (severity, then arrival), sift up and sift down as helpers, changing the priority of an item inside the heap, removing from the middle, reporting through a copy | [LC 1845](https://leetcode.com/problems/seat-reservation-manager/) · [LC 2353](https://leetcode.com/problems/design-a-food-rating-system/) (priority changes) | [📄 PDF](week12/P06-triage-project/P06-triage-project.pdf) · [📁 files](week12/P06-triage-project/) |

</details>

## Midterm topics: where each one is practised

Every topic of the [midterm notes](../materials/exams/vize-notlari.txt) is taught on its own first, then asked with the real data structure, and comes back slightly changed in a timed mock in week 8. Rules the notes do not state (how groups are counted, an incomplete last group, the “middle” of an even-length list, behaviour on an empty structure) are written in the PDF as an explicit **exercise assumption**.

| Midterm topic | Preparation | Main lab | Timed again |
| --- | --- | --- | --- |
| Push and pop between two stacks | L21, L22 (`pushToStack` / `popFromStack`) | L23 | L29-A |
| `st.empty()` vs. `!st.empty()` | L21 | L23 | L29-B |
| Are two strings reverses of each other (two stacks) | L03 (vector), L09 (string) | L23 | L30-B |
| Reverse alternate triples `1…9 → 3 2 1 4 5 6 9 8 7` | L03 (vector, in place) | L27 (queue + one stack) | L30-C, L31-B |
| The smallest number in a string, with a temp variable | L10 | L12 | L30-A |
| Delete the middle node and print the rest through a new queue | L16, L18 (deletion) | L28 | L29-C (doubly), L31-C |
| Delete `last` from a circular list and relink | L13 (paper trace) | L19 | L31-A |

## Course labworks and assignments: where they are

A compiled and tested solution of every archive question lives under [`../materials`](../materials/README.md). The camp asks the same questions again in lab form, with tests and a step-by-step solution:

| Archive | In the camp |
| --- | --- |
| Labwork 1 (`IntSLList`) · Labwork 2 (`genDLList`) · Labwork 3 (a stack on a DLL, palindrome) | L15 · L17 · L17, L24 |
| Labwork 5 (priority queue, FIFO on ties) | L46-A, P06 |
| Labwork 6 (`indegree`, `outdegree`, `num_edges`) | L32 (M1, M2) |
| Labwork 7 (`getnthelement`, `printsmallerthan`, `isbalanced`, deletion) | L38, L39 |
| Labwork 8 (`percolate_down`, `delete_min`, `heapify`, `inorder`) | L44 |
| Practice Lab 2 (linked list questions) · Practice Lab 4 (Campus Friends: BFS, DFS, number of groups) | L13–L16, L19, L20 · L33 |
| 2017 AS1 (grades list) · AS2 (complexity) · AS3 (expressions with a stack) · AS4 (classes) | P01 · L32 · L24 · L11 |
| 2017 AS5 Q1, Q2, Q4, Q5 (tree from traversals, BST shape and deletion, heaps) | L39-M3, L37-M4, L38-V, L44, L36-V, L37-V |
| 2021 A1 (sorting, swapping nodes) · A2 (`codeStack`, undo) · A3 (directed graph, BFS) | L15, L16 · L22, P03 · L33, P04 |
| 2021 A4 (`isThisaBST`, `findHeight`, `findOnlyChild`) · A5 (chained hashing) | L37-M2, L36-M2, L39-M2 · L40 |

## The course's own function names

The same operation has a different name and return type in different classes of the course. The table shows where each name comes from and which lab uses it. Names marked *practice signature* do not exist in the archive; the lab that uses them gives the signature explicitly as an exercise, and they are not presented as the course API.

<details>
<summary><b>Show the table (click)</b></summary>

| Operation | Standard C++ | Real name and contract in the course archive | Lab |
| --- | --- | --- | --- |
| Add at the end | `v.push_back(x)` | `pushBack(Node*& head, int value)` ([Practice Lab 2](../materials/practice-labs/pl2-linked-list/solution/q3.cpp)) · `addToTail(int)` ([IntSLList](../materials/labworks/lw1-singly-linked-list/solution/intSLList.h)) · `addToDLLTail(const T&)` ([genDLList](../materials/labworks/lw2-doubly-linked-list/solution/genDLList.h)) · `pushToBack`: practice signature | L01, L14, L15, L17 |
| Add at the front | `d.push_front(x)` (`deque`, `list`) | `addToHead(int)`, `addToDLLHead(const T&)` | L15, L17 |
| Remove from the front / end | `pop_front()`, `pop_back()` → `void` | `deleteFromHead()`, `deleteFromTail()` → `int`, undefined on an empty list (check `isEmpty()` first); `deleteFromDLLHead/Tail()` → `T` | L15, L17 |
| Push onto a stack | `st.push(x)` | slides: `bool push(StackItemType)` · `pushToStack(const char*)` ([A2 codeStack](../materials/assignments/2021-fall/a2-code-stack-undo/given/codeStack.h)) · `pushToStack(const T&)` (camp `LLStack`) | L21, L22 |
| Pop from a stack | read `st.top()`, remove with `st.pop()` (`void`) | slides: `bool pop()` only removes, `bool pop(item&)` writes the value, `bool getTop(item&) const` · `popFromStack()` returns the value (`string` in A2, `T` in the camp) | L21, L22, L23 |
| Move between stacks | — | `pushFromStack(src, dst)`: practice signature | L22, L23 |
| Enqueue | `q.push(x)` | slides: `bool enqueue(item)` · A3 and camp `LLQueue`: `void enqueue` | L25, L26 |
| Dequeue | read `q.front()`, remove with `q.pop()` (`void`) | slides: `bool dequeue()` only removes, `bool dequeue(item&)` writes the value, `bool getFront(item&) const` · A3 and the camp: `dequeue()` returns the value | L25–L28 |
| Is it empty? | `empty()` | `isEmpty()`: `int` in IntSLList, `bool` elsewhere | L15, L21, L25 |
| Heap | `std::priority_queue`, `push_heap` / `pop_heap` | slides: `heapInsert`, `heapDelete(item&)`, `heapRebuild(root)` · Labwork 8: `percolate_down`, `delete_min`, `heapify` | L43, L44, L45 |
| Hash | `std::unordered_map`, `unordered_set` | slides: `int hash(const string& key, int tableSize)` · A5: `insertIntoHashTable`, `searchInHashTable`, `encodeString` | L40, L41, L42 |

</details>

## Review plan

- **At the end of every week:** the checklist at the end of the last PDF. If you answer “no” to an item, rewrite that lab from an empty file (`git checkout` restores the starter `labXX.cpp`).
- **V questions:** write each lab's memory variant 48 hours later, without the PDF, with a timer. These are the camp's flash cards.
- **Before the midterm (weeks 4–8):** solve L29–L31 under exam conditions (50 minutes). The answer key of each mock tells you which lab to redo for every part below 80 points.
- **Before the final (weeks 9–12):** redo the 4th lab of each week (L35, L39, L42, L46) with a timer; do the slides' traces on paper (BFS/DFS order, `topSort1`, Prim, BST deletion, open addressing tables, building and deleting from a heap) and compare with your program.
- **Projects:** pick one of the “extension ideas” in each project's PDF and add it together with your own tests.

## Folder layout and building the PDFs

```
lab-camp/
├── README.md               this index
├── run.ps1, run.sh         compile + test
├── week01/ … week12/
│   └── L01-vector-first-steps/
│       ├── L01-vector-first-steps.pdf   ← lab question, explanation, solution
│       ├── lab01.h                      given header (do not edit)
│       ├── lab01.cpp                    ← YOU WORK HERE
│       ├── warmup.cpp                   warm-up program (first weeks)
│       └── tests/                       tests + pdf_cases.inc generated from the PDF tables
├── solutions/L01/          reference solution and the PDF's alternatives (look after solving)
├── framework/              small test framework: test.h, todo.h, tree_build.h (tree tests)
└── _tools/                 PDF generation: labs/*.html templates, build.py, draw.py, style.css
```

<details>
<summary><b>Rebuilding the PDFs or adding a lab (click)</b></summary>

Use `python _tools/build.py L01` to build a PDF (needs Microsoft Edge and `pygments`) and `python _tools/build.py verify L01` to check it; `verify` without an ID checks the whole camp. It makes sure that the starter files compile and report “not written yet”, that the reference solutions pass every test, and that the warm-up and demo programs compile without warnings. The code blocks of a PDF come from the files that are compiled, and its test tables come from the same `pdf_cases.inc` that the tests read, so the PDF and the tests cannot drift apart.

</details>
