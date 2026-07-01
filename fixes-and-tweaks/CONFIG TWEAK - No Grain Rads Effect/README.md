# CONFIG TWEAK - No Grain Rads Effect

Disables the visual radiation grain postprocess while keeping radiation zones and damage behavior intact.

## What it changes

- Overrides `gamedata/configs/zones/zone_field_radioactive.ltx`.
- Comments out `postprocess = postprocess_rad` on the base radioactive zone.
- Keeps the configured radiation strengths, attenuation, hit type, and zone definitions unchanged.

## Install

Install as a normal MO2 mod, or copy this entry's `gamedata/` folder into the game directory.

## Load order

Place after mods that edit `gamedata/configs/zones/zone_field_radioactive.ltx`, especially radiation or dynamic anomaly mods.

## Caveats

This is a visual-only tweak. It does not reduce radiation damage, detector behavior, anomaly behavior, or zone placement.
