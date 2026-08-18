# Flashing Inventory Highlights (FIH)

## What it does

FIH adds a configurable pulse to related-item highlights in the inventory and
trading grids, making compatible attachments and upgrade tools easier to spot.
Each focused set begins together on the rising half of its pulse.

Features customizable options:

- Optional fixed-duration post-unhover linger that rises quickly to full
  brightness, holds briefly, then fades on a predictable timer;
- Five pulse/exit timing presets and optional custom timing sliders;
- Minimum/maximum brightness;
- Optional current-faction highlight color from UI Rework G.A.M.M.A. Style;
- Color presets and optional custom RGB sliders.

In MCM, the mod appears as the purple `Flashing Item Highlights` entry.

## Changes in 1.2.0

- Add an optional UI Rework G.A.M.M.A. Style faction-color source while keeping
  FIH's pulse brightness and timing.
- Let each outgoing highlight set complete its linger when the cursor crosses
  another item; rapid movement may leave several brief overlapping fades.
- Keep faction coloring disabled by default and fall back to the selected FIH
  color when UI Rework is unavailable.

## Upgrading from 1.1.0

The linger is now a fixed-duration exit rather than a fade that waited for the
next pulse crest, so the slider means something different than it did. Upgrading
resets that one setting to its default; every other MCM option is preserved.

## Install & Load order

Drop the archive onto the MO2 window and use the one-step installer. FIH has no
component choices; the installer page is a preview of the complete package.

## Compatibility

FIH chains the active inventory highlight implementation instead of replacing
game files. When a linger ends, it returns control through that chain instead
of hiding the highlight layer directly.

The optional faction-color setting reads UI Rework G.A.M.M.A. Style's current
actor-faction RGB. FIH keeps ownership of pulse brightness and timing. If UI
Rework is absent, FIH falls back to its selected preset or custom color.
