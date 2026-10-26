# Arma2Quad

A two-seat ATV for **DayZ 1.30**, ported from the *Arma 2: Operation Arrowhead* ATV using
Bohemia Interactive's own Licensed Data Package. Drivable, repairable, lit, and wired into
the Central Economy.

From v1.0.1 the mod is built for DayZ 1.30 and does not load on 1.29; v1.0.0 is the 1.29
build. See [CHANGELOG.md](CHANGELOG.md).

The model, textures and materials are Bohemia Interactive's. See [NOTICE.md](NOTICE.md) for
attribution and [LICENSE](LICENSE) for the terms: non-commercial, DayZ only.

## What it does

- Two crew seats: driver and co-driver.
- Front-wheel drive, 45 degree steering lock with a speed-dependent steering ramp, automatic
  4-speed gearbox, 750 kg, 25 L tank.
- Four attachable and repairable wheels, each with its own ruined model; car battery, spark
  plug and two headlight bulbs.
- Front, brake, reverse, tail and dashboard lights. The headlights stay on after the driver
  steps off, so the quad can be parked as a light source.
- Damage zones for chassis, front, back, engine, fuel tank and both reflectors.
- 10x30 cargo.
- Six RPM layers of engine sound, plus the vanilla offroad tyre, damper and wind sets.
- Spawns from the Central Economy with a full tank instead of the vanilla random 0-35 %.

## Class names

| Class | What it is |
|---|---|
| `Arma2Quad` | the vehicle |
| `Arma2Quad_Rust`, `Arma2Quad_Sand`, `Arma2Quad_Olive`, `Arma2Quad_Blue`, `Arma2Quad_Black` | colour variants |
| `Arma2Quad_Wheel_Front`, `Arma2Quad_Wheel_Rear` | wheels |
| `Arma2Quad_Wheel_Front_Ruined`, `Arma2Quad_Wheel_Rear_Ruined` | destroyed wheels, swapped in by the game |

## Install

1. Download `Arma2Quad.pbo`, `Arma2Quad.pbo.Return0.bisign` and `Return0.bikey` from the
   latest release.
2. Put the `.pbo` and the `.bisign` in `@Arma2Quad\Addons\`, next to the game on the client
   and next to the server executable on the server.
3. Put `Return0.bikey` in the server's `keys\` folder.
4. Add `-mod=@Arma2Quad` to both command lines. A vehicle mod has to be on both sides.

## Make it spawn (Central Economy)

Vehicles are placed by an event, not by loot, so three mission files are involved. The
shapes below follow the vanilla `OffroadHatchback` entries.

`db/types.xml`:

```xml
<type name="Arma2Quad">
    <nominal>0</nominal>
    <lifetime>3</lifetime>
    <restock>1800</restock>
    <min>0</min>
    <quantmin>-1</quantmin>
    <quantmax>-1</quantmax>
    <cost>100</cost>
    <flags count_in_cargo="0" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
</type>
```

`db/events.xml`:

```xml
<event name="VehicleArma2Quad">
    <nominal>8</nominal>
    <min>5</min>
    <max>11</max>
    <lifetime>300</lifetime>
    <restock>0</restock>
    <saferadius>500</saferadius>
    <distanceradius>500</distanceradius>
    <cleanupradius>200</cleanupradius>
    <flags deletable="0" init_random="0" remove_damaged="1"/>
    <position>fixed</position>
    <limit>mixed</limit>
    <active>1</active>
    <children>
        <child lootmax="0" lootmin="0" max="5" min="3" type="Arma2Quad"/>
        <child lootmax="0" lootmin="0" max="5" min="3" type="Arma2Quad_Olive"/>
    </children>
</event>
```

`position` is `fixed`, so the event also needs its spawn points in `cfgeventspawns.xml`
under the same event name.

`cfgspawnabletypes.xml`, so the quad spawns with parts on:

```xml
<type name="Arma2Quad">
    <attachments chance="1.00"><item name="Arma2Quad_Wheel_Front" chance="0.80" /></attachments>
    <attachments chance="1.00"><item name="Arma2Quad_Wheel_Front" chance="0.80" /></attachments>
    <attachments chance="1.00"><item name="Arma2Quad_Wheel_Rear" chance="0.80" /></attachments>
    <attachments chance="1.00"><item name="Arma2Quad_Wheel_Rear" chance="0.80" /></attachments>
    <attachments chance="1.00"><item name="CarBattery" chance="0.60" /></attachments>
    <attachments chance="1.00"><item name="SparkPlug" chance="0.60" /></attachments>
    <attachments chance="1.00"><item name="HeadlightH7" chance="0.50" /></attachments>
    <attachments chance="1.00"><item name="HeadlightH7" chance="0.50" /></attachments>
</type>
```

## Build from source

You need DayZ Tools and a `P:` drive that contains this addon folder:

```
subst P: "C:\path\to\your\projects"
"C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe" P:\Arma2Quad <output folder> -prefix=Arma2Quad "-temp=P:\temp\Arma2Quad" -packonly
```

`-packonly` ships the MLOD `.p3d` as they are. Note that AddonBuilder returns success even
when it produces nothing, so check that the `.pbo` exists and carries what you expect before
shipping it.

## Where the tuning stands

Honest status, because it matters if you fork this: the vehicle drives, but traction and
steering are still being worked on. In first gear at full throttle the driven axle can ask
more force than the tyres hold, which shows up as wheelspin on the steering axle and a wider
line than the quad should take. The knobs involved are `Clutch.maxTorqueTransfer`, the
gearbox ratios, `tyreGrip` on the wheel items, and the mass in the geometry LOD of
`Arma2Quad_body.p3d`.

`scripts/4_world/RiderHandsProbe.c` is a diagnostic kept on purpose. It only logs when its
probe type is configured.

## Credits

- **Bohemia Interactive a.s.** - the ATV model, textures and materials, from *Arma 2:
  Operation Arrowhead*, and the tools this was built with. Thank you.
- Port to DayZ, config, scripts and vehicle setup - [willy92wins](https://github.com/willy92wins).

This mod is not affiliated or authorized by Bohemia Interactive a.s. Bohemia Interactive,
ARMA, DAYZ and all associated logos and designs are trademarks or registered trademarks of
Bohemia Interactive a.s.
