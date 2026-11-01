class Arma2Quad_base extends CarScript
{
	protected ref Arma2Quad_LightProfileFront m_Arma2QuadFrontProfile;

#ifdef DIAG_DEVELOPER
	protected int m_A2QDiagLastMs;
	protected string m_A2QDiagImportantKey;
	protected string m_A2QDiagBucketKey;
#endif

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
	// does not explain the failure. Arma2Quad_LogGetInDiag is that log, compiled only with
	// DIAG_DEVELOPER. Do not change the point this returns until that log has been read in game.
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

#ifdef DIAG_DEVELOPER
	protected void Arma2Quad_DiagEmit(string line)
	{
		Print(line);
		ErrorEx(line);
	}

	// doorPoint is GetDoorConditionPointFromSelection. planarDist is the Y-flattened world
	// distance CarScript.CanReachSeatFromDoors compares with 1.0; it stays -1 when the memory
	// point is missing, because that path never measures a distance.
	protected void Arma2Quad_DiagSelection(string selection, vector playerPos, out string doorPoint, out int memExists, out vector memMS, out float planarDist, out int within1m, out int reachSeat, out int crewIndex)
	{
		doorPoint = GetDoorConditionPointFromSelection(selection);
		memExists = 0;
		memMS = "0 0 0";
		planarDist = -1;
		within1m = 0;
		reachSeat = 0;
		crewIndex = GetCrewIndex(selection);

		if (doorPoint.Length() > 0 && MemoryPointExists(doorPoint))
		{
			memExists = 1;
			memMS = GetMemoryPointPos(doorPoint);

			vector memWS = ModelToWorld(memMS);
			vector fromWS = playerPos;
			memWS[1] = 0;
			fromWS[1] = 0;
			planarDist = vector.Distance(fromWS, memWS);
			if (planarDist <= 1.0)
				within1m = 1;
		}

		vector reachFrom = playerPos;
		if (CanReachSeatFromDoors(selection, reachFrom, 1.0))
			reachSeat = 1;

		if (doorPoint.Length() == 0)
			doorPoint = "(none)";
	}

	protected string Arma2Quad_DiagSelectionText(string selection, vector playerPos, out string keyReach, out string keyBucket)
	{
		string doorPoint;
		int memExists;
		vector memMS;
		float planarDist;
		int within1m;
		int reachSeat;
		int crewIndex;
		Arma2Quad_DiagSelection(selection, playerPos, doorPoint, memExists, memMS, planarDist, within1m, reachSeat, crewIndex);

		float bucket = -1;
		if (planarDist >= 0)
			bucket = Math.Floor(planarDist * 2.0);

		keyReach = string.Format("%1:%2:%3:%4", selection, memExists, reachSeat, crewIndex);
		keyBucket = string.Format("%1:%2", selection, bucket);

		if (memExists)
			return string.Format("sel=%1 doorPoint=%2 memExists=1 memMS=%3 planarDist=%4 within1m=%5 reachSeat=%6 crewIndex=%7", selection, doorPoint, memMS, planarDist, within1m, reachSeat, crewIndex);

		return string.Format("sel=%1 doorPoint=%2 memExists=0 memMS=missing planarDist=-1 within1m=0 reachSeat=%3 crewIndex=%4", selection, doorPoint, reachSeat, crewIndex);
	}

	// Called from ActionGetInTransport while the player is looking at this quad. The return
	// value of the action is untouched; this only prints.
	void Arma2Quad_LogGetInDiag(PlayerBase player, int componentIndex, bool actionResult)
	{
		if (!player || !GetGame())
			return;

		vector playerPos = player.GetPosition();
		float localX = WorldToModel(playerPos)[0];
		int sideSign = 0;
		if (localX < -0.05)
			sideSign = -1;
		else if (localX > 0.05)
			sideSign = 1;

		int resultInt = 0;
		if (actionResult)
			resultInt = 1;

		int canGetIn = 0;
		if (CanGetIn())
			canGetIn = 1;

		int heavy = 0;
		if (player.GetItemInHands() && player.GetItemInHands().IsHeavyBehaviour())
			heavy = 1;

		int inVeh = 0;
		if (player.GetCommand_Vehicle())
			inVeh = 1;

		int crewPos = CrewPositionIndex(componentIndex);
		int occupied = -1;
		int through = -1;
		int areaFree = -1;
		int areaFreeDiag = -1;
		if (crewPos >= 0)
		{
			occupied = 0;
			if (CrewMember(crewPos))
				occupied = 1;

			through = 0;
			if (CrewCanGetThrough(crewPos))
				through = 1;

			areaFree = 0;
			if (IsAreaAtDoorFree(crewPos))
				areaFree = 1;

			areaFreeDiag = 0;
			if (IsAreaAtDoorFreeDiag(crewPos))
				areaFreeDiag = 1;
		}

		array<string> selections = new array<string>();
		GetActionComponentNameList(componentIndex, selections);

		string sels = "";
		string resolvedReachKey = "";
		string resolvedBucketKey = "";
		array<string> resolvedLines = new array<string>();
		string reachKey;
		string bucketKey;
		string resolved;
		for (int i = 0; i < selections.Count(); i++)
		{
			if (sels.Length() > 0)
				sels = sels + ",";
			sels = sels + selections[i];

			resolved = Arma2Quad_DiagSelectionText(selections[i], playerPos, reachKey, bucketKey);
			resolvedLines.Insert(string.Format("[A2Q-DIAG] resolved comp=%1 %2", componentIndex, resolved));

			if (resolvedReachKey.Length() > 0)
				resolvedReachKey = resolvedReachKey + ",";
			resolvedReachKey = resolvedReachKey + reachKey;

			if (resolvedBucketKey.Length() > 0)
				resolvedBucketKey = resolvedBucketKey + ",";
			resolvedBucketKey = resolvedBucketKey + bucketKey;
		}

		if (sels.Length() == 0)
			sels = "(none)";

		string driverReach;
		string driverBucket;
		string driverSel = Arma2Quad_DiagSelectionText("seat_driver", playerPos, driverReach, driverBucket);
		string codriverReach;
		string codriverBucket;
		string codriverSel = Arma2Quad_DiagSelectionText("seat_codriver", playerPos, codriverReach, codriverBucket);

		int driverAnim = GetSeatAnimationType(0);
		int codriverAnim = GetSeatAnimationType(1);

		string driverDoor = GetDoorSelectionNameFromSeatPos(0);
		string codriverDoor = GetDoorSelectionNameFromSeatPos(1);
		int driverDoors = 0;
		if (CanReachDoorsFromSeat(driverDoor, 0))
			driverDoors = 1;
		int codriverDoors = 0;
		if (CanReachDoorsFromSeat(codriverDoor, 1))
			codriverDoors = 1;
		if (driverDoor.Length() == 0)
			driverDoor = "(none)";
		if (codriverDoor.Length() == 0)
			codriverDoor = "(none)";

		int animInst = GetAnimInstance();
		int posDriverExists = 0;
		if (MemoryPointExists("pos_driver"))
			posDriverExists = 1;
		int posCodriverExists = 0;
		if (MemoryPointExists("pos_codriver"))
			posCodriverExists = 1;

		int isServer = 0;
		if (GetGame().IsServer())
			isServer = 1;
		int isClient = 0;
		if (GetGame().IsClient())
			isClient = 1;

		string important = string.Format("%1|%2|%3|%4|%5|%6|%7", resultInt, componentIndex, crewPos, sideSign, sels, driverReach, codriverReach);
		important = important + string.Format("|%1|%2|%3|%4|%5|%6", driverDoors, codriverDoors, driverAnim, codriverAnim, animInst, resolvedReachKey);
		important = important + string.Format("|%1|%2|%3|%4|%5|%6", canGetIn, heavy, inVeh, occupied, through, areaFreeDiag);

		string buckets = string.Format("%1|%2|%3", driverBucket, codriverBucket, resolvedBucketKey);

		int now = GetGame().GetTime();
		bool importantChanged = important != m_A2QDiagImportantKey;
		bool bucketChanged = buckets != m_A2QDiagBucketKey;
		if (!importantChanged && !bucketChanged)
			return;
		if (!importantChanged && bucketChanged && (now - m_A2QDiagLastMs) < 400)
			return;

		m_A2QDiagImportantKey = important;
		m_A2QDiagBucketKey = buckets;
		m_A2QDiagLastMs = now;

		string actionLine = string.Format("[A2Q-DIAG] ActionCondition result=%1 type=%2 comp=%3 crewPos=%4 sels=%5", resultInt, GetType(), componentIndex, crewPos, sels);
		actionLine = actionLine + string.Format(" animInst=%1 localX=%2 side=%3 server=%4 client=%5", animInst, localX, sideSign, isServer, isClient);
		actionLine = actionLine + string.Format(" canGetIn=%1 heavy=%2 inVeh=%3 occupied=%4 through=%5", canGetIn, heavy, inVeh, occupied, through);
		actionLine = actionLine + string.Format(" areaFree=%1 areaFreeDiag=%2 pos_driverExists=%3 pos_codriverExists=%4", areaFree, areaFreeDiag, posDriverExists, posCodriverExists);
		Arma2Quad_DiagEmit(actionLine);

		Arma2Quad_DiagEmit(string.Format("[A2Q-DIAG] role=driver actionSel=seat_driver %1 seatAnim=%2 doorSel=%3 reachDoors=%4", driverSel, driverAnim, driverDoor, driverDoors));
		Arma2Quad_DiagEmit(string.Format("[A2Q-DIAG] role=codriver actionSel=seat_codriver %1 seatAnim=%2 doorSel=%3 reachDoors=%4", codriverSel, codriverAnim, codriverDoor, codriverDoors));

		for (int r = 0; r < resolvedLines.Count(); r++)
			Arma2Quad_DiagEmit(resolvedLines[r]);
	}
#endif
};
