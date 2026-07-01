# SCRIPT TWEAK - Silent First-pickup weapon inspection

Suppresses actor voice lines during first-pickup weapon inspection while keeping the inspection animations and first-pickup tracking behavior.

## What it changes

- Overrides `gamedata/scripts/grok_doom_weapons_inspect.script`.
- Ships `gamedata/scripts/grok_doom_weapons_inspect_varefined.script` for VArefined setups.
- Replaces the voice-over call with a no-op; the animation callback flow remains intact.

## Install

Install as a normal MO2 mod, or copy this entry's `gamedata/` folder into the game directory.

## Load order

Place after the weapon inspection script source and after VArefined if VArefined is enabled.

## Caveats

- If VArefined is not installed, remove `gamedata/scripts/grok_doom_weapons_inspect_varefined.script` from this entry before installing.
- This does not remove or shorten weapon inspection animations.
