# Level-Changer HUD (L-CHUD)

## What it does

When you get close to a level transition and face it, the Level-Changer HUD shows a card.
It tells you where it leads, which tasks are active or ready to turn in, stashes, and whether an RF package is there.

## MCM options

- **Enable L-CHUD** and **Detection Distance**.
- **Destination Font**, **Counter Font**, and **Animation Preset**: Instant,
  Fast, Balanced, and Gentle (default) rise into place at different speeds;
  Fade keeps the label still.
- **Counters**: turn each counter on or off, pulse the RF package icon, and
  show or hide zero counts.
- **Advanced settings**:
  - Vertical and horizontal offsets for the whole overlay;
  - **Detection Method**:
    - **Auto** (default) checks line of sight on Agroprom, Dark Valley,
      Yantar, Radar, both Chernobyl NPP levels, Generators, Jupiter, and
      Zaton, and uses range and view angle alone everywhere else, so
      transitions inside tunnels and around corners still show;
    - **Simple** uses range and view angle everywhere;
    - **Line of Sight** checks line of sight everywhere;
  - **Detection Angle**, plus the line-of-sight **Grace Period** and
    **Target Radius**.
- **Icons**: pick the task, stash, and RF package icons from a preview list.

## Install & Load order

Drop the archive onto the MO2 window and use the one-step installer. L-CHUD
has no component choices. When updating, choose **Replace** in MO2.

There are no load-order requirements.

## Compatibility

L-CHUD adds its own scripts and UI files and replaces no game files.

It bundles the icon atlas from Interaction Dot Marks at that mod's own paths
(see Credits). The files are identical to Interaction Dot Marks 1.7.5, so the
two mods can be installed together in either order.

## Dependencies

- MCM, to change settings.
- Optional: RF Receiver Tasks and Extra Level Transitions, both part of stock
  GAMMA. Without them, their parts of L-CHUD simply don't appear.

## Files

- `gamedata/scripts/elseform_lchud.script`
- `gamedata/scripts/elseform_lchud_mcm.script`
- `gamedata/configs/ui/elseform_lchud.xml`, `elseform_lchud_16.xml`,
  `elseform_lchud_21.xml`
- `gamedata/configs/text/eng/ui_st_elseform_lchud.xml`
- `gamedata/configs/text/rus/ui_st_elseform_lchud.xml`
- `gamedata/textures/catsy/ui_dotmarks.dds` and
  `gamedata/configs/ui/textures_descr/dotmarks_texd.xml` (bundled, see
  Credits)

## Credits

The icon atlas and its texture definitions are by **Catsy (Catspaw)**, from
[Interaction Dot Marks 1.7.5](https://www.moddb.com/mods/stalker-anomaly/addons/interaction-dot-marks),
included unchanged at their original paths. Interaction Dot Marks does not
need to be installed separately for these icons.

## Changelog

- **1.0.0** — Initial release.
