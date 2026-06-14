# Fixes / Tweaks / Mods

## D3DMetal DXMT Reflex Reticle Fix

- [Download latest release archive](https://github.com/elseform/gamma-mods/releases/latest/download/D3DMetal%20DXMT%20Reflex%20Reticle%20Fix%20-%20elseform.7z)

- Fixes missing red-dot and holographic sight reticles under D3DMetal or DXMT.
- Corrects tangent/binormal/normal TEXCOORD semantics in affected reflex sight shaders.
- Install late in the visual/shader section and delete shaders_cache from appdata.

## Silent first-time weapon inspection

- [Download latest release archive](https://github.com/elseform/gamma-mods/releases/latest/download/Silent%20first-time%20weapon%20inspection%20-%20elseform.7z)

- Prevents actor voice lines from playing during weapon inspection, animations still play.
- Expects VArefined to be installed and enabled; remove the VArefined script from this mod if it is not.

## No Grain Rads Effect

- [Download latest release archive](https://github.com/elseform/gamma-mods/releases/latest/download/No%20Grain%20Rads%20Effect%20-%20elseform.7z)

- Disables the grainy radiation postprocess effect.
- Should load after mods that edit `gamedata/configs/zones/zone_field_radioactive.ltx`.

## Missing Assets Fixes

- [Download latest release archive](https://github.com/elseform/gamma-mods/releases/latest/download/Missing%20Assets%20Fixes%20-%20elseform.7z)

- Provides small fallback assets for missing texture and sound paths.
- Fixes missing `ui_mm_faction_na` references.
- Adds compatibility aliases for missing bullet impact, dropper water, and wind sounds.

## Script Fixes

- [Download latest release archive](https://github.com/elseform/gamma-mods/releases/latest/download/Script%20Fixes%20-%20elseform.7z)

- Profile-specific script and config overrides for known load errors or incompatible hooks.
- Includes no-op overrides for disabled/incomplete integrations.
- Includes defensive fixes for selected scripts that crash on missing or invalid data.

## Force ENG Language for MCM Settings

- [Download latest release archive](https://github.com/elseform/gamma-mods/releases/latest/download/Force%20ENG%20language%20for%20MCM%20Settings%20-%20elseform.7z)

- Displays MCM labels in English without changing the rest of the game's localization.
- Applies English strings only while MCM is rendering its own UI.
- Leaves PDA, inventory, dialogue, task text, and other game UI localization untouched.
