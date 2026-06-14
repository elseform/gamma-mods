# Missing Assets fixes

Intended for cleaning up warnings about missing assets. Warnings are harmless for the most part, so if you do not get triggered by red lines in logs - don't install this.

## Configs

### `configs/ui/textures_descr/ui_mm_faction_na.xml`

Source conflict:

- None directly; this is a new descriptor for a missing texture id.

Current behavior:

- Defines texture descriptor `ui_mm_faction_na`.
- Points the descriptor to `ui\ui_mm_faction_na`.
- Uses a 64x64 texture rect.

Purpose:

- Fixes missing texture references for the unknown/NA faction icon.

Gameplay impact:

- UI elements that request `ui_mm_faction_na` can resolve a valid texture.

Caveats:

- The texture itself is supplied separately in `textures/ui/ui_mm_faction_na.dds`.

## Textures

### `textures/ui/ui_mm_faction_na.dds`

Source conflict:

- None directly. This is a supplied fallback texture.

Current behavior:

- Adds a 64x64 DXT5 DDS icon for the unknown/NA faction.
- Used by `configs/ui/textures_descr/ui_mm_faction_na.xml`.

Purpose:

- Fixes missing `ui_mm_faction_na` texture errors.

Gameplay impact:

- Unknown/NA faction UI elements display an icon instead of logging a missing texture.

Caveats:

- The source art was selected as a suitable fallback from another project. It is a substitute, not necessarily an upstream canonical GAMMA asset.

## Sounds

### Missing bullet impact aliases

Files:

- `sounds/material/bullet/collide/bullet_hit_dirt_02.ogg`
- `sounds/material/bullet/collide/bullet_hit_dirt_03.ogg`

Current behavior:

- Provides missing bullet-hit dirt sound files expected by configs/scripts.

Purpose:

- Fixes missing sound warnings for dirt bullet impacts.

Gameplay impact:

- Bullet impacts that request these paths can play a valid sound.

Caveats:

- These are alias/override files intended to satisfy missing path references.

### Missing dropper water alias

File:

- `sounds/material/dropper/collide/collide/water_1.ogg`

Current behavior:

- Provides the nested `dropper/collide/collide/water_1.ogg` path expected by the game.

Purpose:

- Fixes a missing water collision sound reference.

Gameplay impact:

- The referenced dropper water collision event can resolve a sound file.

Caveats:

- The duplicated `collide/collide` path is intentional because it matches the logged missing path.

### Missing wind aliases

Files:

- `sounds/nature/wind_05.ogg`
- `sounds/nature/wind_07.ogg`

Current behavior:

- Provides missing wind sound files.

Purpose:

- Fixes missing nature/wind sound warnings.

Gameplay impact:

- Weather/ambient sound events that request these paths can play valid audio.

Caveats:

- These are compatibility aliases for missing paths.
