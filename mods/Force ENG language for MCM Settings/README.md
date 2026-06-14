# Force ENG Language for MCM Settings

Forces Mod Configuration Menu (MCM) labels to display in English without changing the rest of the game's localization.

## What it does

- Loads English string table entries from `gamedata/configs/text/eng`.
- Applies those English strings only while MCM is rendering its own UI.
- Leaves PDA, inventory, dialogue, task text, and other game UI localization untouched.

## Why this exists

Some MCM entries are easier to use in English, even when the game language is set to Russian. This mod keeps that preference scoped to MCM's display-time translation path.

## Files

- `gamedata/scripts/elseform_mcm_english_mcm.script`

The script name ends with `_mcm.script` so MCM discovers and loads it with the normal MCM script scan.

## Notes

- If an English string is missing, the script falls back to the game's normal translation result.
- The English string cache is built lazily the first time MCM needs it.
- No `on_xml_read` hook is used.
