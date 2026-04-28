# AGENTS.md

## Scope

- The git repo root is `/home/othman/work/college`.
- `dataStructure/` contains standalone C++ practice files (`array.cpp`, `stack.cpp`, `queue.cpp`, `linkedList.cpp`, etc.). Each file currently has its own `main()` and should be treated independently unless the user asks for consolidation.
- This is coursework / teaching code, not a production library. Prefer the smallest correct fix and keep implementations easy to follow.
- Base your reviews on the lecture/section materials located at ~/Documents/obsidian/src/College/yearTwo/secondTerm/DataStructures/*

## Verification

- Use `cppc` for compile/run verification instead of manual `g++` commands.
- Run a single file from `dataStructure/` with `cppc <file>.cpp`.
- Use `cppc -c <file>.cpp` only when compile-only verification is enough.
- `dataStructure/.gitignore` ignores `*.out`, so do not rely on tracked binaries.

## Implementation Conventions

- Keep data-structure implementations simple and aligned with classroom intent: fixed-size array-backed structures and straightforward linked-list pointer logic are acceptable.
- Do not "productionize" these exercises unless the user explicitly asks. Avoid adding extra abstractions, advanced error-handling APIs, or heavy refactors.
- Still fix real correctness issues even in demo code: invalid memory access, leaks in core operations, broken empty/full handling, and off-by-one errors.

## Working Style

- When reviewing these files, judge them against "basic teaching implementation" expectations, not against STL/container-quality standards.
- If adding another variant of a structure, keep the original version when it helps compare approaches for learning.
