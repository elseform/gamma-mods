# GAMMA Fixes and Tweaks

Small STALKER Anomaly/GAMMA override mods. Each first-level directory under `fixes-and-tweaks/` or `script-fixes/` is installable independently in Mod Organizer 2; the install root should contain that entry's `README.md` when present and `gamedata/` directly.

Downloads: [release page](<https://github.com/elseform/gamma-mods/releases>).

## Repository layout

- `fixes-and-tweaks/<Entry Name>/README.md`: install notes, load-order notes, caveats, and changed files.
- `fixes-and-tweaks/<Entry Name>/gamedata/...`: exact in-game override paths.
- `script-fixes/<Entry Name>/README.md`: install notes, load-order notes, caveats, and changed files for promoted script fixes.
- `script-fixes/<Entry Name>/gamedata/...`: exact in-game override paths for promoted script fixes.

### SHADER FIX - D3DMetal Missing Reflex Reticles and Scopes Fix

Compatibility shader overrides for running GAMMA through D3DMetal/DXMT on macOS.

- Restores red-dot and holographic sight reticles that can disappear under D3DMetal.
- Fixes scope lens-edge artifacts caused by NaN-producing sphere projection math.
- Fixes night-vision scope tint initialization for strict HLSL compilers.
- Fixes thermal scope garbage or black output caused by uninitialized cold-pixel color data.
- Load after 3DSS, Boomsticks & Sharpsticks, Parallax Reflex Sights, and any other optic shader override.
- Clear `appdata/shaders_cache/` after installing.

Path: `fixes-and-tweaks/SHADER FIX - D3DMetal Missing Reflex Reticles and Scopes Fix`

### SCRIPT FIX - Dynamic Dialog UI - Demonized - Camera Twitching In Dialogue

Script override for `267- Dynamic Dialog UI - Demonized`.

- Keeps dialogue zoom and `Camera focus on NPC` behavior enabled.
- Captures a stable NPC focus point when dialogue opens instead of sampling the animated `bip01_head` bone every frame.
- Applies the captured head-height offset to the NPC root position so the camera still follows real NPC movement.
- Load after `267- Dynamic Dialog UI - Demonized`.

Path: `script-fixes/SCRIPT FIX - Dynamic Dialog UI - Demonized - Camera Twitching In Dialogue`

### SCRIPT FIX - G.A.M.M.A. Arti Recipes Overhaul - Game Crash on Ammo Autolooter Disassembly

Script override for `G.A.M.M.A. Arti Recipes Overhaul`.

- Prevents a fatal crash when the autolooter tries to disassemble non-favorited ammo with missing or empty parts data.
- Guards empty ammo lists, missing parts sections, missing parts lists, and empty parsed parts lists before consuming ammo or degrading tools.
- Load after `G.A.M.M.A. Arti Recipes Overhaul`.

Path: `fixes-and-tweaks/SCRIPT FIX - G.A.M.M.A. Arti Recipes Overhaul - Game Crash on Ammo Autolooter Disassembly`

### SCRIPT FIX - Kute's Free Zoom Rewrite - FOV Changes by itself

Script override for `Kute's Free Zoom Rewrite`.

- Prevents temporary ADS/free-zoom FOV, HUD FOV, and mouse sensitivity values from being learned as the new baseline.
- Reads persisted MCM option values first, falling back to live console values only when saved options are unavailable.
- Load after `Kute's Free Zoom Rewrite`.

Path: `fixes-and-tweaks/SCRIPT FIX - Kute's Free Zoom Rewrite - FOV Changes by itself`

## Tweaks

### CONFIG TWEAK - No Grain Rads Effect

Config override that disables the radiation grain postprocess without changing radiation gameplay.

- Comments out `postprocess = postprocess_rad` on the base radioactive zone.
- Keeps radiation zone strengths, attenuation, hit type, and child zone definitions unchanged.
- Load after mods that edit `gamedata/configs/zones/zone_field_radioactive.ltx`.

Path: `fixes-and-tweaks/CONFIG TWEAK - No Grain Rads Effect`

### SCRIPT TWEAK - Silent First-pickup weapon inspection

Script override for first-pickup weapon inspection.

- Prevents actor voice lines from playing during weapon inspection.
- Keeps the inspection animations and first-pickup tracking behavior.
- Includes a VArefined companion override; remove `grok_doom_weapons_inspect_varefined.script` if VArefined is not installed.

Path: `fixes-and-tweaks/SCRIPT TWEAK - Silent First-pickup weapon inspection`
