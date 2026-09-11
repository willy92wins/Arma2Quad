class Arma2Quad_base extends CarScript
{
	bool m_Arma2QuadLightsWanted;
	CarLightBase m_Arma2QuadExitLight;

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
		m_CarHornShortSoundName = "Hatchback_02_Horn_Short_SoundSet";
		m_CarHornLongSoundName = "Hatchback_02_Horn_SoundSet";

		RegisterNetSyncVariableBool("m_Arma2QuadLightsWanted");
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

	override bool IsVitalTruckBattery()
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

	override CarLightBase CreateFrontLight()
	{
		return CarLightBase.Cast(ScriptedLightBase.CreateLight(Arma2Quad_FrontLight));
	}

	override CarRearLightBase CreateRearLight()
	{
		return CarRearLightBase.Cast(ScriptedLightBase.CreateLight(Arma2Quad_RearLight));
	}

	override float GetActionDistanceFuel()
	{
		return 3.2;
	}

	override void OnDriverExit(Human player)
	{
		bool wasRunning = EngineIsOn();
		super.OnDriverExit(player);
		if (wasRunning && !EngineIsOn())
			EngineStart();

		if (GetGame().IsServer())
		{
			ForceUpdateLightsStart();
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ForceUpdateLightsEnd, 100, false);
		}
	}

	void ManageExitLight()
	{
		bool need = m_Arma2QuadLightsWanted && !LightIsOn() && m_HeadlightsState != CarHeadlightBulbsState.NONE && !IsDamageDestroyed();
		if (need && !m_Arma2QuadExitLight)
		{
			m_Arma2QuadExitLight = CreateFrontLight();
			if (m_Arma2QuadExitLight)
			{
				vector posLeft = GetMemoryPointPos(m_LeftHeadlightPoint);
				vector posRight = GetMemoryPointPos(m_RightHeadlightPoint);
				m_Arma2QuadExitLight.AttachOnObject(this, (posLeft + posRight) * 0.5);
				m_Arma2QuadExitLight.AggregateLight();
			}
		}
		else if (!need && m_Arma2QuadExitLight)
		{
			m_Arma2QuadExitLight.FadeOut();
			m_Arma2QuadExitLight = null;
		}
	}

	override void UpdateLightsClient(int newGear = -1)
	{
		super.UpdateLightsClient(newGear);
		ManageExitLight();
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		if (m_Arma2QuadExitLight)
		{
			m_Arma2QuadExitLight.Destroy();
			m_Arma2QuadExitLight = null;
		}
	}

	override void ToggleHeadlights()
	{
		super.ToggleHeadlights();
		m_Arma2QuadLightsWanted = IsScriptedLightsOn();
		if (GetGame().IsServer())
			SetSynchDirty();
	}

	//! Spawns from the Central Economy with a full tank. Vanilla CarScript fills a random
	//! 0-35 % (carscript.c:2967-2974); this tops up to capacity from whatever that left, so
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

	// Reach condition point for CanReachSeatFromDoors (carscript.c:2710-2732). Vanilla and
	// LFQuad return centred seat_con_* points; this model has none baked and uses the approach
	// points instead.
	//
	// Substituting the centred crew points was TRIED on 2026-09-07 and REVERTED: in game the
	// driver entering from the right ended up yawed 15-20 deg and the codriver became
	// unreachable from BOTH sides. The offline arithmetic had predicted it would pass
	// (0.85 m driver, 0.83 m codriver against the 1.0 m default), so the default is not what
	// the engine passes: CanReachSeatFromDoors is invoked natively - no vanilla script calls
	// it - and neither pDistance nor pFromPos are observable from script. Instrument them with
	// a logging override before touching this again.
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
