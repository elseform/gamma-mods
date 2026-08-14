# Custom Mod Categories

## Summary

CMC replaces MCM's long flat mod list with a category browser whose assignments
are chosen by the user. It works in a flattened installation and does not use
MO2 metadata, original mod folders, file provenance, or classification rules.

Open **MCM**, select the green **Organize mods** entry below **Logging**, choose
a category for each discovered MCM page, and press **Apply**. The first MCM
opening starts at **MCM > About**; later openings restore the last real page.
Every normal mod page also has a CMC **Category** dropdown in the fixed header
above the scrolling options, including nested pages. On pages with a native MCM
preset, the header is shared by both dropdowns. Category changes use MCM's
normal **Apply**, **Reset**, and **Cancel** flow and do not modify the original
mod's option tree. After Apply commits the changes, CMC returns to the category
root on the next UI frame so native controls are not rebuilt inside the button
callback. New and unassigned pages appear in both **All mods** and the
hide-when-empty **Uncategorized** inbox until the user sorts them.

## Default Categories

CMC embeds assignments for all 109 MCM pages curated in its development
profile. On first launch, CMC writes those explicit assignments immediately;
it does not write empty `Uncategorized` values. On the **Organize mods** page,
MCM's standard **Default** button stages the same mapping. Press **Apply** to
save staged defaults, or **Reset**/**Cancel** to discard them. Assignments for
pages that are not installed remain dormant and return automatically if the
mod is reinstalled. Newly discovered pages without an embedded assignment
appear in **Uncategorized**.

**Clear all categories** stages every discovered page as Uncategorized. Press
**Apply** to remove their stored `[cmc]` assignments, or **Reset**/**Cancel** to
discard the staged clear.

Existing option paths are left unchanged, so saved mod values, callbacks,
presets, keybinds, and `ui_mcm.open_to()` callers continue to address the same
settings.

The override also disables MCM's always-on per-row console debug prints. Those
prints produced hundreds of synchronous log writes while opening large lists;
the explicit MCM `debug_logging2` option remains available for diagnostics.

## Keybind Display

Two small corrections to MCM's keybind handling, both in the same overridden
`ui_mcm.script`:

- Key codes with no entry in `mcm_key_localization.ltx` used to display the
  literal placeholder `<!!!>`, which identified neither the key nor its code.
  They now display `Key <code>`, so an unrecognized key can be read off the
  screen and named in the localization file. Named keys are unaffected.
- Caps Lock is no longer refused as a bindable key. MCM blocked code `58` with
  the comment that its author did not know how the toggle behaved; the other
  blocked codes, Escape and the three main mouse buttons, are unchanged and
  still reserved.

Header placement follows the preset and option-list geometry supplied by the
active `ui_mcm.xml`. This supports both stock MCM and Sota UI Rework without
hardcoding either layout. Inline color controls used by some mod titles are
removed only from the organizer's plain-text captions so stock MCM does not
display raw `%c[...]` controls; their colored tree names remain unchanged.

## Categories

- Favorites (always first, amber)
- User Interface
- Gameplay
- Graphics
- Crafting & Repair
- Items & Inventory
- Weapons
- PDA & Tasks
- Audio
- Animations
- Controls & Camera
- World & Environment
- AI & NPCs
- System & Utilities
- Other

The first page starts with the pinned **MCM** entry, followed by amber
**Favorites**, muted blue-gray **All mods**, the non-empty assigned categories,
and muted cyan **Uncategorized** at the bottom when it contains pages.
**Organize mods** is the final entry
inside MCM's own menu and is colored green. Search ignores the selected category
and searches the complete MCM list. Empty and placeholder search text always
returns to the category root, including after Apply. **Other** is an ordinary
explicit category; **Uncategorized** is a smart inbox rather than a stored
category.

Opening the organizer creates one native combo box per discovered MCM page;
removing that initial construction pause on very large lists would require a
paged or virtualized organizer redesign.

## Storage

Explicit assignments use a dedicated section and the original top-level MCM ID:

```ini
[cmc]
lower_weapon_sprint = 6
```

The stored value is the selected category number. Other is stored explicitly as
`0`; a missing entry means Uncategorized and appears in its smart inbox and All
mods. The organizer and per-page selector do not move or rename the original MCM
option tree.

## Installation and Load Order

The FOMOD installs the complete package with no optional components. CMC is
built against Anomaly MCM `1.7.2fix`. Install it as a separate MO2 mod or copy
its `gamedata` tree into a flattened installation. It must override MCM's
`gamedata/scripts/ui_mcm.script`. The adaptive header and caption handling
support both stock MCM and Sota UI Rework.

## Playtest

- Assign several pages, press Apply, and reopen MCM to verify persistence.
- Verify normal Apply returns to CMC's category root without closing MCM;
  options that require a game or video restart retain MCM's close/restart flow.
- Change a category from a mod page and from one of its nested pages. Verify the
  change is shared, Apply saves it, and Reset/Cancel discard it.
- Stage category changes from at least seven different mod pages and across
  several target categories. Press Apply and verify all assignments save and
  the category root appears without a crash.
- Press Default on an individual mod page and verify it resets that mod's own
  settings without changing its CMC category.
- With no `[cmc]` section, open MCM and verify all 109 embedded assignments are
  saved on first launch without explicit Uncategorized entries.
- On Organize mods, press **Default** and verify all embedded assignments are
  staged while unknown pages become Uncategorized.
- Verify Reset/Cancel discard the staged defaults and Apply stores them.
- Press **Clear all categories** and verify every page becomes Uncategorized;
  verify Reset/Cancel discard the staged clear and Apply removes every current
  assignment.
- Assign one page explicitly to Other and verify it appears in the Other root
  category; clear another assignment and verify it appears in Uncategorized and
  All mods.
- Verify the first opening selects MCM > About and later openings restore the
  last real page.
- Verify MCM is pinned above Favorites and Organize mods is green below Logging.
- Enter several categories, then return with `< Categories`.
- Open nested two- and three-column MCM pages.
- Verify Favorites remains the most distinct root entry; All mods uses muted
  blue-gray, and Uncategorized uses muted cyan when visible.
- Verify Uncategorized is hidden when empty and returns at the bottom when a
  category assignment is cleared.
- Search from the category page and from inside a category.
- Clear Search and press Apply from an option page; verify the full category
  root returns instead of showing only the pinned MCM entry.
- Compare navigation responsiveness in Favorites, a populated category, and All
  mods; verify that tree-building debug lines appear only when MCM debug logging
  is explicitly enabled.
- Apply, reset, and restore defaults for several original mod settings.
- Verify MCM keybind lists, conflicts, and presets.
- Bind a key that `mcm_key_localization.ltx` does not name and verify the box
  reads `Key <code>` rather than `<!!!>`.
- Bind Caps Lock, then confirm the bound action fires and that the key's toggle
  state does not desynchronize typing elsewhere in the UI.
- Open a page with native presets and verify Category and Preset share the fixed
  header without overlap, while ordinary pages show a full-width Category row.
- Repeat the header and organizer checks with stock MCM and Sota UI Rework;
  verify organizer titles do not expose literal `%c[...]` controls.
- Verify CMC adds no separator above the original page content.
- Exercise any mod that calls `ui_mcm.open_to(path)` directly.
