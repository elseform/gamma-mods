# Script & Config fixes

These are not intended for everyone, use only when there is a need to.

## `scripts/a_faction_prices.script`

Source conflict:

- `G.A.M.M.A. UI/gamedata/scripts/a_faction_prices.script`

Current behavior:

- Replaces the source script with a no-op file.
- The override contains only a comment:
  `-- No-op override: disabled incomplete Haruka faction economy pricing hook.`

Purpose:

- The original script was producing script-load errors in this profile.
- Investigation showed the script looked like an incomplete or profile-incompatible Haruka faction economy pricing hook.
- Rather than trying to run incomplete economy logic, this profile disables the hook cleanly.

Gameplay impact:

- Prevents the faulty faction-pricing script from loading.
- Disables whatever price adjustment behavior that incomplete hook would have provided.

Caveats:

- If the upstream `a_faction_prices.script` is later fixed and wanted, this no-op override should be removed or rebuilt from the updated source.

## `scripts/mags_patches.script`

Source conflict:

- `433- UDP-9 Carbine - Pilliii/gamedata/scripts/mags_patches.script`

Current behavior:

- Replaces UDP-9's magazine integration script with a no-op file.

Purpose:

- UDP-9 ships a `mags_patches.script` integration for Mags Redux.
- This profile does not enable the magazine framework.
- The original integration script can still load and reference missing magazine globals, causing script-load errors.

Gameplay impact:

- UDP-9 remains usable in a non-magazines profile.
- Mags Redux integration for UDP-9 is intentionally disabled.

Caveats:

- If the magazine framework is enabled later, this no-op override should be removed.

## `scripts/zz_ui_inventory_better_stats_bars.script`

Source conflicts:

- `UI Rework G.A.M.M.A. Style v1.6.3_beta1/gamedata/scripts/zz_ui_inventory_better_stats_bars.script`
- `G.A.M.M.A. Keybinds fixes/gamedata/scripts/zz_ui_inventory_better_stats_bars.script`

Current behavior:

- Replaces the controller script with a no-op comment.

Purpose:

- Better Stats Bars is not enabled/usable in this profile.
- Sota UI also ships this script as a disabled placeholder saying the addon is no longer compatible.
- The Small no-op keeps the profile explicit: this controller is intentionally disabled.

Gameplay impact:

- Prevents Better Stats Bars controller logic from running.
- Does not disable Sota's own inventory stats UI; this only covers the old Better Stats Bars controller path.

Caveats:

- This override is currently redundant with Sota beta1's disabled placeholder, but harmless.

## `scripts/ammo_maker.script`

Source conflicts:

- `G.A.M.M.A. Arti Recipes Overhaul/gamedata/scripts/ammo_maker.script`
- `145- Ammo Maker - arti/gamedata/scripts/ammo_maker.script`

Current behavior:

- Keeps the Ammo Maker batch-disassembly feature and custom inventory context-menu hooks.
- Adds defensive handling around empty/missing ammo recipe data.
- Uses `parts = part_lookup:r_value(sec, "parts") or ""` and treats a missing parts list as an empty map instead of crashing during `str_explode`.
- Logs debug messages when breakdown is skipped because `ammo_list` is empty or recipe data is missing.
- Keeps the custom UI hooks:
  - `ui_inventory.UIInventory:Name_Custom`
  - `ui_inventory.UIInventory:Action_Custom`
- Uses context action slot `i == 4` for ammo batch breakdown.

Purpose:

- Fixes crashes around ammo disassembly when the script encounters ammo sections without valid recipe/parts data.
- Keeps batch ammo breakdown available through the inventory UI.

Gameplay impact:

- Ammo disassembly should fail gracefully instead of crashing on invalid data.
- The amount and type of returned parts are still driven by `parts\importer.ltx`.
- The script still degrades the disassembly tool and creates returned ammo/parts after the disassembly delay.

Caveats:

- This file is a broad script override, not a tiny patch.
- It should be rechecked if either Ammo Maker or GAMMA Arti Recipes Overhaul updates.
- The debug logging is useful for diagnosis but may be noisier than a final polished fix.

## `scripts/illish/lib/npc.lua`

Source conflict:

- `450- Useful Idiots - bellyillish/gamedata/scripts/illish/lib/npc.lua`

Current behavior:

- Rewrites `NPC.getCompanions()` to avoid Lua `goto` labels and to guard `squad` / `commander_id` access more directly.
- The companion loop now checks:
  - the squad exists,
  - the squad has a commander id,
  - the squad commander is not a hostage.

Purpose:

- Fixes a Useful Idiots companion scan crash seen in this profile.
- Keeps the function's intended behavior: return valid current companions, sorted by actor id.

Gameplay impact:

- Useful Idiots companion logic should continue to work.
- Hostage squads are still excluded.

Caveats:

- This is a full-file override of a nested library path. Recheck if Useful Idiots updates.

### `scripts/zzz_mspizza_godis_zoomcalc.script`

Source conflict:

- `410- 3DSS for GAMMA - Redotix99 & Andtheherois & party50/gamedata/scripts/zzz_mspizza_godis_zoomcalc.script`

Current behavior:

- Keeps Godis/mspizza zoom calculation behavior.
- Uses the lowercase filename expected by the engine and profile.
- Replaces invalid Lua block-comment syntax with valid Lua comments.
- Disables the debug F5 key bind by commenting out the bind setup.

Purpose:

- Fixes script-load errors caused by invalid comment syntax.
- Prevents the debug F5 bind from being registered.

Gameplay impact:

- Dynamic scope zoom calculation remains available.
- Debug printing is disabled.

Caveats:

- The source script should be rechecked if 3DSS updates its scope zoom handling.

## `scripts/zzz_mspizza_godis_zoom_control.script`

Source conflict:

- `410- 3DSS for GAMMA - Redotix99 & Andtheherois & party50/gamedata/scripts/zzz_mspizza_godis_zoom_control.script`

Current behavior:

- Keeps Godis/mspizza zoom-control behavior.
- Uses the lowercase filename expected by the engine and profile.
- Disables the debug F5 key bind by commenting out the bind setup.

Purpose:

- Prevents the broken/debug F5 callback from registering.
- Keeps zoom-control logic active.

Gameplay impact:

- Dynamic zoom behavior remains active.
- F5 debug output is disabled.

Caveats:

- Recheck if 3DSS updates its zoom-control script.

## Config Tweaks

### `configs/items/settings/npc_loadouts/npc_loadouts__name.ltx`

Source conflicts:

- `G.A.M.M.A. NPC Loadouts`
- `29- Dux's Innemurable Characters Kit - DuxFortis`

Current behavior:

- Defines name-based NPC loadout overrides for several military, Monolith, and ISG NPC sections.
- Replaces an invalid `wpn_usp_match:4:r` reference with `wpn_usp:4:r`.
- Comments out or replaces several debug-only / unavailable GAMMA weapon references.

Purpose:

- Prevents NPC loadout warnings/errors from invalid weapon section names.
- Keeps the intended NPC role loadouts while avoiding missing-section references.

Gameplay impact:

- Affected NPCs receive valid weapon entries.
- The specific invalid USP Match reference is replaced by a standard USP.

Caveats:

- If weapon packs change, these loadouts should be rechecked.

### `configs/scripts/evac/smart/pri_a28_school.ltx`

Source conflict:

- `G.A.M.M.A. NPC Spawns/gamedata/configs/scripts/evac/smart/pri_a28_school.ltx`

Current behavior:

- Adds a missing `[spawn_isg]` section.
- The section spawns:
  - `isg_sim_squad_advanced`
  - `isg_sim_squad_veteran`
- Uses the same `living_legend_psy_helmet` condition pattern as nearby spawn sections.

Purpose:

- Fixes log errors where the smart terrain referenced `spawn_isg` but the section did not exist.

Gameplay impact:

- Prevents missing-section errors for the Pripyat school evacuation smart terrain.
- Allows the referenced ISG spawn path to resolve normally.

Caveats:

- This is a spawn/smart-terrain config override. Existing saves may already have some smart-terrain state serialized, but the fix is primarily for config resolution.

## Maintenance Checklist

Recheck this mod when any of the following source mods are updated:

- `UI Rework G.A.M.M.A. Style`
- `G.A.M.M.A. Arti Recipes Overhaul`
- `145- Ammo Maker - arti`
- `450- Useful Idiots - bellyillish`
- `410- 3DSS for GAMMA`
- `433- UDP-9 Carbine - Pilliii`
- `G.A.M.M.A. NPC Loadouts`
- `G.A.M.M.A. NPC Spawns`
- `Dynamic Anomalies Overhaul`
- `G.A.M.M.A. Radiation Dynamic Areas`
