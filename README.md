# Fixes / Tweaks / Mods

## D3DMetal DXMT Reflex Reticle Fix

- [Download](https://github.com/elseform/gamma-mods/releases/latest/download/D3DMetal.DXMT.Reflex.Reticle.Fix.-.elseform.7z)

- Fixes missing red-dot and holographic sight reticles under D3DMetal or DXMT.
- Corrects tangent/binormal/normal TEXCOORD semantics in affected reflex sight shaders.
- Install late in the visual/shader section and delete shaders_cache from appdata.

## Silent first-time weapon inspection

- [Download](https://github.com/elseform/gamma-mods/releases/latest/download/Silent.first-time.weapon.inspection.-.elseform.7z)

- Prevents actor voice lines from playing during weapon inspection, animations still play.
- Expects VArefined to be installed and enabled; remove the VArefined script from this mod if it is not.

## No Grain Rads Effect

- [Download](https://github.com/elseform/gamma-mods/releases/latest/download/No.Grain.Rads.Effect.-.elseform.7z)

- Disables the grainy radiation postprocess effect.
- Should load after mods that edit `gamedata/configs/zones/zone_field_radioactive.ltx`.

## Missing Assets Fixes

- [Download](https://github.com/elseform/gamma-mods/releases/latest/download/Missing.Assets.Fixes.-.elseform.7z)

- Provides small fallback assets for missing texture and sound paths.
- Fixes missing `ui_mm_faction_na` references.
- Adds compatibility aliases for missing bullet impact, dropper water, and wind sounds.

## Script Fixes

- [Download](https://github.com/elseform/gamma-mods/releases/latest/download/Script.Fixes.-.elseform.7z)

- Profile-specific script and config overrides for known load errors or incompatible hooks.
- Includes no-op overrides for disabled/incomplete integrations.
- Includes defensive fixes for selected scripts that crash on missing or invalid data.

## Force ENG Language for MCM Settings

- [Download](https://github.com/elseform/gamma-mods/releases/latest/download/Force.ENG.language.for.MCM.Settings.-.elseform.7z)

- Displays MCM labels in English without changing the rest of the game's localization.
- Applies English strings only while MCM is rendering its own UI.
- Leaves PDA, inventory, dialogue, task text, and other game UI localization untouched.
