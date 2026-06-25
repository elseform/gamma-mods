# Changelog

## v1.0

First release. Fixes scope, sight, and night/thermal-vision rendering under D3DMetal / DXMT. All changes are compatibility-only — no gameplay or visual behavior changes versus stock.

**Fixed**

- **NV scope tint** (`models_scope_nv_1/2/3.ps`) — comma-operator init `(0.1,1.0,0.1)` → `float3(0.1,1.0,0.1)`; the night-vision tint no longer collapses to grey / fails to compile under DXMT.
- **Lens sphere-projection** (`scope_3dss_common.h`, `models_scope_reticle.ps`, `models_scope_reticle_precise.ps`, `models_reflex_lens.ps`) — `sqrt(...)` → `sqrt(max(0.0, ...))`; clamps the NaN that produced garbage shading at the lens rim.
- **Reflex reticle tangent-frame** (`models_reflex_reticle.ps`, `models_reflex_reticle_3db.ps`, `models_reflex_reticle_simple.ps`, `models_reflex_reticle_simple_3db.ps`, `models_lfo_light_dot_weapons.ps`) — corrected pixel-shader TEXCOORD semantics so red-dot/holo reticles render under D3DMetal.
- **Thermal scope image** (`thermal_utils.h`) — initialized `hot_color` (`= COLOR_COLD_MAX`) to avoid NaN on cold pixels; normalized the `float3 accum` comma-init.

**Intentionally excluded**

- `RT_DFP_ALT` (reticle type 10) — unused, would be dead code.
- `current_lum_2()` / `lum_2` — dead code.
- `RT_DFP` zoom-condition tweak — left at stock 3DSS behavior.
- `RT_DFP` illumination-mask change — alters the Cortex Sight reticle; not a compatibility fix.

**Ships** 13 shader files.
