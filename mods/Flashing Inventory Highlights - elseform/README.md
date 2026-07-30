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

Install as any other MO2 mod, drop the archive onto MO2 window.

## Compatibility

FIH chains the active inventory highlight implementation instead of replacing
game files. When a linger ends, it returns control through that chain instead
of hiding the highlight layer directly.
