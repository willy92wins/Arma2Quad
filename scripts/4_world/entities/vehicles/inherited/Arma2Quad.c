class Arma2Quad_base extends CarScript
{
	protected ref Arma2Quad_LightProfileFront m_Arma2QuadFrontProfile;

	void Arma2Quad_base()
	{
		m_dmgContactCoef = 0.02;
		m_EngineStartOK = "Hatchback_02_engine_start_SoundSet";
		m_EngineStartBattery = "Hatchback_02_engine_failed_start_battery_SoundSet";
		m_EngineStartPlug = "Hatchback_02_engine_failed_start_sparkplugs_SoundSet";
		m_EngineStartFuel = "Hatchback_02_engine_failed_start_fuel_SoundSet";
		m_EngineStopFuel = "offroad_engine_stop_fuel_SoundSet";
		m_CarDoorOpenSound = "offroad_door_open_SoundSet";
		m_CarDoorCloseSound = "offroad_door_close_SoundSet";

		// Lights and horn are CarScript components since DayZ 1.30: the base registers generic
		// light profiles and no horn sound.
		m_Arma2QuadFrontProfile = new Arma2Quad_LightProfileFront();
		m_LightsComponent.RegisterLight("Front", new VehicleLightData(m_Arma2QuadFrontProfile));
		m_LightsComponent.RegisterLight("Rear", new VehicleLightData(new Arma2Quad_LightProfileRear()));

		m_HornComponent.RegisterSound(VehicleHornMode.SHORT, "Hatchback_02_Horn_Short_SoundSet");
		m_HornComponent.RegisterSound(VehicleHornMode.LONG, "Hatchback_02_Horn_SoundSet");
	}

	override int GetAnimInstance()
	{
		string survivorPatch = "CfgPatches SurvivorAnims";
		if (GetGame().ConfigIsExisting(survivorPatch))
		{
			return 22;
		}

		return VehicleAnimInstances.V3S;
	}

	override int GetSeatAnimationType(int posIdx)
	{
		switch (posIdx)
		{
			case 0:
				return DayZPlayerConstants.VEHICLESEAT_DRIVER;
			case 1:
				return DayZPlayerConstants.VEHICLESEAT_CODRIVER;
		}

		return 0;
	}

	override bool CrewCanGetThrough(int posIdx)
	{
		switch (posIdx)
		{
			case 0:
				return true;
			case 1:
				return true;
		}

		return false;
	}

	override bool IsVitalGlowPlug()
	{
		return false;
	}

	override bool IsVitalRadiator()
	{
		return false;
	}

	override bool IsVitalEngineBelt()
	{
		return false;
	}

	// The battery is found through the electricity source since DayZ 1.30. Transport answers no
	// device by default, and CarScript then reports NO_BATTERY with a battery attached: the engine
	// never starts and the lights action never shows. Same three overrides as the vanilla
	// petrol cars.
	override bool NeedElectricitySourceDevice()
	{
		return true;
	}

	override EntityAI GetElectricitySourceDevice()
	{
		return GetInventory().FindAttachment(CarBattery.SLOT_ID);
	}

	override string GetElectricitySourceDeviceType()
	{
		return "CarBattery";
	}

	override float GetActionDistanceFuel()
	{
		return 3.2;
	}

	// Keep the engine running when the driver dismounts: CarScript.OnDriverExit stops it unless
	// the gearbox is in neutral. The headlights need nothing here: since DayZ 1.30 the native
	// light state survives the driver's exit, on the server and on the clients.
	override void OnDriverExit(Human player)
	{
		bool wasRunning = EngineIsOn();
		super.OnDriverExit(player);
		if (wasRunning && !EngineIsOn())
			EngineStart();

		#ifdef DIAG_DEVELOPER
		Print(string.Format("[Arma2Quad] driver exit server=%1 lightIsOn=%2 engine=%3", GetGame().IsServer(), LightIsOn(), EngineIsOn()));
		#endif
	}

	// The front profile switches its lens flare off whenever both bulbs light as one
	// (VehicleLightProfileFront.ApplyAggregatedValues) and nothing switches it back on, so once
	// both bulbs had been lit a headlight left with one bulb would show no flare for the rest of
	// the vehicle's life. Up to 1.29 every single-bulb headlight showed it
	// (CarLightBase.SegregateLight); the flag is restored here before the single-bulb state is
	// applied.
	override void UpdateLightsClient(int newGear = -1)
	{
		if (m_HeadlightsState == CarHeadlightBulbsState.LEFT || m_HeadlightsState == CarHeadlightBulbsState.RIGHT)
			m_Arma2QuadFrontProfile.m_FlaresVisible = true;

		super.UpdateLightsClient(newGear);
	}

	//! Spawns from the Central Economy with a full tank. Vanilla CarScript fills a random
	//! 0-35 % (carscript.c:2412-2419); this tops up to capacity from whatever that left, so
	//! the result does not depend on Fill clamping at capacity.
	override void EEOnCECreate()
	{
		super.EEOnCECreate();
		Fill(CarFluid.FUEL, GetFluidCapacity(CarFluid.FUEL) * (1.0 - GetFluidFraction(CarFluid.FUEL)));
	}

	override void OnDebugSpawn()
	{
		EntityAI entity;
		if (Class.CastTo(entity, this))
		{
			entity.GetInventory().CreateAttachment("CarBattery");
			entity.GetInventory().CreateAttachment("SparkPlug");
			entity.GetInventory().CreateAttachment("HeadlightH7");
			entity.GetInventory().CreateAttachment("HeadlightH7");
			entity.GetInventory().CreateAttachment("Arma2Quad_Wheel_Front");
			entity.GetInventory().CreateAttachment("Arma2Quad_Wheel_Front");
			entity.GetInventory().CreateAttachment("Arma2Quad_Wheel_Rear");
			entity.GetInventory().CreateAttachment("Arma2Quad_Wheel_Rear");
		}

		Fill(CarFluid.FUEL, GetFluidCapacity(CarFluid.FUEL));
	}

	// Reach condition point for CanReachSeatFromDoors (carscript.c:2177-2199). Vanilla and
	// LFQuad return centred seat_con_* points; this model has none baked and uses the approach
	// points instead.
	//
	// Substituting the centred crew points was TRIED on 2026-09-07 and REVERTED: in game the
	// driver entering from the right ended up yawed 15-20 deg and the codriver became
	// unreachable from BOTH sides. The offline arithmetic had predicted it would pass
	// (0.85 m driver, 0.83 m codriver against the 1.0 m limit). That limit is what the get-in
	// action passes, with the player's position (actiongetintransport.c:64), so the arithmetic
	// does not explain the failure. Instrument CanReachSeatFromDoors with a logging override
	// before touching this again.
	override string GetDoorConditionPointFromSelection(string selection)
	{
		switch (selection)
		{
			case "seat_driver":
			case "seatback_driver":
				return "pos_driver";
			case "seat_codriver":
			case "seatback_codriver":
				return "pos_codriver";
		}

		return "";
	}

	override int GetCrewIndex(string selection)
	{
		switch (selection)
		{
			case "seat_driver":
			case "seatback_driver":
				return 0;
			case "seat_codriver":
			case "seatback_codriver":
				return 1;
		}

		return -1;
	}
};
