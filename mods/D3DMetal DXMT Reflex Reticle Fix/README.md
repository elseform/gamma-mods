# D3DMetal/DXMT Reflex Reticle Fix

Fixes missing red-dot and holographic sight reticles when running STALKER Anomaly/GAMMA through D3DMetal or DXMT.

## Problem

Some Parallax Reflex Sights shaders calculate reticle UVs through a tangent-space parallax path. The original pixel shaders read tangent, binormal, and normal vectors from different TEXCOORD slots than the vertex shader writes. Under DXVK this can still appear to render normally, but under D3DMetal/DXMT the bad tangent frame can push the reticle sample out of the visible texture area, making the dot disappear.

This can affect regular reflex sights and side/canted reflex sights. Magnified 3D scopes were not the target of this fix.

## Solution

The patched shaders keep the original tangent-space parallax projection, but fix the pixel shader input semantics so tangent, binormal, and normal match the existing vertex shader outputs:

- vertex shader: `P/T/B/N` = `TEXCOORD1/2/3/4`
- patched pixel shaders: `P/T/B/N` = `TEXCOORD1/2/3/4`

This is intended to restore the visible dot while preserving the Parallax Reflex Sights effect.

Patched files:

- `gamedata/shaders/r3/models_reflex_reticle_3db.ps`
- `gamedata/shaders/r3/models_reflex_reticle_simple.ps`
- `gamedata/shaders/r3/models_reflex_reticle.ps`
- `gamedata/shaders/r3/models_reflex_reticle_simple_3db.ps`
- `gamedata/shaders/r3/models_lfo_light_dot_weapons.ps`

## Installation

Install as a normal MO2 mod, or copy the `gamedata` folder into the game directory so it overrides the original shader files.

Recommended modlist placement: late in the visual/shader section, after Parallax Reflex Sights and any mod that replaces reflex sight shaders.

## Shader Cache

After installing or updating this fix, clear the affected shader cache so the game recompiles the patched shaders:

- `appdata/shaders_cache/r4/models_reflex_reticle_3db.ps`
- `appdata/shaders_cache/r4/models_reflex_reticle_simple.ps`
- `appdata/shaders_cache/r4/models_reflex_reticle.ps`
- `appdata/shaders_cache/r4/models_reflex_reticle_simple_3db.ps`
- `appdata/shaders_cache/r4/models_lfo_light_dot_weapons.ps`

Deleting the whole `appdata/shaders_cache` folder is also fine; the game will rebuild it.

## Notes

This is a compatibility workaround for D3DMetal/DXMT. It should be harmless under DXVK, but it mainly targets translators that are less forgiving of the original shader semantic mismatch.
