# D3DMetal Fix - Screen Space Shaders - Metal Loop Guards

Bounds the two unbounded parallax-occlusion loops in Screen Space Shaders'
`sload.h` so they cannot hang the GPU under **D3DMetal / DXMT** (macOS / Apple
Silicon).

macOS has no TDR-style recovery — a fragment shader that spins forever takes
down the GPU until the game or the machine restarts, so data-dependent loops
with no iteration cap are the top hang risk in the shader stack. Parallax
normally terminates because `curr_step` outgrows the sampled height; a
degenerate `_step` (a division producing 0 or inf) or a NaN feeding the
comparison can otherwise spin it.

## Source mod

| Source mod | Version this fix was built against | File |
| --- | --- | --- |
| Screen Space Shaders | 23 | `gamedata/shaders/r3/sload.h` |

The shipped shader is Screen Space Shaders 23's own `sload.h` plus the two
guards, with no other changes. If Screen Space Shaders updates this file,
re-copy it and re-apply the guards (search `[elseform]`).

`sload.h` is also shipped by Enhanced Shaders, which loses the conflict to
Screen Space Shaders in a standard G.A.M.M.A. load order — the copy here is
built on the Screen Space Shaders version.

## What it changes

- Caps the parallax main loop at 128 iterations.
- Caps the contact-refinement loop at 64 iterations.

Both limits sit well above the worst legitimate step count, so visuals are
unaffected — a guard only fires if the loop is already misbehaving.

## Install

1. Install as a normal MO2 mod, or drop its `gamedata` folder into the game
   directory.
2. Load it **after** Screen Space Shaders so this shader wins the conflict.
3. **Delete the `appdata/shaders_cache/` folder** so the game rebuilds the
   shaders. This step is required, not optional.

This entry is self-contained: it ships the complete shader and does not require
any other loop-guard mod.

## Scope

This entry covers `sload.h` only. The matching guard for `ssfx_water.ps` is held
back because its base file comes from SSS Update 24 ALPHA18, which is not a
public release; it will ship once that source mod is public.

## Validation

Static checks:

- Compare the override against Screen Space Shaders 23's `sload.h` and verify
  the only additions are the two loop guards.

In-game checks:

- Compile the shaders under D3DMetal/DXMT without errors.
- Check terrain and world geometry with parallax enabled, at grazing angles
  where the step count is highest.
