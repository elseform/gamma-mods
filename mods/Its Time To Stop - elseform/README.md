# It's Time To Stop (ITTS)

Helps keep an eye on how much real time you spend in the Zone and gives you a
notification when it's time to touch grass.

## What you get

- **Playtime in the PDA**: two new rows in the ranking tab's bottom strip,
  next to the achievement and visited-location counters. "Time Played" is
  your real (wall-clock) total for the savegame; "Session" is the current
  sitting - it survives quickloads, level transitions, and game
  restarts, and starts over only after you've been away for a while
  (20 minutes by default).
- **Real-life clock on the HUD**, By default it sits
  around the minimap or in a
  screen corner, and can swap places with - or replace - the in-game
  clock. Fonts, color presets, custom RGB, blinking ":" separators,
  and fine-tune offsets included.
- **Session notifications**: a PDA message when your session crosses the
  "good" threshold (tells you how much time is left; 2 hours by default)
  and the "bad" one (tells you to stop; 3 hours by default). Optional
  repeat reminders and a PDA beep.
- **Progressive clock color**: the HUD clock can change color as your
  session crosses those thresholds - green, orange, red by default, each
  stage configurable.

What counts as playtime:

- Counts: normal gameplay, including PDA, inventory, trading, and dialogs
  (the world keeps running during those).
- Doesn't count: main menu, pause/Esc menu, MCM, console, alt-tab, loading
  screens, and level transitions. One exception out of the box: the Session
  timer does include loading time, so a sitting isn't full of holes - the
  per-save total never does. Both that and pause-counting are MCM toggles.
- Sleeping counts only the real seconds the animation takes, not the
  skipped game hours.

## Settings

Everything is in MCM under "Its Time To Stop", on three pages: Real-time
HUD Clock, Session Notifications, and Playtime Stats.

Most options take effect immediately. Two exceptions:

- Clock positions that move or replace the stock in-game clock need a game
  restart.
- Showing/hiding the PDA rows applies after reloading a save (with the PDA
  closed).

## Install

Install like any other MO2 mod: drop the archive onto the MO2 window. No
load-order requirements, no dependencies beyond stock GAMMA.

## Compatibility

- No game files are overridden; everything is patched at runtime, so it
  gets along with other PDA and HUD mods, including reworked ranking
  layouts.
- To make room in the PDA strip, "Unlocked Articles"
  counter is hidden while ITTS rows are shown. Turn both rows off and it
  comes right back.
- Safe to add to an existing savegame - counting simply starts from zero.
  Safe to remove too: it leaves behind only an inert number in the save and
  a tiny `sessiontime` file in appdata that you can delete.
