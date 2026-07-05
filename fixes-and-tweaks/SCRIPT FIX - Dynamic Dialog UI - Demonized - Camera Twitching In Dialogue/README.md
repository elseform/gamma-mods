# SCRIPT FIX - Dynamic Dialog UI - Demonized - Camera Twitching In Dialogue

Fixes dialogue camera twitching while preserving Dynamic Dialog UI's zoom and NPC focus behavior.

## Source

- Upstream addon: `267- Dynamic Dialog UI - Demonized`
- Override: `gamedata/scripts/dialog_fov.script`

## What it changes

- Captures the NPC head focus point once when dialogue opens.
- Uses a copied vector so later direction math does not mutate the saved camera target.
- Applies the captured head-height offset to the NPC root position so the camera still follows real NPC movement.
- Stops per-frame `bip01_head` animation and look-IK jitter from moving the camera target.
- Keeps dialogue zoom and `Camera focus on NPC` enabled.

## Install

Install as a normal MO2 mod, or copy this entry's `gamedata/` folder into the game directory.

## Load order

Place after `267- Dynamic Dialog UI - Demonized` so this script override wins.

## Caveats

This fix does not disable dialogue zoom or NPC focus. It only changes the focus target source from the live animated head bone to a stable head-height point derived from the NPC root position.
