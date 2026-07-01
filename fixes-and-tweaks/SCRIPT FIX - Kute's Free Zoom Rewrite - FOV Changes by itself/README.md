# SCRIPT FIX - Kute's Free Zoom Rewrite - FOV Changes by itself

Fixes cases where FOV, HUD FOV, or mouse sensitivity can appear to change by itself after ADS/free-zoom state is restored.

## Source

- Upstream addon: `Kute's Free Zoom Rewrite`
- Override: `gamedata/scripts/Free_ZoomV2_mcm.script`

## What it changes

- Reads the saved MCM option values for FOV, HUD FOV, and mouse sensitivity before falling back to live console values.
- Rebuilds the normal zoom baseline from persisted settings so temporary ADS/free-zoom values are not learned as the player's defaults.
- Keeps the original callback names, MCM ids, zoom key handling, and weapon zoom flow intact.

## Install

Install as a normal MO2 mod, or copy this entry's `gamedata/` folder into the game directory.

## Load order

Place after `Kute's Free Zoom Rewrite` so this script override wins.

## Caveats

This fix targets baseline drift caused by temporary zoom state. It does not intentionally change the addon keybinds, zoom multipliers, or weapon-specific HUD FOV behavior.
