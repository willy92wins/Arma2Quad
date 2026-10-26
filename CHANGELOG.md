# Changelog

## v1.0.1 - 2026-10-26

The port to DayZ 1.30. v1.0.0 was written for 1.29: on 1.30 its scripts do not load, and
with the script path fixed they do not compile. This version does not load on 1.29. Checked
against the DayZ 1.30.164200 scripts and in game on a 1.30.164200 DayZDiag server and client.
Models, textures, materials and `model.cfg` are unchanged.

**Fixed**

- None of the mod's scripts loaded, with no error. The `worldScriptModule` path in
  `config.cpp` was written with backslashes (`Arma2Quad\scripts\4_world`), and on
  1.30.164200 such a path loads nothing (measured with LFQuad, whose path had the same form),
  so the quad would run as a bare `CarScript`. The path now uses forward slashes.
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
  `ToggleHeadlights()` hook that set the flag are removed. Measured with this build: after the
  driver got off with the lights on, the lights stayed on for the server and the client, and
  the beam still lit the ground; a client that joins later was not tested. With one bulb left
  the parked quad now shows that bulb's own beam; the old parked beam was always the two-bulb
  one, from the middle of the quad.
- The wheels declare the four tyre fields that 1.30 added to every vanilla wheel
  (`tyreType`, `tyreRoughness`, `tyreLongitudinalFriction`, `tyreLateralFriction`), with the
  values of the vanilla `Offroad_02_Wheel`; the ruined wheels take the surface values of
  `Offroad_02_Wheel_Ruined`.
- The wheel script classes no longer override `GetRuinedReplacement()` and
  `GetReplacement()`. Since 1.30 the game derives the replacement itself, as the class name
  plus `_Ruined`, which gives the same names.
- `Arma2Quad_FrontLight` and `Arma2Quad_RearLight` (`CarLightBase` subclasses) are removed.

**Tested** in game on the 1.30.164200 DayZDiag of the stable install, server and client, with
Survivor Animations loaded:

- The scripts load and compile on both sides (`World` module at 2349 files, the count of
  LFQuad v1.0.1 with the same mods), with no script errors from the mod and no ruined-wheel
  errors.
- The engine starts, the headlights light the ground ahead, the short-horn action starts, and
  getting off keeps the engine running and the lights on. The driver sits in the Survivor
  Animations quad pose.
- The four wheel classes run their own script classes; each ruined wheel fits the two slots of
  its own axle, is refused by the other axle and shows its torn-tyre model.
- Lights on with both bulbs and then one bulb removed, twice: the remaining headlight drew the
  bright screen glow the two-bulb state did not, as the lens-flare fix intends.
- A copy with a manual gearbox, because the test tool cannot shift an automatic one, reached
  34 to 39 km/h in 2.8 s from a standstill, turned about 65 degrees in 2.3 s at full lock and
  40 to 47 km/h without rolling over, and stopped from about 38 km/h in about 1.6 s.

Not tested: the automatic gearbox itself, the co-driver seat, the horn sound, a wheel that
reaches zero health (no test tool can set it), a client joining later, and the full tank of a
Central Economy spawn.

**Known issues**

- No tyre-burst sound plays when a wheel is ruined: vanilla picks that sound by wheel class
  name (`CarWheel_Ruined.PlayWheelExlosionSound()`) and lists only its own wheels.
- `scripts/4_world/RiderHandsProbe.c`, unchanged since v1.0.0, is switched on for this quad:
  while someone drives it, their client script log gets about ten lines a second.

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
