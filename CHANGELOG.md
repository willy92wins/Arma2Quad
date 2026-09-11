# Changelog

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
