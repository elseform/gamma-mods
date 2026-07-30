# GAMMA Mods, Fixes & Tweaks

Small standalone mods and targeted fixes for STALKER Anomaly/GAMMA.

## Download & install

Download ready-to-install archives from the [release page](https://github.com/elseform/gamma-mods/releases), then add them to Mod Organizer 2. Check the individual mod notes for any load-order or compatibility requirements.

## Usage and permissions

You may include any of my mods or tweaks in your own mods / modpacks, provided that you credit me and link back to this repository.
Although asking permission or letting me know is not required - I would love to know if you decide to use any of my work, so hit me up on Discord's GAMMA server.

This permission covers my original work only. Third-party code and assets keep their original authors' permissions and requirements.

## Standalone mods

### [Flashing Inventory Highlights (FIH)](<mods/Flashing Inventory Highlights - elseform/README.md>)

Adds pulsating flash for inventory / trading grid instead of a static highlight.

Features customizable options:

- Five pulse/fade timing presets and optional custom timing.
- Post-unhover linger that reaches the next pulse crest before fading out.
- Minimum and maximum brightness.
- Color presets and optional custom RGB sliders.

[Source and notes](<mods/Flashing Inventory Highlights - elseform/README.md>)

Special thanks to **kingofthebeats** from the GAMMA Discord server for suggesting lingering highlights.

### [It's Time To Stop (ITTS)](<mods/Its Time To Stop - elseform/README.md>)

Tracks real-world playtime and helps you keep sessions from running longer than intended.

- Adds total playtime and current-session rows to the PDA ranking tab.
- Adds an optional real-life HUD clock with configurable placement, fonts, and colors.
- Sends configurable session-threshold reminders, with optional repeats and a PDA beep.
- Can progressively change the HUD clock color as a session crosses its warning thresholds.
- Offers Full, HUD-clock-only, and playtime-statistics-only MO2 installer presets, with no load-order requirements or dependencies beyond stock GAMMA.

[Source and notes](<mods/Its Time To Stop - elseform/README.md>)

### [Inspect Weapon Hotkey](<mods/Inspect Weapon Hotkey - elseform/README.md>)

Adds a configurable hotkey that plays the current weapon's existing inspect animation on demand.

- Uses each weapon's own bore animation and sound, including grenade-launcher variants.
- Only starts while the weapon is idle, avoiding reload, firing, and weapon-swap interruptions.
- Provides MCM settings for enable state, key, modifier, and single-press or double-tap activation.
- Includes English and Russian localization and falls back to `J` when MCM is unavailable.

[Source and notes](<mods/Inspect Weapon Hotkey - elseform/README.md>)

## Fixes

### [D3DMetal Missing Reflex Reticles and Scopes Fix](<fixes-and-tweaks/SHADER FIX - D3DMetal Missing Reflex Reticles and Scopes Fix/README.md>)

Compatibility shader overrides for running GAMMA through D3DMetal/DXMT on macOS.

- Restores red-dot and holographic sight reticles that can disappear under D3DMetal.
- Fixes scope lens-edge artifacts caused by NaN-producing sphere projection math.
- Fixes night-vision scope tint initialization for strict HLSL compilers.
- Fixes thermal scope garbage or black output caused by uninitialized cold-pixel color data.
- Load after 3DSS, Boomsticks & Sharpsticks, Parallax Reflex Sights, and any other optic shader override.
- Clear `appdata/shaders_cache/` after installing.

[Source and notes](<fixes-and-tweaks/SHADER FIX - D3DMetal Missing Reflex Reticles and Scopes Fix/README.md>)

### [G.A.M.M.A. Arti Recipes Overhaul — Ammo Autolooter Crash Fix](<fixes-and-tweaks/SCRIPT FIX - G.A.M.M.A. Arti Recipes Overhaul - Game Crash on Ammo Autolooter Disassembly/README.md>)

Script override for `G.A.M.M.A. Arti Recipes Overhaul`.

- Prevents a fatal crash when the autolooter tries to disassemble non-favorited ammo with missing or empty parts data.
- Guards empty ammo lists, missing parts sections, missing parts lists, and empty parsed parts lists before consuming ammo or degrading tools.
- Load after `G.A.M.M.A. Arti Recipes Overhaul`.

[Source and notes](<fixes-and-tweaks/SCRIPT FIX - G.A.M.M.A. Arti Recipes Overhaul - Game Crash on Ammo Autolooter Disassembly/README.md>)

### [Kute's Free Zoom Rewrite — FOV Changes by Itself Fix](<fixes-and-tweaks/SCRIPT FIX - Kute's Free Zoom Rewrite - FOV Changes by itself/README.md>)

Script override for `Kute's Free Zoom Rewrite`.

- Prevents temporary ADS/free-zoom FOV, HUD FOV, and mouse sensitivity values from being learned as the new baseline.
- Reads persisted MCM option values first, falling back to live console values only when saved options are unavailable.
- Load after `Kute's Free Zoom Rewrite`.

[Source and notes](<fixes-and-tweaks/SCRIPT FIX - Kute's Free Zoom Rewrite - FOV Changes by itself/README.md>)

## Tweaks

### [No Grain Rads Effect](<fixes-and-tweaks/CONFIG TWEAK - No Grain Rads Effect/README.md>)

Config override that disables the radiation grain postprocess without changing radiation gameplay.

- Comments out `postprocess = postprocess_rad` on the base radioactive zone.
- Keeps radiation zone strengths, attenuation, hit type, and child zone definitions unchanged.
- Load after mods that edit `gamedata/configs/zones/zone_field_radioactive.ltx`.

[Source and notes](<fixes-and-tweaks/CONFIG TWEAK - No Grain Rads Effect/README.md>)

### [Silent First-pickup Weapon Inspection](<fixes-and-tweaks/SCRIPT TWEAK - Silent First-pickup weapon inspection/README.md>)

Script override for first-pickup weapon inspection.

- Prevents actor voice lines from playing during weapon inspection.
- Keeps the inspection animations and first-pickup tracking behavior.
- Includes a VArefined companion override; remove `grok_doom_weapons_inspect_varefined.script` if VArefined is not installed.

[Source and notes](<fixes-and-tweaks/SCRIPT TWEAK - Silent First-pickup weapon inspection/README.md>)

## Repository layout

- `mods/`: standalone elseform-authored mods.
- `fixes-and-tweaks/`: targeted fixes and optional behavior tweaks.
- `script-fixes-tweaks/`: promoted script fixes and tweaks when applicable.
- Each entry keeps its install notes and original `gamedata/` paths inside its own folder.
