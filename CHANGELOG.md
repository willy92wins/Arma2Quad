# Changelog

## v1.0.1 - 2026-10-26

The port to DayZ 1.30. v1.0.0 was written for 1.29: on 1.30 its scripts do not load, and
with the script path fixed they do not compile. This version does not load on 1.29. Checked
against the DayZ 1.30.164200 scripts. Models, textures, materials and `model.cfg` are
unchanged.

**Fixed**

- None of the mod's scripts loaded, with no error. The `worldScriptModule` path in
  `config.cpp` was written with backslashes (`Arma2Quad\scripts\4_world`), and on
  1.30.164200 such a path loads nothing (measured with LFQuad, whose path had the same form),
  so the quad ran as a bare `CarScript`. The path now uses forward slashes.
- With its scripts loading, v1.0.0 would not compile: `Arma2Quad_base` overrode
  `CarScript.ToggleHeadlights()`, which 1.30 deleted outright. Removed.
- The engine could not start and the light switch never showed, with a battery attached.
  Since 1.30 the battery is found through `Transport.GetElectricitySourceDevice()`, which
  returns nothing unless the vehicle overrides it. The quad now declares its `CarBattery` the
  way the vanilla petrol cars do; the old `IsVitalTruckBattery()` override is gone, since 1.30
  no longer calls it.
- The headlight came out as the generic 1.30 beam (brightness 20/30 instead of 3/6), and the
  rear light as the generic profile: a dimmer brake light (2 instead of 4) and, in reverse, a
  beam as strong as a headlight from a quad that has no reverse lens. 1.30 no longer calls
  `CreateFrontLight()`/`CreateRearLight()`; the same values now live in
  `Arma2Quad_LightProfileFront` and `Arma2Quad_LightProfileRear`, registered on the
  vehicle's `VehicleLightsComponent`. A headlight left with one bulb keeps its lens flare, as
  in 1.29; the 1.30 front profile would switch it off for good once both bulbs had been lit.
- The horn was silent: 1.30 plays it from `VehicleHornComponent`, where the quad now
  registers the same two sound sets.

**Changed**

- Headlights left on when the driver steps off: 1.30 keeps the native lights on after the
  driver leaves, so the quad's own parked beam, the synchronised flag behind it and the
  `ToggleHeadlights()` hook that set the flag are removed. With one bulb left the parked quad
  now shows that bulb's own beam; the old parked beam was always the two-bulb one, from the
  middle of the quad.
- The wheels declare the four tyre fields that 1.30 added to every vanilla wheel
  (`tyreType`, `tyreRoughness`, `tyreLongitudinalFriction`, `tyreLateralFriction`), with the
  values of the vanilla `Offroad_02_Wheel`; the ruined wheels take the surface values of
  `Offroad_02_Wheel_Ruined`.
- The wheel script classes no longer override `GetRuinedReplacement()` and
  `GetReplacement()`. Since 1.30 the game derives the replacement itself, as the class name
  plus `_Ruined`, which gives the same names.
- `Arma2Quad_FrontLight` and `Arma2Quad_RearLight` (`CarLightBase` subclasses) are removed.

**Known issues**

- No tyre-burst sound plays when a wheel is ruined: vanilla picks that sound by wheel class
  name (`CarWheel_Ruined.PlayWheelExlosionSound()`) and lists only its own wheels.

## v1.0.0 - 2026-09-12

First public release. It is the build that had been running as the stable export, published
here unchanged.

**Vehicle**

- Two-seat ATV (driver and co-driver) for DayZ 1.29, ported from the Arma 2: Operation
  Arrowhead ATV.
- Five colour variants besides the default one: rust, sand, olive, blue and black.
- Front-wheel drive, 45 deg steering lock with a speed-dependent steering ramp, automatic
  4-speed gearbox, 750 kg, 25 L tank.

**Parts and damage**

- Four attachable and repairable wheels, front and rear, each with its own ruined model and
  proxy; car battery, spark plug and two headlight bulbs.
- Damage zones for chassis, front, back, engine, fuel tank and both reflectors.
- 10x30 cargo.

**Lights and sound**

- Front, brake, reverse, tail and dashboard lights.
- The headlights stay on when the driver steps off, so the quad can be used to light a spot.
- Six RPM layers of engine sound plus the offroad tyre, damper and wind sets.

**Central Economy**

- Spawns with a full tank instead of the vanilla random 0-35 %.

**Known and open**

- Traction and steering are still being tuned. In first gear at full throttle the driven
  axle can ask more force than the tyres hold, which shows up as wheelspin on the steering
  axle and a wider line than it should take.
- `scripts/4_world/RiderHandsProbe.c` is a diagnostic left in on purpose; it only logs when
  its probe type is configured.
