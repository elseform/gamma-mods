# SCRIPT FIX - G.A.M.M.A. Arti Recipes Overhaul - Game Crash on Ammo Autolooter Disassembly

Fixes a fatal crash when the autolooter tries to disassemble non-favorited ammo and the ammo parts data is missing or empty.

## Source

- Upstream addon: `G.A.M.M.A. Arti Recipes Overhaul`
- Override: `gamedata/scripts/ammo_maker.script`

## What it changes

- Guards empty or nil ammo lists before disassembly.
- Checks for a valid first ammo item and parts section before reading parts data.
- Skips breakdown cleanly when the `parts` value is missing or parses to an empty list.
- Avoids consuming ammo or degrading tools when the breakdown cannot produce valid parts.

## Install

Install as a normal MO2 mod, or copy this entry's `gamedata/` folder into the game directory.

## Load order

Place after `G.A.M.M.A. Arti Recipes Overhaul` so this script override wins.

## Caveats

This is a crash guard for invalid ammo breakdown data. It does not add new ammo recipes or change valid recipe output.
