# SHADER FIX - D3DMetal Missing Reflex Reticles and Scopes Fix

A single compatibility mod that fixes broken scope, sight, and night/thermal-vision rendering when STALKER GAMMA runs through **D3DMetal / DXMT** (macOS / Apple Silicon via GPTK and similar).

---

## What it fixes

GAMMA's optic shaders were written for Windows, where the DirectX shader compiler accepts some non-standard HLSL. The Metal translation layer (D3DMetal/DXMT) is stricter and rejects or miscompiles that same code — which shows up as optics that render wrong on Mac. This mod patches the shaders so they're valid everywhere.

- **Red-dot & holographic sights** — dots/reticles that disappear now show up again, and the sight glass renders cleanly.
- **Night-vision scopes** — the image is properly lit up and not overblown / broken looking.
- **Thermal scopes** (e.g. the G36 Spec Ops) — cold areas no longer turn into black/garbage noise; you get a clean thermal picture.
- **Regular magnified scopes** — no more artifacts around the reticle/lens edge.

### Install

1. Install as a normal MO2 mod (or drop its `gamedata` folder into the game directory).
2. In your load order, put it **after** 3DSS (410), ARC 3DSS (if installed), Boomsticks & Sharpsticks (76), and any reflex-sight shader mod — it needs to win those conflicts.
3. **Delete the `appdata/shaders_cache/` folder** so the game rebuilds the shaders. This step is required, not optional.

---

## Technical details

All fixes target the same theme: HLSL that legacy FXC (Windows/DXVK) accepts but the Metal path rejects or miscompiles. The scope-rendering shaders carry only the changes below.

### 1. NV scope tint — comma-operator bug (correctness + DXMT compile)

`models_scope_nv_1/2/3.ps`

```
- float3 BAS_NV_COLOR = (0.1, 1.0, 0.1);
+ float3 BAS_NV_COLOR = float3(0.1, 1.0, 0.1);
```

`(0.1, 1.0, 0.1)` is the HLSL comma operator, not a vector — it evaluates to the last scalar (`0.1`) and splats to `(0.1, 0.1, 0.1)`, so the night-vision tint silently collapses to grey. Legacy FXC compiles it anyway; the DXMT path can hard-error on it. The `float3(...)` constructor is the unambiguously correct form.

### 2. Lens sphere-projection — sqrt of a negative (NaN under DXMT)

`scope_3dss_common.h`, `models_scope_reticle.ps`, `models_scope_reticle_precise.ps`, `models_reflex_lens.ps`

```
- sqrt(pow(radius, 2) - dot(xy, xy))
+ sqrt(max(0.0, pow(radius, 2) - dot(xy, xy)))
```

At lens-edge pixels `dot(xy,xy)` exceeds `radius²`, so the argument goes negative and `sqrt` returns NaN. DXVK clamps/tolerates this; DXMT propagates NaN into garbage shading at the lens rim. The `max(0.0, …)` guard clamps it. The reflex-sight lens (`models_reflex_lens.ps`) carries the identical math and is fixed alongside the scope shaders.

`models_scope_reticle.ps` and `models_scope_reticle_precise.ps` are based on **ARC 3DSS v1.6.7**'s versions of these files (which add `RT_DFP_ALT`, brightness-adaptive reticle via `current_lum_2`, and the blue-channel LED illumination mask), with the sqrt clamp re-applied on top — the only delta vs. ARC's copies is line 284. If ARC 3DSS updates these shaders again, rebase and re-apply the clamp.

### 3. Reflex reticle tangent-frame semantics

`models_reflex_reticle.ps`, `models_reflex_reticle_3db.ps`, `models_reflex_reticle_simple.ps`, `models_reflex_reticle_simple_3db.ps`, `models_lfo_light_dot_weapons.ps`. Fixes pixel-shader TEXCOORD input semantics (P/T/B/N = TEXCOORD1/2/3/4) so they match the vertex shader, restoring red-dot/holo reticles that vanish under D3DMetal.

### 4. Thermal scope image — uninitialized variable (NaN under DXMT)

`thermal_utils.h` (included by `models_scope_reticle.ps`). In `infrared()`, `hot_color` was declared but only assigned inside `if (hotness > 0.0)`, then used unconditionally in `lerp(mixed, hot_color, hotness)`. On cold pixels (`hotness == 0`, most of a thermal scene) the value is undefined; DXVK reads it as finite 0 (harmless), but DXMT can read garbage/NaN and `NaN * 0 = NaN`, producing black/garbage thermal output.

```
- float hot_color;
+ float hot_color = COLOR_COLD_MAX;
```

Also normalized the malformed comma-operator init on the same file (`float3 accum = (0.0,0.0,0.0)` → `float3(0.0,0.0,0.0)`; functionally identical, but valid HLSL for strict compilers). Affects every thermal optic (G36 RWAP Spec Ops, G3 DRS, G3 M-LOK kit, HK51 DRS, Gauss, the K98/Rem700/M98B thermal-color "skeet" variants, 1PN93N2 thermal).

### TODO (not yet addressed — low priority)

Same malformed comma-operator init `(0,0,0[,0])` exists in these shaders. Currently harmless because all components are equal (the collapse yields the correct zero vector), but worth normalizing to `float3(...)`/`float4(...)` in case DXMT's compiler rejects the syntax outright:

- `gamedata/shaders/r3/gasmask_dudv.ps` (line ~30)
- `gamedata/shaders/r3/deffer_eft_weapon.ps` (line ~18)
- `gamedata/shaders/r3/water.ps` (line ~55)

(`thermal_utils.h` was previously here — now fixed, see item 4 above.)

---

## Changelog

### 2026-07-05

- Rebased `models_scope_reticle.ps` and `models_scope_reticle_precise.ps` onto **ARC 3DSS v1.6.7**. The previous copies were built from an older ARC 3DSS build and, when loaded after ARC, silently reverted its newer features (`RT_DFP_ALT` reticle type, brightness-adaptive reticle, LED illumination mask). Only delta vs. ARC 1.6.7 is the sqrt NaN clamp (line 284, fix #2). ARC 1.6.7's own copies still ship the unclamped sqrt, so this mod must still load after ARC.
- Delete `appdata/shaders_cache/` after updating.

### Initial release

- Fixes #1–#4 as described above.
