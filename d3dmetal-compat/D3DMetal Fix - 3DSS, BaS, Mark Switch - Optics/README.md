# D3DMetal Fix - 3DSS, BaS, Mark Switch - Optics

Fixes broken scope, sight, and night/thermal-vision rendering when STALKER
GAMMA runs through **D3DMetal / DXMT** (macOS / Apple Silicon via GPTK and
similar).

GAMMA's optic shaders were written for Windows, where the DirectX shader
compiler accepts some non-standard HLSL. The Metal translation layer is
stricter and rejects or miscompiles that same code, which shows up as optics
that render wrong on Mac. This mod patches the shaders so they're valid
everywhere.

- **Red-dot & holographic sights** — dots/reticles that disappear now show up
  again, and the sight glass renders cleanly.
- **Night-vision scopes** — the image is properly lit and not overblown.
- **Thermal scopes** (e.g. the G36 Spec Ops) — cold areas no longer turn into
  black/garbage noise; you get a clean thermal picture.
- **Regular magnified scopes** — no more artifacts around the reticle/lens edge.
- **Mark-switch reticle grid** — can no longer spin on garbage input.

## Source mods

The shipped shaders are the winning copies from these mods plus the documented
fixes. If any of them updates one of these files, rebase and re-apply.

| Source mod | Version this fix was built against | Files |
| --- | --- | --- |
| 3DSS for GAMMA | 4.17 | `mark_adjust.h`, `models_reflex_lens.ps`, `models_reflex_reticle*.ps`, `models_scope_zwrite.ps`, `models_scope_zwrite.s`, `scope_3dss_common.h`, `thermal_utils.h` |
| Boomsticks and Sharpsticks | 1.5.1 | `models_scope_nv_1.ps`, `models_scope_nv_2.ps`, `models_scope_nv_3.ps` |
| Mark Switch | GAMMA ver. | `models_lfo_light_dot_weapons.ps` |
| Authentic Reticles Collection (ARC) 3DSS | 1.6.7 | `models_scope_reticle.ps`, `models_scope_reticle_precise.ps` |

`models_scope_reticle.ps` and `models_scope_reticle_precise.ps` are ARC 3DSS
1.6.7's own copies with the sqrt clamp applied — verified as the only functional
delta. ARC ships them in its optional `ARC-3DSS-U/SHADERS` component, which is
not part of a default ARC install, so 3DSS's older copies win otherwise. That
means this mod also carries ARC's reticle features (`RT_DFP_ALT`, the
brightness-adaptive reticle via `current_lum_2`, and the blue-channel LED
illumination mask), which 3DSS 4.17's own `--ARC 3DSS VERSION--` copies predate.
That is intended: install this mod and you get ARC's optional shader component
with the D3DMetal fix already applied.

## Install

1. Install as a normal MO2 mod, or drop its `gamedata` folder into the game
   directory.
2. Load it **after** 3DSS, Boomsticks and Sharpsticks, Mark Switch, and any
   reflex-sight shader mod — it needs to win those conflicts.
3. **Delete the `appdata/shaders_cache/` folder** so the game rebuilds the
   shaders. This step is required, not optional.

## Technical details

All fixes target the same theme: HLSL that legacy FXC (Windows/DXVK) accepts but
the Metal path rejects or miscompiles.

### 1. NV scope tint — comma-operator bug (correctness + DXMT compile)

`models_scope_nv_1/2/3.ps`

```
- float3 BAS_NV_COLOR = (0.1, 1.0, 0.1);
+ float3 BAS_NV_COLOR = float3(0.1, 1.0, 0.1);
```

`(0.1, 1.0, 0.1)` is the HLSL comma operator, not a vector — it evaluates to the
last scalar (`0.1`) and splats to `(0.1, 0.1, 0.1)`, so the night-vision tint
silently collapses to grey. Legacy FXC compiles it anyway; the DXMT path can
hard-error on it. The `float3(...)` constructor is the unambiguously correct
form.

### 2. Lens sphere-projection — sqrt of a negative (NaN under DXMT)

`scope_3dss_common.h`, `models_scope_reticle.ps`,
`models_scope_reticle_precise.ps`, `models_reflex_lens.ps`

```
- sqrt(pow(radius, 2) - dot(xy, xy))
+ sqrt(max(0.0, pow(radius, 2) - dot(xy, xy)))
```

At lens-edge pixels `dot(xy,xy)` exceeds `radius²`, so the argument goes negative
and `sqrt` returns NaN. DXVK clamps/tolerates this; DXMT propagates NaN into
garbage shading at the lens rim. The `max(0.0, …)` guard clamps it. The
reflex-sight lens carries the identical math and is fixed alongside the scope
shaders.

### 3. Reflex reticle tangent-frame semantics

`models_reflex_reticle.ps`, `models_reflex_reticle_3db.ps`,
`models_reflex_reticle_simple.ps`, `models_reflex_reticle_simple_3db.ps`,
`models_lfo_light_dot_weapons.ps`. Fixes pixel-shader TEXCOORD input semantics
(P/T/B/N = TEXCOORD1/2/3/4) so they match the vertex shader, restoring
red-dot/holo reticles that vanish under D3DMetal.

### 4. Thermal scope image — uninitialized variable (NaN under DXMT)

`thermal_utils.h` (included by `models_scope_reticle.ps`). In `infrared()`,
`hot_color` was declared but only assigned inside `if (hotness > 0.0)`, then used
unconditionally in `lerp(mixed, hot_color, hotness)`. On cold pixels
(`hotness == 0`, most of a thermal scene) the value is undefined; DXVK reads it
as finite 0 (harmless), but DXMT can read garbage/NaN and `NaN * 0 = NaN`,
producing black/garbage thermal output.

```
- float hot_color;
+ float hot_color = COLOR_COLD_MAX;
```

The malformed comma-operator init on the same file is normalized alongside it
(`float3 accum = (0.0,0.0,0.0)` → `float3(0.0,0.0,0.0)`). Affects every thermal
optic (G36 RWAP Spec Ops, G3 DRS, G3 M-LOK kit, HK51 DRS, Gauss, the
K98/Rem700/M98B thermal-color "skeet" variants, 1PN93N2 thermal).

### 5. Scope depth-restore pass — partial MRT write (undefined GBuffer under Metal)

`models_scope_zwrite.ps`, `models_scope_zwrite.s`

The 3DSS depth-restore pass (`scopelense(2)`) runs during the deferred GBuffer
phase with four render targets bound (RT0 position, RT1 albedo/accumulator, RT2
heat, RT3 scope mask — the engine swaps `rt_ssfx_temp` into slot 3 for this
pass). The original shader wrote only `SV_Target3` + `SV_Depth`, leaving RT0–2
bound but unwritten — formally undefined in both D3D11 and Metal; it works today
only because translators happen to preserve unwritten attachments. The engine's
Lua API can't set per-RT write masks (`color_write_enable` applies one mask to
all four RTs), so the fix uses blending instead: the `.s` enables
`blend(true, blend.srcalpha, blend.invsrcalpha)` and the `.ps` writes all four
targets — RT0–2 with alpha 0 (blend resolves to dst, GBuffer preserved exactly)
and RT3 with alpha 1 (blend resolves to src, mask written exactly). All formats
involved (RGBA16F/RGBA8) are blendable under Metal. Depth and stencil behavior
unchanged.

### 6. Mark-grid side computation — unbounded loop

`mark_adjust.h`

`while (sides * sides < int(markswitch_count.x))` — D3D defines `int(NaN)` as 0,
Metal fast-math does not; garbage in `markswitch_count` could spin ~46k
iterations per pixel before signed-integer overflow exits the loop. macOS has no
TDR-style recovery, so a fragment shader that spins takes down the GPU until the
game or machine restarts. The constant is now clamped to `[1, 4096]`, bounding
the loop at 64 iterations.

All changes are tagged `[elseform]` in the source.

### Not addressed (low priority)

The same malformed comma-operator init `(0,0,0[,0])` exists in
`gasmask_dudv.ps`, `deffer_eft_weapon.ps`, and `water.ps`. Currently harmless
because all components are equal, but worth normalizing in case DXMT's compiler
rejects the syntax outright.

## History

This entry supersedes
`SHADER FIX - D3DMetal Missing Reflex Reticles and Scopes Fix` (last released as
v1.2.0) and additionally absorbs the `mark_adjust.h` guard from the unreleased
Metal Loop Guards work. Reinstall it in place of the old entry; there is no
migration step.
