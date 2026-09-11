/**
 * @brief Client-side rider bone positions in the vehicle model frame.
 * Diagnostic only. Bone origins are not calibrated palm contacts.
 * Geometry APIs: object.c:244,458-460; human.c:1387; game.c:718; entity.c:12.
 *
 * The data line is concatenated instead of formatted in one call: a nine-argument
 * string.Format whose arguments are themselves formatted strings placed the last
 * vector's first component in slot %1, so the elapsed time read back as the pelvis X.
 * The short formats below print correctly and are kept. Print() takes an expression
 * rather than a bare variable, which DayZDiag would otherwise echo as an assignment.
 *
 * w= is the rendered handlebar phase (model.cfg class drivingwheel, source
 * steeringwheel, range -1..1 across angle0/angle1). A keyboard drives GetSteering() to
 * -1, 0 or +1 only, so the animation phase is what carries the intermediate sweep.
 */
modded class CarScript
{
	const string RIDER_PROBE_TYPES = "LFQuad3;Arma2Quad;OffroadHatchback";
	const string RIDER_PROBE_WHEEL_ANIM = "drivingwheel";
	const float RIDER_PROBE_PERIOD = 0.1;
	protected float m_RiderProbeAccum;
	protected float m_RiderProbeElapsed;
	protected bool m_RiderProbeHeader;
	protected bool m_RiderProbeTypesReady;
	protected bool m_RiderProbeEnabled;
	protected Human m_RiderProbeDriver;
	protected int m_RiderProbeBones[9];

	//! Decimal formatting avoids a platform-specific float format specifier.
	protected string RiderProbeDecimal(float RiderProbeValue)
	{
		string RiderProbeSign = "";
		if (RiderProbeValue < 0)
		{
			RiderProbeSign = "-";
			RiderProbeValue = -RiderProbeValue;
		}
		int RiderProbeScaled = RiderProbeValue * 10000 + 0.5;
		int RiderProbeWhole = RiderProbeScaled / 10000;
		int RiderProbeFraction = RiderProbeScaled - RiderProbeWhole * 10000;
		string RiderProbePad = "";
		if (RiderProbeFraction < 1000) RiderProbePad += "0";
		if (RiderProbeFraction < 100) RiderProbePad += "0";
		if (RiderProbeFraction < 10) RiderProbePad += "0";
		return string.Format("%1%2.%3%4", RiderProbeSign, RiderProbeWhole, RiderProbePad, RiderProbeFraction);
	}

	protected string RiderProbeVector(vector RiderProbePosition)
	{
		return string.Format("%1,%2,%3", RiderProbeDecimal(RiderProbePosition[0]), RiderProbeDecimal(RiderProbePosition[1]), RiderProbeDecimal(RiderProbePosition[2]));
	}

	protected string RiderProbeMemory(string RiderProbeName)
	{
		if (!MemoryPointExists(RiderProbeName)) return "none";
		return RiderProbeVector(GetMemoryPointPos(RiderProbeName));
	}

	protected string RiderProbeBone(int RiderProbeSlot)
	{
		if (RiderProbeSlot < 0 || RiderProbeSlot >= 9) return "none";
		if (!m_RiderProbeDriver) return "none";
		int RiderProbeIndex = m_RiderProbeBones[RiderProbeSlot];
		if (RiderProbeIndex < 0) return "none";
		vector RiderProbePosition = GetGame().ObjectWorldToModel(this, m_RiderProbeDriver.GetBonePositionWS(RiderProbeIndex));
		return RiderProbeVector(RiderProbePosition);
	}

	protected void RiderProbeCache(Human RiderProbeDriver)
	{
		m_RiderProbeDriver = RiderProbeDriver;
		m_RiderProbeBones[0] = RiderProbeDriver.GetBoneIndexByName("LeftHand");
		m_RiderProbeBones[1] = RiderProbeDriver.GetBoneIndexByName("RightHand");
		m_RiderProbeBones[2] = RiderProbeDriver.GetBoneIndexByName("LeftForeArmRoll");
		m_RiderProbeBones[3] = RiderProbeDriver.GetBoneIndexByName("RightForeArmRoll");
		m_RiderProbeBones[4] = RiderProbeDriver.GetBoneIndexByName("LeftFoot");
		m_RiderProbeBones[5] = RiderProbeDriver.GetBoneIndexByName("RightFoot");
		m_RiderProbeBones[6] = RiderProbeDriver.GetBoneIndexByName("Pelvis");
		m_RiderProbeBones[7] = RiderProbeDriver.GetBoneIndexByName("Spine3");
		m_RiderProbeBones[8] = RiderProbeDriver.GetBoneIndexByName("Head");
	}

	override void OnInput(float dt)
	{
		super.OnInput(dt);
		if (GetGame().IsDedicatedServer()) return;
		if (!m_RiderProbeTypesReady)
		{
			string RiderProbeTypesRaw = RIDER_PROBE_TYPES;
			array<string> RiderProbeTypes = {};
			RiderProbeTypesRaw.Split(";", RiderProbeTypes);
			foreach (string RiderProbeType : RiderProbeTypes)
			{
				if (RiderProbeType != "" && GetType().Contains(RiderProbeType)) m_RiderProbeEnabled = true;
			}
			m_RiderProbeTypesReady = true;
		}
		if (!m_RiderProbeEnabled) return;
		Human RiderProbeDriver = CrewDriver();
		if (!RiderProbeDriver || RiderProbeDriver != GetGame().GetPlayer())
		{
			m_RiderProbeDriver = null;
			m_RiderProbeAccum = 0;
			return;
		}
		if (RiderProbeDriver != m_RiderProbeDriver) RiderProbeCache(RiderProbeDriver);
		m_RiderProbeElapsed += dt;
		m_RiderProbeAccum += dt;
		if (m_RiderProbeAccum < RIDER_PROBE_PERIOD) return;
		// Preserve the fractional remainder without duplicating stale frames.
		while (m_RiderProbeAccum >= RIDER_PROBE_PERIOD) m_RiderProbeAccum -= RIDER_PROBE_PERIOD;
		if (!m_RiderProbeHeader)
		{
			string RiderProbeHead = string.Format("[RIDER-HANDS] hdr veh=%1 anim=%2", GetType(), GetAnimInstance());
			RiderProbeHead += " mp_crewdriver=" + RiderProbeMemory("crewdriver");
			RiderProbeHead += " mp_pos_driver=" + RiderProbeMemory("pos_driver");
			RiderProbeHead += " mp_drivewheel_axis=" + RiderProbeMemory("drivewheel_axis");
			Print(string.Format("%1", RiderProbeHead));
			m_RiderProbeHeader = true;
		}
		string RiderProbeLine = "[RIDER-HANDS] t=" + RiderProbeDecimal(m_RiderProbeElapsed);
		RiderProbeLine += " s=" + RiderProbeDecimal(GetSteering());
		RiderProbeLine += " w=" + RiderProbeDecimal(GetAnimationPhase(RIDER_PROBE_WHEEL_ANIM));
		RiderProbeLine += " LH=" + RiderProbeBone(0);
		RiderProbeLine += " RH=" + RiderProbeBone(1);
		RiderProbeLine += " LFA=" + RiderProbeBone(2);
		RiderProbeLine += " RFA=" + RiderProbeBone(3);
		RiderProbeLine += " LF=" + RiderProbeBone(4);
		RiderProbeLine += " RF=" + RiderProbeBone(5);
		RiderProbeLine += " PEL=" + RiderProbeBone(6);
		RiderProbeLine += " SP3=" + RiderProbeBone(7);
		RiderProbeLine += " HEAD=" + RiderProbeBone(8);
		Print(string.Format("%1", RiderProbeLine));
	}
}
