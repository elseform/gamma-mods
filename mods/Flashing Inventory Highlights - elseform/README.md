# Flashing Inventory Highlights (FIH)

## What it does

FIH adds a configurable pulse to related-item highlights in the inventory and
trading grids, making compatible attachments and upgrade tools easier to spot.
Each focused set begins together on the rising half of its pulse.

Features customizable options:

- Optional post-unhover linger that completes the pulse to its next bright
  crest, then runs a configurable fade-out;
- Five pulse/fade timing presets and optional custom timing sliders;
- Minimum/maximum brightness;
- Color presets and optional custom RGB sliders.

In MCM, the mod appears as the purple `Flashing Item Highlights` entry.

## Install & Load order

Drop the archive onto the MO2 window and use the one-step installer. FIH has no
component choices; the installer page is a preview of the complete package.

## Compatibility

FIH chains the active inventory highlight implementation instead of replacing
game files. When a linger ends, it returns control through that chain instead
of hiding the highlight layer directly.
