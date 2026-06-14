# No Grain Rads Effect

Disables the annoying visual radiation postprocess effect while keeping radiation zones and damage behavior intact.

## What it changes

- Overrides `gamedata/configs/zones/zone_field_radioactive.ltx`.
- Comments out `postprocess = postprocess_rad` on the base radioactive zone.
- Keeps the configured radiation strengths, attenuation, hit type, and zone definitions unchanged.

## Load order

Place after mods that edit `gamedata/configs/zones/zone_field_radioactive.ltx`, especially radiation or dynamic anomaly mods.
