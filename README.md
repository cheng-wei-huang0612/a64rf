# A64RF Playground

Welcome! This repository is a tiny sandbox for tinkering with ARM64 register snapshots.  If you enjoy low-level experiments, you might like these files.

> **Heads up**: the instruction simulation core works, but many instructions still
> aren't implemented. Expect gaps while we fill in the missing pieces over time.
> The snapshot function also likes to misbehave occasionally, so treat results
> as experimental.

```
\o/  Features
-----------------
* Snapshot helpers written in C
* Macros to capture register state from assembly
* Small demo programs
* Extra sample programs live in `tests/`
```

To build the examples, grab a compiler that targets ARM64 and run a few clang commands (see `README.md`). Define `A64RF_TRACE` when you assemble to emit extra debug snapshots.

Have fun exploring!


