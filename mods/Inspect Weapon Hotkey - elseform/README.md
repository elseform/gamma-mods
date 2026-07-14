# Inspect Weapon Hotkey

## Summary

- Adds a bindable hotkey that plays the weapon "inspect" animation on demand.
- Reuses the game's own first-pickup inspect motion (`anm_bore`), so it works on
  any weapon that ships a bore animation without per-weapon setup.
- Only fires while the weapon is idle, so it never interrupts a reload, shot, or
  weapon swap.
- Adds an MCM page under `Inspect Weapon Hotkey` with an enable toggle, key bind,
  modifier key, and press / double-tap activation.
- Ships English and Russian localization for its own MCM strings.

## How It Works

- On key press (`on_key_press`), `do_inspect()` grabs the active weapon and, if it
  is idle (`get_state() == 0`), resolves the bore animation from the weapon's HUD
  section and plays it with `play_hud_motion(anim, true, 0, 1, 0)`.
- Grenade-launcher variants are handled: `anm_bore_g` in grenade mode,
  `anm_bore_w_gl` when a GL is attached in rifle mode, otherwise `anm_bore`. It
  falls back to plain `anm_bore` and bails out cleanly if the weapon defines no
  bore animation.
- The matching `snd_bore` sound is played when present.
- A `block_repeat` flag plus a `CreateTimeEvent` restore (switching the weapon
  back to idle after the animation length) prevents spam and stuck states. This
  mirrors the proven `grok_doom_weapons_inspect` first-pickup logic.

## MCM Options (`elseform_inspect`)

- `enabled` — master toggle.
- `keybind` — inspect key, defaults to `J`.
- `modifier` — none / shift / ctrl / alt, to avoid conflicts.
- `mode` — single press or double tap.

Without MCM (or on a pre-1.6.0 version) the mod falls back to a plain single
press on the default key `J`.

## Files

- `gamedata/scripts/elseform_inspect_weapon_mcm.script`
- `gamedata/configs/text/eng/ui_st_elseform_inspect.xml`
- `gamedata/configs/text/rus/ui_st_elseform_inspect.xml`

## Dependencies

- MCM (RavenAscendant) for the configurable keybind. Optional; degrades to a
  fixed default key without it.

## Not Touched

- No changes to `/Users/elseform/gamma/flat` or to source mods under
  `/Users/elseform/gamma/g/mods`. This is a self-contained standalone mod.

## Playtest Targets

- Draw a weapon and press the key while standing idle: inspect plays.
- Press during reload / firing / aiming: nothing happens (no interrupt).
- A weapon with a GL attached, in both rifle and grenade mode.
- A weapon with no bore animation (e.g. some pistols/melee): no error, no anim.
- Rebind the key, change modifier and press/double-tap in MCM and confirm each.
