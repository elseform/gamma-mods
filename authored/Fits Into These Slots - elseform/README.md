# Fits Into These Slots

## Summary

- Lets whitelisted weapons be equipped into the pistol slot (base slot 2) or
  the binoculars slot (base slot 5), on top of whatever their own `slot =`
  already allows.
- No manual weapon-name lookup: right-click any eligible weapon in inventory
  for an "allow extra slot" toggle, which writes the choice straight into
  `gamedata/configs/plugins/zzzz_elseform_ees_slots.ltx`.
- The toggle only appears on weapons that aren't already default-eligible for
  the target slot — an already-eligible pistol or binocular never needs an
  entry.
- A weapon can be allowed into both the pistol and binoculars slot at once.
- Adds an MCM page under `FITS` with two cosmetic checkboxes: show/hide the
  right-click option, and whether it renders in the mod's purple or the
  default context-menu color.

## How It Works

- Right-click hooks in through `custom_functor_autoinject.script` (the same
  right-click-action API Neat Usability Tweaks uses) and offers "Allow:
  Pistol Slot" / "Allow: Binoculars Slot" per eligible weapon.
- Allow-lists load once from the ltx at startup into plain Lua tables, and
  stay there for the whole session; toggling writes straight to disk via
  `io.open` so the choice persists for the next launch. The ltx stays
  hand-editable too — the toggle is just a faster way to populate it.
- Patches `Action_Equip`, the "Ruck/Slot to Slot" drag/drop branch, and the
  hover-highlight block in `ui_inventory.script` so each independently
  recognizes the extra cell for an allowed weapon. Each wraps `slot_cell`
  temporarily, so the extra cell only opens up for that one item, not every
  weapon sharing its base slot.
- Detector fallback is handled as an exception: switching a weapon into an
  EES slot can make the engine's own detector-key fallback search select the
  EES slot itself instead of falling back to the bolt. FITS intercepts that
  key press, switches to the bolt itself, and shows the detector only once
  the inventory finishes its deferred slot transition.

## MCM Options (`elseform_ees`)

- `show_menu_toggle` — show/hide the "allow extra slot" right-click entry.
- `colored_menu_text` — render that entry (and its submenu) in purple instead
  of the default context-menu color.

Neither option enables or disables an already-allowed weapon; a weapon
toggled on in the ltx keeps working in its extra slot even with the menu
hidden.

## Files

- `gamedata/scripts/zzzz_elseform_ees_slots.script`
- `gamedata/scripts/zzzz_elseform_ees_mcm.script`
- `gamedata/configs/plugins/zzzz_elseform_ees_slots.ltx`
- `gamedata/configs/text/eng/zzzz_elseform_ees_slots.xml`
- `gamedata/configs/text/rus/zzzz_elseform_ees_slots.xml`

## Dependencies

- MCM (RavenAscendant) for the two cosmetic checkboxes. Optional; the
  right-click toggle itself works without it.