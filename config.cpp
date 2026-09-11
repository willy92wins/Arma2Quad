class CfgPatches
{
	class Arma2Quad
	{
		units[] =
		{
			"Arma2Quad",
			"Arma2Quad_Rust",
			"Arma2Quad_Sand",
			"Arma2Quad_Olive",
			"Arma2Quad_Blue",
			"Arma2Quad_Black",
			"Arma2Quad_Wheel_Front",
			"Arma2Quad_Wheel_Rear",
			"Arma2Quad_Wheel_Front_Ruined",
			"Arma2Quad_Wheel_Rear_Ruined"
		};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Vehicles_Wheeled",
			"DZ_Vehicles_Parts",
			"DZ_Gear_Containers",
			"DZ_Sounds_Effects"
		};
	};
};

class CfgMods
{
	class Arma2Quad
	{
		dir = "Arma2Quad";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Arma2Quad";
		credits = "";
		author = "LostForest";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = {"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"Arma2Quad\scripts\4_world"};
			};
		};
	};
};

class CfgSoundShaders
{
	class baseEngineOffroad_SoundShader
	{
		range = 80;
	};
	class Arma2Quad_Engine_Ext_Rpm0_SoundShader: baseEngineOffroad_SoundShader
	{
		samples[] = {{"\Arma2Quad\data\sound\arma2quad_engine", 1}};
		frequency = "0.55 * ((850 + ((rpm - 850)/(8000/5600))) max 850) / 850";
		volume = "0.75 * 1 * engineOn * 0.4 * ((850 + ((rpm - 850)/(8000/5600))) factor [(((850+1200)/2) + 2.5*50),(((850+1200)/2) - 50)]) * ((1 - 0.25*doors) max campos)";
	};
	class Arma2Quad_Engine_Ext_Rpm1_SoundShader: baseEngineOffroad_SoundShader
	{
		samples[] = {{"\Arma2Quad\data\sound\arma2quad_engine", 1}};
		frequency = "0.55 * (850 + ((rpm - 850)/(8000/5600))) / 1200";
		volume = "0.75 * 1 * (thrust factor[0.1,0.45]) * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 0.6 * ((850 + ((rpm - 850)/(8000/5600))) factor [(((850+1200)/2) - 2.5*50),(((850+1200)/2) + 50)]) * ((850 + ((rpm - 850)/(8000/5600))) factor [(((1200+1700)/2) + 2.5*150),(((1200+1700)/2) - 150)]) * ((1 - 0.25*doors) max campos)";
	};
	class Arma2Quad_Engine_Ext_Rpm2_SoundShader: baseEngineOffroad_SoundShader
	{
		samples[] = {{"\Arma2Quad\data\sound\arma2quad_engine", 1}};
		frequency = "0.55 * (850 + ((rpm - 850)/(8000/5600))) / 1700";
		volume = "0.75 * 1 * (thrust factor[0.1,0.45]) * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 0.85 * ((850 + ((rpm - 850)/(8000/5600))) factor [(((1200+1700)/2) - 2.5*150),(((1200+1700)/2) + 150)]) * ((850 + ((rpm - 850)/(8000/5600))) factor [(((1700+2300)/2) + 2.5*150),(((1700+2300)/2) - 150)]) * ((1 - 0.25*doors) max campos)";
	};
	class Arma2Quad_Engine_Ext_Rpm3_SoundShader: baseEngineOffroad_SoundShader
	{
		samples[] = {{"\Arma2Quad\data\sound\arma2quad_engine", 1}};
		frequency = "0.55 * (850 + ((rpm - 850)/(8000/5600))) / 2300";
		volume = "0.75 * 1 * (thrust factor[0.1,0.45]) * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((850 + ((rpm - 850)/(8000/5600))) factor [(((1700+2300)/2) - 2.5*150),(((1700+2300)/2) + 150)]) * ((850 + ((rpm - 850)/(8000/5600))) factor [(((2300+3250)/2) + 2.5*200),(((2300+3250)/2) - 200)]) * ((1 - 0.25*doors) max campos)";
	};
	class Arma2Quad_Engine_Ext_Rpm4_SoundShader: baseEngineOffroad_SoundShader
	{
		samples[] = {{"\Arma2Quad\data\sound\arma2quad_engine", 1}};
		frequency = "0.55 * (850 + ((rpm - 850)/(8000/5600))) / 3250";
		volume = "0.75 * 1 * (thrust factor[0.1,0.45]) * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((850 + ((rpm - 850)/(8000/5600))) factor [(((2300+3250)/2) - 2.5*200),(((2300+3250)/2) + 200)]) * ((850 + ((rpm - 850)/(8000/5600))) factor [(((3250+4400)/2) + 2.5*200),(((3250+4400)/2) - 200)]) * ((1 - 0.25*doors) max campos)";
	};
	class Arma2Quad_Engine_Ext_Rpm5_SoundShader: baseEngineOffroad_SoundShader
	{
		samples[] = {{"\Arma2Quad\data\sound\arma2quad_engine", 1}};
		frequency = "(0.55 * (850 + ((rpm - 850)/(8000/5600))) / 4400) min (8000/5600)";
		volume = "0.75 * 1 * (thrust factor[0.1,0.45]) * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((850 + ((rpm - 850)/(8000/5600))) factor [(((3250+4400)/2) - 2.5*200),(((3250+4400)/2) + 200)]) * ((1 - 0.25*doors) max campos)";
	};
	class Arma2Quad_Engine_Ext_Broken_SoundShader: baseEngineOffroad_SoundShader
	{
		samples[] = {{"\Arma2Quad\data\sound\arma2quad_engine", 1}};
		frequency = 0.9;
		volume = "0.75 * 1 * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((850 + ((rpm - 850)/(8000/5600))) factor [(((3250+4400)/2) - 2.5*200),(((3250+4400)/2) + 200)]) * ((1 - 0.25*doors) max campos) * (rpm factor[5300,6200])";
	};
};

class CfgSoundSets
{
	class baseEngine_EXT_SoundSet;
	class Arma2Quad_Engine_Ext_Rpm0_SoundSet: baseEngine_EXT_SoundSet { soundShaders[] = {"Arma2Quad_Engine_Ext_Rpm0_SoundShader"}; volumeFactor = 1.5; };
	class Arma2Quad_Engine_Ext_Rpm1_SoundSet: baseEngine_EXT_SoundSet { soundShaders[] = {"Arma2Quad_Engine_Ext_Rpm1_SoundShader"}; volumeFactor = 1.5; };
	class Arma2Quad_Engine_Ext_Rpm2_SoundSet: baseEngine_EXT_SoundSet { soundShaders[] = {"Arma2Quad_Engine_Ext_Rpm2_SoundShader"}; volumeFactor = 1.5; };
	class Arma2Quad_Engine_Ext_Rpm3_SoundSet: baseEngine_EXT_SoundSet { soundShaders[] = {"Arma2Quad_Engine_Ext_Rpm3_SoundShader"}; volumeFactor = 1.5; };
	class Arma2Quad_Engine_Ext_Rpm4_SoundSet: baseEngine_EXT_SoundSet { soundShaders[] = {"Arma2Quad_Engine_Ext_Rpm4_SoundShader"}; volumeFactor = 1.5; };
	class Arma2Quad_Engine_Ext_Rpm5_SoundSet: baseEngine_EXT_SoundSet { soundShaders[] = {"Arma2Quad_Engine_Ext_Rpm5_SoundShader"}; volumeFactor = 1.725; };
	class Arma2Quad_Engine_Ext_Broken_SoundSet: baseEngine_EXT_SoundSet { soundShaders[] = {"Arma2Quad_Engine_Ext_Broken_SoundShader"}; volumeFactor = 1.62; };
};

class CfgSlots
{
	class Slot_Arma2Quad_wheel_1_1
	{
		name = "Arma2Quad_wheel_1_1";
		displayName = "Front Left Wheel";
		selection = "wheel_1_1";
		ghostIcon = "wheel";
	};
	class Slot_Arma2Quad_wheel_2_1
	{
		name = "Arma2Quad_wheel_2_1";
		displayName = "Front Right Wheel";
		selection = "wheel_2_1";
		ghostIcon = "wheel";
	};
	class Slot_Arma2Quad_wheel_1_2
	{
		name = "Arma2Quad_wheel_1_2";
		displayName = "Rear Left Wheel";
		selection = "wheel_1_2";
		ghostIcon = "wheel";
	};
	class Slot_Arma2Quad_wheel_2_2
	{
		name = "Arma2Quad_wheel_2_2";
		displayName = "Rear Right Wheel";
		selection = "wheel_2_2";
		ghostIcon = "wheel";
	};
};

class CfgVehicles
{
	class CarWheel;
	class CarScript;

	class Arma2Quad_Wheel_Front: CarWheel
	{
		scope = 2;
		displayName = "Arma2Quad Front Wheel";
		descriptionShort = "A front wheel for Arma2Quad.";
		model = "\Arma2Quad\Arma2Quad_wheel_front.p3d";
		weight = 20000;
		inventorySlot[] = {"Arma2Quad_wheel_1_1", "Arma2Quad_wheel_2_1"};
		rotationFlags = 4;
		repairableWithKits[] = {6};
		repairCosts[] = {30};
		radiusByDamage[] = {0, 0.350149, 0.3, 0.288358, 0.9998, 0.259522, 0.9999, 0.230686};
		radius = 0.350149;
		width = 0.30;
		tyreOffroadResistance = 0.99;
		tyreGrip = 0.99;
		tyreRollResistance = 0.015;
		physLayer = "item_large";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] =
					{
						{1.0, {}},
						{0.7, {}},
						{0.5, {}},
						{0.3, {}},
						{0.0, {}}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class drop
				{
					soundset = "hatchbackwheel_drop_SoundSet";
					id = 898;
				};
			};
		};
	};

	class Arma2Quad_Wheel_Rear: CarWheel
	{
		scope = 2;
		displayName = "Arma2Quad Rear Wheel";
		descriptionShort = "A rear wheel for Arma2Quad.";
		model = "\Arma2Quad\Arma2Quad_wheel_rear.p3d";
		weight = 20000;
		inventorySlot[] = {"Arma2Quad_wheel_1_2", "Arma2Quad_wheel_2_2"};
		rotationFlags = 4;
		repairableWithKits[] = {6};
		repairCosts[] = {30};
		radiusByDamage[] = {0, 0.350176, 0.3, 0.288380, 0.9998, 0.259542, 0.9999, 0.230704};
		radius = 0.350176;
		width = 0.40;
		tyreOffroadResistance = 0.99;
		tyreGrip = 0.99;
		tyreRollResistance = 0.015;
		physLayer = "item_large";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] =
					{
						{1.0, {}},
						{0.7, {}},
						{0.5, {}},
						{0.3, {}},
						{0.0, {}}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class drop
				{
					soundset = "hatchbackwheel_drop_SoundSet";
					id = 898;
				};
			};
		};
	};

	// Ruined variants, swapped in by CarWheel.EEHealthLevelChanged through the names
	// resolved in Arma2Quad_Wheels.c. Only the model and the contact patch change; slots,
	// weight, health and sounds are inherited so the wheel keeps its identity and stays
	// in the same slot.
	//
	// radius comes from the outer envelope of the torn tyre measured every 10 degrees
	// around the axle: median 0.3275, mean 0.3125, peak 0.3588 on the shreds. The tyre is
	// not flattened all round, so the single axis-to-lowest-point figure (0.27635) belongs
	// to one sector only and would bury the intact rubber up to 83 mm at other angles; the
	// 0.221 and 0.242 minima are the rips, where no rubber reaches the ground anyway.
	// radiusByDamage is flattened to the same value: the inherited healthy curve resolves
	// to 0.2307 at full damage, which is the same failure 100 mm deeper.
	class Arma2Quad_Wheel_Front_Ruined: Arma2Quad_Wheel_Front
	{
		model = "\Arma2Quad\Arma2Quad_wheel_front_ruined.p3d";
		radiusByDamage[] = {0, 0.33, 1, 0.33};
		radius = 0.33;
		width = 0.341;
		tyreOffroadResistance = 0.10;
		tyreGrip = 0.33;
		tyreRollResistance = 0.3;
	};

	class Arma2Quad_Wheel_Rear_Ruined: Arma2Quad_Wheel_Rear
	{
		model = "\Arma2Quad\Arma2Quad_wheel_rear_ruined.p3d";
		radiusByDamage[] = {0, 0.33, 1, 0.33};
		radius = 0.33;
		width = 0.364;
		tyreOffroadResistance = 0.10;
		tyreGrip = 0.33;
		tyreRollResistance = 0.3;
	};

	class Arma2Quad_base: CarScript
	{
		scope = 0;
		displayName = "Arma2Quad";
		descriptionShort = "Two-seat all-terrain quad.";
		model = "\Arma2Quad\Arma2Quad_body.p3d";
		attachments[] =
		{
			"CarBattery",
			"Reflector_1_1",
			"Reflector_2_1",
			"SparkPlug",
			"Arma2Quad_wheel_1_1",
			"Arma2Quad_wheel_2_1",
			"Arma2Quad_wheel_1_2",
			"Arma2Quad_wheel_2_2"
		};
		hiddenSelections[] =
		{
			"light_1_1",
			"light_2_1",
			"light_brake_1_2",
			"light_brake_2_2",
			"light_reverse_1_2",
			"light_reverse_2_2",
			"light_1_2",
			"light_2_2",
			"light_dashboard",
			"camo1",
			"camo2"
		};
		hiddenSelectionsTextures[] =
		{
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"Arma2Quad\data\Arma2Quad_co.paa",
			"Arma2Quad\data\Arma2Quad_detail_co.paa"
		};
		hiddenSelectionsMaterials[] =
		{
			"Arma2Quad\data\mat\Arma2Quad_lights.rvmat",
			"Arma2Quad\data\mat\Arma2Quad_lights.rvmat",
			"Arma2Quad\data\mat\Arma2Quad_lights_off.rvmat",
			"Arma2Quad\data\mat\Arma2Quad_lights_off.rvmat",
			"Arma2Quad\data\mat\Arma2Quad_lights_off.rvmat",
			"Arma2Quad\data\mat\Arma2Quad_lights_off.rvmat",
			"Arma2Quad\data\mat\Arma2Quad_lights_off.rvmat",
			"Arma2Quad\data\mat\Arma2Quad_lights_off.rvmat",
			"Arma2Quad\data\mat\Arma2Quad_lights.rvmat",
			"Arma2Quad\data\mat\Arma2Quad_body.rvmat",
			"Arma2Quad\data\mat\Arma2Quad_detail.rvmat"
		};
		frontReflectorMatOn = "Arma2Quad\data\mat\Arma2Quad_lights_emissive.rvmat";
		frontReflectorMatOff = "Arma2Quad\data\mat\Arma2Quad_lights.rvmat";
		brakeReflectorMatOn = "Arma2Quad\data\mat\Arma2Quad_lights_brake.rvmat";
		brakeReflectorMatOff = "Arma2Quad\data\mat\Arma2Quad_lights_off.rvmat";
		ReverseReflectorMatOn = "Arma2Quad\data\mat\Arma2Quad_lights_off.rvmat";
		ReverseReflectorMatOff = "Arma2Quad\data\mat\Arma2Quad_lights_off.rvmat";
		TailReflectorMatOn = "Arma2Quad\data\mat\Arma2Quad_lights_red.rvmat";
		TailReflectorMatOff = "Arma2Quad\data\mat\Arma2Quad_lights_off.rvmat";
		dashboardMatOn = "Arma2Quad\data\mat\Arma2Quad_lights_emissive.rvmat";
		dashboardMatOff = "Arma2Quad\data\mat\Arma2Quad_lights.rvmat";
		fuelCapacity = 25;
		fuelConsumption = 3.5;

		class Sounds
		{
			thrust = 0.6;
			thrustTurbo = 1;
			thrustGentle = 0.3;
			thrustSmoothCoef = 0.02;
			camposSmoothCoef = 0.03;
			soundSetsFilter[] =
			{
				"Arma2Quad_Engine_Ext_Rpm0_SoundSet",
				"Arma2Quad_Engine_Ext_Rpm1_SoundSet",
				"Arma2Quad_Engine_Ext_Rpm2_SoundSet",
				"Arma2Quad_Engine_Ext_Rpm3_SoundSet",
				"Arma2Quad_Engine_Ext_Rpm4_SoundSet",
				"Arma2Quad_Engine_Ext_Rpm5_SoundSet",
				"Arma2Quad_Engine_Ext_Broken_SoundSet",
				"offroad_Tires_rock_slow_Ext_SoundSet",
				"offroad_Tires_rock_fast_Ext_SoundSet",
				"offroad_Tires_grass_slow_Ext_SoundSet",
				"offroad_Tires_grass_fast_Ext_SoundSet",
				"offroad_Tires_gravel_slow_Ext_SoundSet",
				"offroad_Tires_gravel_fast_Ext_SoundSet",
				"offroad_Tires_gravel_dust_fast_Ext_SoundSet",
				"offroad_Tires_asphalt_slow_Ext_SoundSet",
				"offroad_Tires_asphalt_fast_Ext_SoundSet",
				"offroad_Tires_water_slow_Ext_SoundSet",
				"offroad_Tires_water_fast_Ext_SoundSet",
				"Offroad_skid_dirt_SoundSet",
				"offroad_dirt_turn_SoundSet",
				"offroad_Rain_Ext_SoundSet",
				"offroad_damper_left_SoundSet",
				"offroad_damper_right_SoundSet"
			};
			soundSetsInt[] =
			{
				"Offroad_Tires_Asphalt_Fast_General_Int_SoundSet",
				"Offroad_Wind_SoundSet"
			};
		};

		class Crew
		{
			class Driver
			{
				actionSel = "seat_driver";
				proxyPos = "crewdriver";
				getInPos = "pos_driver";
				getInDir = "pos_driver_dir";
				isDriver = 1;
			};
			class CoDriver
			{
				actionSel = "seat_codriver";
				proxyPos = "crewcodriver";
				getInPos = "pos_codriver";
				getInDir = "pos_codriver_dir";
			};
		};

		class SimulationModule
		{
			class Steering
			{
				maxSteeringAngle = 45;
				increaseSpeed[] = {0, 100, 30, 60, 60, 60, 100, 40};
				decreaseSpeed[] = {0, 160, 60, 120, 90, 80};
				centeringSpeed[] = {0, 0, 15, 25, 60, 40, 100, 60};
			};
			class Throttle
			{
				reactionTime = 0.7;
				defaultThrust = 0.57;
				gentleThrust = 0.2;
				turboCoef = 5.5;
				gentleCoef = 0.55;
			};
			class Brake
			{
				pressureBySpeed[] = {0, 0.75, 10, 0.65, 20, 0.5, 40, 0.4, 60, 0.43, 80, 0.45, 100, 0.5, 120, 0.65};
				gentleCoef = 0.65;
				minPressure = 0.2;
				reactionTime = 0.3;
				driverless = 0.1;
			};
			class Aerodynamics
			{
				frontalArea = 0.5;
				dragCoefficient = 0.85;
			};
			drive = "DRIVE_FWD";
			class Engine
			{
				torqueCurve[] = {525, 0, 800, 42, 1000, 210, 1300, 290, 2700, 320, 4200, 240, 6400, 0};
				inertia = 0.17;
				frictionTorque = 42;
				rollingFriction = 0.7;
				viscousFriction = 0.6;
				rpmIdle = 800;
				rpmMin = 900;
				rpmClutch = 2400;
				rpmRedline = 6399;
			};
			class Clutch
			{
				maxTorqueTransfer = 180;
				uncoupleTime = 0.25;
				coupleTime = 0.3;
			};
			class Gearbox
			{
				type = "GEARBOX_AUTOMATIC";
				reverse = 3.526;
				ratios[] = {4.3, 2.15, 1.35, 0.9};
			};
			class Axles
			{
				class Front
				{
					maxBrakeTorque = 16100;
					wheelHubMass = 5;
					wheelHubRadius = 0.350149;
					class Differential
					{
						ratio = 3.667;
						type = "DIFFERENTIAL_OPEN";
					};
					class Suspension
					{
						stiffness = 30000;
						compression = 1050;
						damping = 2750;
						travelMaxUp = 0.10;
						travelMaxDown = 0.08;
					};
					class Wheels
					{
						class Left
						{
							animTurn = "turnfrontleft";
							animRotation = "wheelfrontleft";
							wheelHub = "wheel_1_1_damper_land";
							animDamper = "damper_1_1";
							inventorySlot = "Arma2Quad_wheel_1_1";
						};
						class Right
						{
							animTurn = "turnfrontright";
							animRotation = "wheelfrontright";
							wheelHub = "wheel_2_1_damper_land";
							animDamper = "damper_2_1";
							inventorySlot = "Arma2Quad_wheel_2_1";
						};
					};
				};
				class Rear
				{
					maxBrakeTorque = 16100;
					maxHandbrakeTorque = 3400;
					wheelHubMass = 5;
					wheelHubRadius = 0.350176;
					class Suspension
					{
						stiffness = 17000;
						compression = 1000;
						damping = 2550;
						travelMaxUp = 0.10;
						travelMaxDown = 0.08;
					};
					class Wheels
					{
						class Left
						{
							animTurn = "";
							animRotation = "wheelbackleft";
							wheelHub = "wheel_1_2_damper_land";
							animDamper = "damper_1_2";
							inventorySlot = "Arma2Quad_wheel_1_2";
						};
						class Right
						{
							animTurn = "";
							animRotation = "wheelbackright";
							wheelHub = "wheel_2_2_damper_land";
							animDamper = "damper_2_2";
							inventorySlot = "Arma2Quad_wheel_2_2";
						};
					};
				};
			};
		};

		class Cargo
		{
			itemsCargoSize[] = {10, 30};
			allowOwnedCargoManipulation = 1;
			openable = 1;
		};

		class AnimationSources
		{
			class damper_1_1
			{
				source = "user";
				initPhase = 0.4444;
				animPeriod = 1;
			};
			class damper_2_1: damper_1_1
			{
			};
			class damper_1_2: damper_1_1
			{
			};
			class damper_2_2: damper_1_2
			{
			};
		};

		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 5000;
					healthLevels[] =
					{
						{1.0, {}},
						{0.7, {}},
						{0.5, {}},
						{0.31, {}},
						{0.0, {}}
					};
				};
			};
			class DamageZones
			{
				class Chassis
				{
					displayName = "$STR_CfgVehicleDmg_Chassis0";
					fatalInjuryCoef = -1;
					componentNames[] = {"dmgZone_chassis"};
					class Health
					{
						hitpoints = 5000;
						transferToGlobalCoef = 0;
					};
					inventorySlots[] = {};
					inventorySlotsCoefs[] = {};
				};
				class Front
				{
					displayName = "$STR_CfgVehicleDmg_Bumper0";
					fatalInjuryCoef = -1;
					componentNames[] = {"dmgzone_front"};
					class Health
					{
						hitpoints = 5000;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0,{}}};
					};
					transferToZonesNames[] = {"Chassis", "Engine"};
					transferToZonesCoefs[] = {0.2, 0.15};
					inventorySlots[] = {"Arma2Quad_wheel_1_1", "Arma2Quad_wheel_2_1"};
					inventorySlotsCoefs[] = {0.3, 0.3};
				};
				class Reflector_1_1
				{
					displayName = "$STR_CfgVehicleDmg_Reflector0";
					fatalInjuryCoef = -1;
					componentNames[] = {"dmgZone_lights_1_1"};
					class Health
					{
						hitpoints = 50;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0,{}}};
					};
					transferToZonesNames[] = {"Front"};
					transferToZonesCoefs[] = {0.75};
					inventorySlots[] = {"Reflector_1_1", "Arma2Quad_wheel_1_1"};
					inventorySlotsCoefs[] = {1, 0.1};
				};
				class Reflector_2_1
				{
					displayName = "$STR_CfgVehicleDmg_Reflector0";
					fatalInjuryCoef = -1;
					componentNames[] = {"dmgZone_lights_2_1"};
					class Health
					{
						hitpoints = 50;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0,{}}};
					};
					transferToZonesNames[] = {"Front"};
					transferToZonesCoefs[] = {0.75};
					inventorySlots[] = {"Reflector_2_1", "Arma2Quad_wheel_2_1"};
					inventorySlotsCoefs[] = {1, 0.1};
				};
				class Back
				{
					displayName = "$STR_CfgVehicleDmg_Bumper0";
					fatalInjuryCoef = -1;
					componentNames[] = {"dmgzone_back"};
					class Health
					{
						hitpoints = 5000;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0,{}}};
					};
					transferToZonesNames[] = {"Chassis"};
					transferToZonesCoefs[] = {0.15};
					inventorySlots[] = {"Arma2Quad_wheel_1_2", "Arma2Quad_wheel_2_2"};
					inventorySlotsCoefs[] = {0.1, 0.1};
				};
				class Engine
				{
					displayName = "$STR_CfgVehicleDmg_Engine0";
					fatalInjuryCoef = 0.001;
					componentNames[] = {"dmgzone_engine"};
					class Health
					{
						hitpoints = 10000;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0,{}}};
					};
					inventorySlots[] = {"CarBattery", "SparkPlug"};
					inventorySlotsCoefs[] = {0.1, 0.05};
				};
				class FuelTank
				{
					displayName = "$STR_CfgVehicleDmg_FuelTank0";
					fatalInjuryCoef = -1;
					componentNames[] = {"dmgzone_fueltank"};
					class Health
					{
						hitpoints = 5000;
						transferToGlobalCoef = 0;
						healthLevels[] = {{1,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0,{}}};
					};
					inventorySlots[] = {};
					inventorySlotsCoefs[] = {};
				};
			};
		};

		class ObstacleGenerator
		{
			carve = 1;
			timeToStationary = 5;
			moveThreshold = 0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius = 0.75;
						height = 1.0;
						center[] = {0, 0, 0.45};
					};
					class Cyl2
					{
						radius = 0.75;
						height = 1.0;
						center[] = {0, 0, -0.45};
					};
				};
			};
		};

		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name = "$STR_attachment_Engine0";
				description = "";
				icon = "set:dayz_inventory image:cat_vehicle_engine";
				attachmentSlots[] = {"CarBattery", "SparkPlug"};
			};
			class Body
			{
				name = "$STR_attachment_Body0";
				description = "";
				icon = "set:dayz_inventory image:cat_vehicle_body";
				attachmentSlots[] = {"Reflector_1_1", "Reflector_2_1"};
			};
			class Chassis
			{
				name = "$STR_attachment_Chassis0";
				description = "";
				icon = "cat_vehicle_chassis";
				attachmentSlots[] = {"Arma2Quad_wheel_1_1", "Arma2Quad_wheel_2_1", "Arma2Quad_wheel_1_2", "Arma2Quad_wheel_2_2"};
			};
		};
	};

	class Arma2Quad: Arma2Quad_base
	{
		scope = 2;
		displayName = "Arma2Quad";
	};

	class Arma2Quad_Rust: Arma2Quad_base
	{
		scope = 2;
		displayName = "Arma2Quad Rust";
		hiddenSelectionsTextures[] =
		{
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"Arma2Quad\data\Arma2Quad_co_rust.paa",
			"Arma2Quad\data\Arma2Quad_detail_co.paa"
		};
	};

	class Arma2Quad_Sand: Arma2Quad_base
	{
		scope = 2;
		displayName = "Arma2Quad Sand";
		hiddenSelectionsTextures[] =
		{
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"Arma2Quad\data\Arma2Quad_co_sand.paa",
			"Arma2Quad\data\Arma2Quad_detail_co.paa"
		};
	};

	class Arma2Quad_Olive: Arma2Quad_base
	{
		scope = 2;
		displayName = "Arma2Quad Olive";
		hiddenSelectionsTextures[] =
		{
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"Arma2Quad\data\Arma2Quad_co_olive.paa",
			"Arma2Quad\data\Arma2Quad_detail_co.paa"
		};
	};

	class Arma2Quad_Blue: Arma2Quad_base
	{
		scope = 2;
		displayName = "Arma2Quad Blue";
		hiddenSelectionsTextures[] =
		{
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"Arma2Quad\data\Arma2Quad_co_blue.paa",
			"Arma2Quad\data\Arma2Quad_detail_co.paa"
		};
	};

	class Arma2Quad_Black: Arma2Quad_base
	{
		scope = 2;
		displayName = "Arma2Quad Black";
		hiddenSelectionsTextures[] =
		{
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"Arma2Quad\data\Arma2Quad_co_black.paa",
			"Arma2Quad\data\Arma2Quad_detail_co.paa"
		};
	};
};

class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyVehiclePart: ProxyAttachment
	{
		scope = 2;
		simulation = "ProxyInventory";
		autocenter = 0;
		animated = 0;
		shadow = 1;
		reversed = 0;
	};
	class ProxyArma2Quad_wheel_front: ProxyVehiclePart
	{
		model = "\Arma2Quad\Arma2Quad_wheel_front.p3d";
		inventorySlot[] = {"Arma2Quad_wheel_1_1", "Arma2Quad_wheel_2_1"};
	};
	class ProxyArma2Quad_wheel_rear: ProxyVehiclePart
	{
		model = "\Arma2Quad\Arma2Quad_wheel_rear.p3d";
		inventorySlot[] = {"Arma2Quad_wheel_1_2", "Arma2Quad_wheel_2_2"};
	};
	// A proxy binds one model file to the slots it may fill, so the ruined mesh needs
	// its own entry or the engine has no route to draw it once the attachment has been
	// replaced. Vanilla declares the same pair for every destroyed wheel, with the slot
	// list copied from the healthy proxy (DZ\vehicles\wheeled\config.cpp:22265, :22287).
	class ProxyArma2Quad_wheel_front_ruined: ProxyVehiclePart
	{
		model = "\Arma2Quad\Arma2Quad_wheel_front_ruined.p3d";
		inventorySlot[] = {"Arma2Quad_wheel_1_1", "Arma2Quad_wheel_2_1"};
	};
	class ProxyArma2Quad_wheel_rear_ruined: ProxyVehiclePart
	{
		model = "\Arma2Quad\Arma2Quad_wheel_rear_ruined.p3d";
		inventorySlot[] = {"Arma2Quad_wheel_1_2", "Arma2Quad_wheel_2_2"};
	};
};
