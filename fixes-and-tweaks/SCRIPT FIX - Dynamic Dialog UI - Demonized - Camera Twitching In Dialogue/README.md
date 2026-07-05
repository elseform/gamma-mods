# SCRIPT FIX - Dynamic Dialog UI - Demonized - Camera Twitching In Dialogue

Fixes dialogue camera twitching while preserving Dynamic Dialog UI's zoom and NPC focus behavior.

## Source

- Upstream addon: `267- Dynamic Dialog UI - Demonized`
- Override: `gamedata/scripts/dialog_fov.script`

## What it changes

- Captures the NPC head focus point once when dialogue opens; never samples the animated `bip01_head` bone after that.
- Applies the captured head-height offset to the NPC root position so the camera still follows real NPC movement.
- Runs the look target through a deadzone + eased filter that rejects animation/root noise but tracks real repositioning, with stronger filtering at close range where twitching is worst.
- Filters the eye point used for direction math, breaking the feedback loop between camera sway and the look-at target.
- Skips `actor_look_at_point()` calls when the direction change is below perception (~0.3 deg), so the engine stops chasing micro-jitter.
- Uses frame-rate independent direction smoothing; the MCM smoothing setting still applies.
- Keeps dialogue zoom and `Camera focus on NPC` enabled.

## Install

Install as a normal MO2 mod, or copy this entry's `gamedata/` folder into the game directory.

## Load order

Place after `267- Dynamic Dialog UI - Demonized` so this script override wins.

## Caveats

This fix does not disable dialogue zoom or NPC focus. It only changes the focus target source from the live animated head bone to a stable head-height point derived from the NPC root position.
