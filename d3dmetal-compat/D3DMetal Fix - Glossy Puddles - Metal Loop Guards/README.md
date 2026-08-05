# D3DMetal Fix - Glossy Puddles - Metal Loop Guards

Bounds the two unbounded terrain parallax-occlusion loops in Glossy Puddles'
terrain shader so they cannot hang the GPU under **D3DMetal / DXMT** (macOS /
Apple Silicon).

macOS has no TDR-style recovery — a fragment shader that spins forever takes
down the GPU until the game or the machine restarts, so data-dependent loops
with no iteration cap are the top hang risk in the shader stack. Terrain POM
normally terminates because `curr_step += _step` outgrows the sampled height; a
degenerate `_step` (a division producing 0 or inf) or a NaN feeding the
comparison can otherwise spin it.

## Source mod

| Source mod | Version this fix was built against | File |
| --- | --- | --- |
| Glossy Puddles | 1.4 | `gamedata/shaders/r3/deffer_terrain_high_flat_d.ps` |

The shipped shader is Glossy Puddles 1.4's own terrain shader — including its
`shader_param_5.w` reflection-strength control — plus the two guards. If Glossy
Puddles updates this file, re-copy it and re-apply the guards (search
`[elseform]`).

## What it changes

- Caps the terrain POM main loop at 128 iterations.
- Caps the optional `SSFX_TERRA_POM_REFINE` contact-refinement loop at 64
  iterations.

Both limits sit well above the worst legitimate step count, so visuals are
unaffected — a guard only fires if the loop is already misbehaving.

## Install

1. Install as a normal MO2 mod, or drop its `gamedata` folder into the game
   directory.
2. Load it **after** Glossy Puddles so this terrain shader wins the conflict.
3. **Delete the `appdata/shaders_cache/` folder** so the game rebuilds the
   shaders. This step is required, not optional.

This entry is self-contained: it ships the complete terrain shader and does not
require any other loop-guard mod.

## Validation

Static checks:

- Compare the override against Glossy Puddles 1.4 and verify the only additions
  are the two loop guards.

In-game checks:

- Compile the terrain shader under D3DMetal/DXMT without errors.
- Check dry and wet terrain with terrain POM enabled.
- Adjust the Glossy Puddles reflection strength and verify the puddle response
  still changes as expected.
