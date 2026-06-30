# Fixes / Tweaks / Mods

## Fixes

### D3DMetal DXMT Scopes & Reflex Reticles Fix

- [Download](https://github.com/elseform/gamma-mods/releases)

- **Red-dot & holographic sights** — dots/reticles that disappear now show up again, and the sight glass renders cleanly.
- **Night-vision scopes** — the image is properly lit up and not overblown / broken looking.
- **Thermal scopes** (e.g. the G36 Spec Ops) — cold areas no longer turn into black/garbage noise; you get a clean thermal picture.
- **Regular magnified scopes** — no more artifacts around the reticle/lens edge.

### SCRIPT FIX - Kute's Free Zoom Rewrite - FOV Changes by itself

Solves the issue of FOV changing by itself randomly.

Source: `Kute's Free Zoom Rewrite`
`gamedata/scripts/Free_ZoomV2_mcm.script`

- Reads FOV, HUD FOV, and mouse sensitivity from persisted option values instead of the current live console values. This prevents temporary ADS/free-zoom state from being learned as the new baseline and later restored as an apparently random FOV change.

### SCRIPT FIX - G.A.M.M.A. Arti Recipes Overhaul - Game Crash on Ammo Autolooter Disassembly

Fixes a fatal crash when autolooter's option to disassemble not favorited ammo is enabled.

Source: `G.A.M.M.A. Arti Recipes Overhaul`
`gamedata/scripts/ammo_maker.script`

- Guards empty ammo lists, missing parts sections, and missing/empty parts lists before consuming ammo or degrading tools.

## Tweaks

### Silent first-time weapon inspection

- [Download](https://github.com/elseform/gamma-mods/releases/tag/v2026.06.14)

- Prevents actor voice lines from playing during weapon inspection, animations still play.
- Expects VArefined to be installed and enabled; remove the VArefined script from this mod if it is not.

### No Grain Rads Effect

- [Download](https://github.com/elseform/gamma-mods/releases/tag/v2026.06.14)

- Disables the grainy radiation postprocess effect.
- Should load after mods that edit `gamedata/configs/zones/zone_field_radioactive.ltx`.
