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
hide-when-empty **Unassigned** inbox until the user sorts them.


A new **Manage categories** page allows you to create custom categories, rename existing ones, and manage which categories are pinned to the top. When the "Force English locale for MCM menus" option is enabled, pinned and unpinned categories are sorted alphabetically. **Delete all categories** wipes every custom and built-in category (reassigning their mods to Unassigned); **Restore default categories** clears the same `[cmc_categories]` state back to CMC's shipped defaults.

## Default Categories

CMC embeds assignments for all 119 MCM pages curated in its development
profile. On first launch, CMC writes those explicit assignments immediately;
it does not write empty `Unassigned` values. On the **Organize mods** page,
MCM's standard **Default** button stages the same mapping. Press **Apply** to
save staged defaults, or **Reset**/**Cancel** to discard them. Assignments for
pages that are not installed remain dormant and return automatically if the
mod is reinstalled. Newly discovered pages without an embedded assignment
appear in **Unassigned**.

**Clear all categories** stages every discovered page as Unassigned. Press
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
**Favorites**, muted blue-gray **All mods**, **Pinned** categories, all other
categories, and muted cyan **Unassigned** at the bottom when it contains pages.
**Organize mods** and **Manage categories** are the final entries
inside MCM's own menu and are colored green.

Alphabetical sorting of categories requires the **Force English locale for MCM menus** option to be enabled, which also requires DXML/modded-exes to function correctly. If DXML is unavailable, this feature gracefully falls back to deterministic definition order.

Opening the organizer creates one native combo box per discovered MCM page;
removing that initial construction pause on very large lists would require a
paged or virtualized organizer redesign.

## Storage

CMC stores all mutable state in
`gamedata/configs/plugins/elseform_cmc.ltx`. The file is created at runtime so
installing or updating the mod does not replace player state with a packaged
copy. Explicit assignments use the original top-level MCM ID:

```ini
[cmc]
lower_weapon_sprint = 6

[cmc_categories]
1_pinned = true

[cmc_custom_categories]
1000 = 1,My category
1001 = 0,QoL, tools

[cmc_settings]
force_english_mcm = false
```

The stored value is the selected category number. Other is stored explicitly as
`0`; a missing entry means Unassigned and appears in its smart inbox and All
mods. The organizer and per-page selector do not move or rename the original MCM
option tree. Each custom-category row stores `<pinned 0/1>,<name>`. Everything
after the first comma belongs to the name, so names may contain commas. CMC
calculates the next custom ID from existing numeric rows; no counter is stored.

On first use, CMC copies legacy `[cmc]` assignments and
`mcm/mcm_about/dxml` from `axr_options.ltx` into the dedicated file. Only
shipped category values (`-1` and `0` through `14`) are accepted. CMC saves the
destination before removing all legacy `[cmc]`, `[cmc_categories]`, locale, and
manager-draft values. The old section headers may remain empty because the
engine INI API cannot remove sections. Edit either file only while the game is
closed.

Development-only multi-key custom-category rows are not migrated. CMC removes
them and resets assignments pointing only to those removed categories to
Unassigned. Built-in overrides retain their existing `<value>_name`,
`<value>_pinned`, and `<value>_deleted` representation.

## Installation and Load Order

The FOMOD installs the complete package with no optional components. CMC is
built against Anomaly MCM `1.7.2fix`. Install it as a separate MO2 mod or copy
its `gamedata` tree into a flattened installation. It must override MCM's
`gamedata/scripts/ui_mcm.script`. The adaptive header and caption handling
support both stock MCM and Sota UI Rework.

## Playtest

- Start with legacy assignments and locale setting in `axr_options.ltx`, open
  MCM, and verify valid values migrate before legacy values are removed.
- Include an invalid legacy category value and verify it is discarded rather
  than copied.
- Verify `gamedata/configs/plugins/elseform_cmc.ltx` is created with
  `force_english_mcm = false` and contains all later category changes.
- Create, rename, pin, and delete custom categories; verify each custom category
  remains one `[cmc_custom_categories]` row and deleted rows disappear.
- Create a category whose name contains commas and verify it round-trips intact.
- Toggle **Force English locale for MCM menus**, Apply, restart, and verify the
  value and locale behavior survive without recreating `mcm/mcm_about/dxml`.
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
- With no `[cmc]` section, open MCM and verify all 119 embedded assignments are
  saved on first launch without explicit Unassigned entries.
- On Organize mods, press **Default** and verify all embedded assignments are
  staged while unknown pages become Unassigned.
- Verify Reset/Cancel discard the staged defaults and Apply stores them.
- Press **Clear all categories** and verify every page becomes Unassigned;
  verify Reset/Cancel discard the staged clear and Apply removes every current
  assignment.
- Assign one page explicitly to Other and verify it appears in the Other root
  category; clear another assignment and verify it appears in Unassigned and
  All mods.
- Verify the first opening selects MCM > About and later openings restore the
  last real page.
- Verify MCM is pinned above Favorites and Organize mods is green below Logging.
- Enter several categories, then return with `< Categories`.
- Open nested two- and three-column MCM pages.
- Verify Favorites remains the most distinct root entry; All mods uses muted
  blue-gray, and Unassigned uses muted cyan when visible.
- Verify Unassigned is hidden when empty and returns at the bottom when a
  category assignment is cleared.
- Search from the category page and from inside a category.
- Clear Search and press Apply from an option page; verify the full category
  root returns instead of showing only the pinned MCM entry.
- Compare navigation responsiveness in Favorites, a populated category, and All
  mods; verify no `[CMC]` tree-building debug lines are emitted.
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
- Create a custom category, delete a built-in one, then press **Restore
  default categories**, Apply, and verify built-ins return to their shipped
  state while any mod on the removed custom category becomes Unassigned.
- Open All mods, enter Favorites (or any category), open a mod's own page,
  and verify MCM reports no pending changes until you actually edit
  something.
