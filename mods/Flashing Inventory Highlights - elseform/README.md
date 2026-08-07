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
- Color presets and optional custom RGB sliders.

In MCM, the mod appears as the purple `Flashing Item Highlights` entry.

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
