# A64RF Register-File Playground

This repository contains a minimal framework for experimenting with ARMv8-A register snapshots and instruction emulation.  It offers a small C library that models the general purpose and NEON vector registers of a 64‑bit ARM core along with helper routines to inspect and modify the state.

## Repository layout

- `include/` – Public headers describing the register file, helpers and instruction API.
- `src/` – Implementations for snapshot/dump routines used by the examples.
- `asm.S` – Demo assembly showing how to call the snapshot macros.
- `tests/` – Small sample programs using the API.  Each file can be built independently.

## Status

The snapshot helpers and the unit tests are stable.  Many instruction helpers are still incomplete, so the library should be considered experimental.  Contributions and bug reports are welcome.

