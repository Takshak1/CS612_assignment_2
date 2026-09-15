# CS612 Lab: Defusing a Binary Bomb

*Based on CMU's classic 15-213 Bomb Lab. This lab covers material from
CS:APP Chapter 3, Sections 3.1-3.6 (machine-level data, registers and
addressing modes, arithmetic/logical instructions, condition codes, jumps,
loops, and switch statements).*

## 1. Introduction

Attached to this assignment is a binary bomb: a program with 6 phases.
Each phase reads one line from standard input. If the line you type is
correct, the phase is *defused* and the bomb moves to the next one.
Otherwise, it prints `BOOM!!!` and exits.

Your job is to defuse all 6 phases by figuring out, from the disassembly
alone, what each phase expects you to type.

## 2. Getting started

The bomb is a Linux/x86-64 binary built and tested for **Ubuntu 24.04**.
Run it there directly, or in a VM running Ubuntu 24.04 if you're on
Windows or macOS.

```
chmod +x bomb
./bomb
```

If you run it with a file argument, e.g. `./bomb answers.txt`, the bomb
reads lines from that file until EOF and then switches to stdin -- so
once you've defused a phase, save its answer to a file and you won't
have to retype it.

**There is no scoreboard and no penalty for exploding the bomb while you
experiment.** Only the file you submit is graded. That said, get in the
habit of using breakpoints (see below) rather than repeatedly guessing --
it is the whole point of the exercise, and it is the skill this lab is
meant to build.

## 3. Tools

- `objdump -d bomb` -- disassemble the whole binary.
- `objdump -t bomb` -- list the symbol table, including the names of all
  6 `phase_N` functions.
- `gdb ./bomb` -- step through a phase, inspect registers (`info
  registers`, `p $eax`) and memory (`x/6dw $rsp`), and set breakpoints
  (`break phase_3`) so a wrong guess doesn't run past the point you're
  studying.
- `strings bomb` -- list printable strings embedded in the binary.

The binary is **not** compiled with `-g`, so `gdb` cannot show you C
source or `list` a phase -- you are reading disassembly only, exactly as
in the real lab.

## 4. Method

For each phase:

1. Disassemble it (`objdump -d` or `disas phase_N` in gdb).
2. Find the call to `sscanf` (or the string-comparison helper) near the
   top -- its format string tells you the *shape* of the input (how many
   numbers, or a string).
3. Walk forward through the comparisons and jumps. Translate every
   `cmp`/`test` + `jXX` pair back into the C condition it implements --
   this is exactly the skill from lecture (condition codes -> branches).
4. Chain those conditions into the constraint your input must satisfy,
   then pick a concrete value.
5. Verify in gdb before you rely on it: set a breakpoint at the phase's
   final comparison, step to it, and check the flags/registers agree
   with what you expect.

## 5. What each phase exercises

You do not need to know what "phase 3" or "phase 5" *does* in advance --
that's the point of the lab -- but here is which lecture material each
phase draws on, so you know where to look back if you get stuck:

| Phase | Lecture material |
|---|---|
| 1 | Procedure calls, pointers, loop-based comparison |
| 2 | Loops and condition codes (reading a `for`/`while` translation) |
| 3 | `switch` compiled as a jump table |
| 4 | `switch` with fall-through, combined with a loop |
| 5 | Conditional move (`cmov`) -- a branch compiled *without* a jump |
| 6 | Indexed/scaled addressing (`array[i]`) and loops |

## 6. Submitting

**Every file you submit must be prefixed with your roll number**, e.g.
if your roll number is `21110123`:

- `21110123_answers.txt`
- `21110123_report.md`

Submissions without the roll-number prefix may not be graded.

Create the answers file as plain text, one line per phase (in order,
phase 1 through phase 6), matching the format each phase expects.
Verify it locally:

```
./bomb 21110123_answers.txt
```

You should see `Congratulations! You've defused the bomb!` and no
`BOOM!!!`.

Submit both `<rollnumber>_answers.txt` **and** the report described
below, as instructed on the course page.

## 7. Submission report

Along with `<rollnumber>_answers.txt`, submit a short report
(`<rollnumber>_report.md` or `.txt`) describing how you actually solved
each phase. This is graded as part of the assignment, and it will also
be the basis for a short in-person follow-up conversation about your
submission -- so write about what you actually did, not a clean,
after-the-fact derivation that skips the parts where you were confused.

For each of the 6 phases, include:

- What you tried first, and why it didn't work (if it didn't).
- The specific commands/tools you used to figure it out -- which
  `objdump`/`gdb` commands, what addresses or registers you inspected,
  and what they showed.
- The moment it "clicked" -- what you saw in the disassembly or in gdb
  that made the constraint clear.
- Any wrong turns or dead ends along the way.

**If you could not solve a phase, don't skip it.** Describe what you
tried, where you got stuck, and what you did understand about the
phase even without a final answer. A well-reasoned account of a phase
you didn't solve is worth more than a vague one-line report for a
phase you did.

Aim for roughly 100-200 words per phase -- enough to show real
engagement, not an essay.

**Track your work with git, and state your commit count at the top of
the report.** `git init` in your working directory when you start, and
make a commit as you go -- e.g. whenever you crack a phase, save a
useful gdb finding, or update your notes. At the top of your report,
state your total commit count (`git log --oneline | wc -l`). This is
just another data point for the in-person follow-up, alongside the
report itself -- a handful of commits made over the time you actually
spent on this is expected; it's fine if it's rough and messy.

## 8. Please don't brute-force it

We haven't told you the length or character set of any answer. Brute
force is not a realistic strategy here, and it defeats the purpose of
the exercise -- you'll get much more out of reading the disassembly.

Good luck!
