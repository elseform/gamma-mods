# Fits Into These Slots

## Summary

- Lets whitelisted weapons be equipped into the pistol slot (base slot 2) or
  the binoculars slot (base slot 5), on top of whatever their own `slot =`
  already allows.
- No manual weapon-name lookup: right-click any eligible weapon in inventory
  for an "allow extra slot" toggle, which writes the choice straight into
  `gamedata/configs/plugins/elseform_fits_slots.ltx`.
- The toggle only appears on weapons that aren't already default-eligible for
  the target slot — an already-eligible pistol or binocular never needs an
  entry.
- A weapon can be allowed into both the pistol and binoculars slot at once.
- Adds an MCM page under `FITS`: a master on/off checkbox, a mode list
  (Allowlist / Rank-based), and an Allowlist-only checkbox for whether the
  right-click option is colored.
- Optional **Rank-based mode**: instead of the per-weapon allow-list, slots
  are earned by rank — Experienced unlocks pistols in the binoculars slot,
  Professional puts shotguns in the knife slot, Veteran adds SMGs there,
  Expert adds shotguns to the binoculars slot, Master adds SMGs there, and
  Legend opens every weapon kind to both slots. Each unlock
  announces itself in the PDA on rank-up.

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
- Detector fallback is handled as an exception: the engine's own
  detector-key fallback always prefers whatever is in the knife slot over the
  bolt, without checking it's actually a knife — so a weapon FITS parked in
  the pistol or knife slot gets wrongly reactivated instead of the bolt.
  FITS intercepts that key press, switches to the bolt itself, and shows the
  detector only once the inventory finishes its deferred slot transition.

## MCM Options (`elseform_fits`)

- `enabled` — FITS enabled. While off, no weapon gets an extra slot in either
  mode, the right-click entry is hidden, the detector override is skipped, and
  no rank tips are posted. Nothing is written or cleared.
- `mode` — `Allowlist` (default): per-weapon list built with the right-click
  entry. `Rank-based`: slots earned by rank, right-click entry hidden.
- Allowlist section: `colored_menu_text` — render the right-click entry (and
  its submenu) in the mod's color instead of the default context-menu color.

## Rank-based Mode

Off by default (the mode list defaults to Allowlist). While it's selected, the per-weapon ltx allow-list is ignored
entirely and allowances come from the actor's rank and the weapon's `kind`:

| Rank | Unlocks |
| --- | --- |
| Rookie / Trainee | nothing |
| Experienced | `w_pistol` → binoculars slot |
| Professional | `w_shotgun` → pistol (knife) slot |
| Veteran | `w_smg` → pistol (knife) slot |
| Expert | `w_shotgun` → binoculars slot |
| Master | `w_smg` → binoculars slot |
| Legend | every kind (`w_melee`, `w_pistol`, `w_smg`, `w_shotgun`, `w_rifle`, `w_sniper`) in both slots |

Unlocks are cumulative — a Master keeps everything Experienced through Expert
earned. There is no melee tier below Legend: GAMMA's `binoc_pistol_knife.script`
already lets every knife-slot item into the binoculars slot. Rank tiers and their thresholds are read from
`configs/creatures/game_relations.ltx`, so a modded rating line still resolves.

The two modes are mutually exclusive, not additive. The right-click toggle is
hidden while Rank-based mode is selected, because it writes an ltx that this
mode doesn't read. Switching either way never touches that ltx, so the
hand-picked list survives untouched and comes straight back when Allowlist is
selected again.
A weapon already sitting in an extra slot when the mode changes isn't forced
out of it — it just can't be re-equipped there if the now-active mode doesn't
allow it.

On each rank-up that unlocks something, FITS posts its own PDA tip saying what
was granted. That's a separate message from the game's own rank-up notice, sent
with the game's built-in weapon-category icon.

## Files

- `gamedata/scripts/zzzz_elseform_fits_slots.script`
- `gamedata/scripts/elseform_fits_mcm.script`
- `gamedata/configs/plugins/elseform_fits_slots.ltx`
- `gamedata/configs/plugins/mod_news_tips_icons_fits.ltx`
- `gamedata/configs/text/eng/elseform_fits_slots.xml`
- `gamedata/configs/text/rus/elseform_fits_slots.xml`

## Dependencies

- MCM (RavenAscendant) for the two cosmetic checkboxes. Optional; the
  right-click toggle itself works without it.

## Changelog

- **1.1.0** — Added Rank-based mode: slots earned automatically by rank and
  weapon kind, as an alternative to the per-weapon allow-list. Reworked the
  MCM page into an enable switch, a mode list, and an Allowlist-only section.
  Rank-up unlocks now post their own PDA tip using the built-in weapon-category
  icon.
- **1.0.1** — Fixed detector-key fallback wrongly reactivating a FITS-parked
  weapon (in the pistol or knife slot) instead of switching to the bolt, when
  both slots were occupied. Root cause: the engine's own fallback search
  always prefers the knife slot over the bolt without checking it holds a
  real knife.
- **1.0.0** — Initial release.
