# Midterm Camp · Linked List · Stack · Queue

Workspace for the 30 problems in `Vize.pdf`. The problems, classes and tests are ready; you only write the function bodies.

## Workflow

1. Open a file in `problems/` (`linkedlist.cpp`, `stack.cpp`, `queue.cpp`).
2. Delete the `TODO();` line in the problem's function and write your code.
3. Run:

```powershell
.\run.ps1          # everything
.\run.ps1 ll       # linked list only   (st, qu)
.\run.ps1 LL-6     # a single problem
.\run.ps1 mock     # Monday's mock exam set: LL-6, LL-9, ST-5, ST-9, QU-8, QU-9
```

From Git Bash: `./run.sh LL-6`

## Reading the output

```
LL-5   Remove first occurrence ............... ✗ 616/624
      ✗ [1, 4, 3, 4], v=4  →  1 node(s) were not deleted (memory leak)
LL-6   Reverse the list ...................... ✓ 619/619
QU-6   Remove all occurrences ................ · needs QU-1 (Queue size) first
```

| Mark | Meaning |
| ---- | ------- |
| `✓` | every check passed |
| `✗` | some cases are wrong; the input, the expected value and your output are shown |
| `·` | not written yet, or it calls another function that isn't written yet |
| `💥` | segfault (null pointer or access to a deleted node) |
| `⏱` | did not finish in 3 seconds, probably an infinite loop |

## What the tests cover

Each problem has three kinds of cases:

- **PDF examples**
- **Hand-picked edge cases:** empty structure, single element, head/tail, invalid `k`, the `target == value` trap and similar
- **200 random inputs**, compared against a simple `std::vector` reference. The seed is fixed, so you get the same inputs on every run.

On top of that, the tests also check:

- **LL-5, LL-6, LL-9:** removed nodes are really `delete`d (leak check)
- **LL-6:** the list is reversed in place, without allocating new nodes
- **LL-10:** the pointers are swapped, not the `item` values
- **ST/QU:** structures that must stay unchanged really do; in queues, `rear` is still valid afterwards (one more `enqueue` is tried)

## Folders

```
camp/
├── problems/     ← YOU WORK HERE
├── ds/           LinkedList, LLStack, LLQueue (push/pop/enqueue/dequeue are provided)
├── tests/        test cases
├── framework/    tiny test framework
└── run.ps1       compile + run
```

For debugging you can call `print();` (LL), `printStack();` or `printQueue();` inside your functions.
