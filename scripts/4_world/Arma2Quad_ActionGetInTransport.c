// Arma2Quad bilateral get-in: snap the player to the side of the bench they approached from, so a
// right-side approach does not spin the player >180 deg. The engine forces yaw toward
// dir(pos_<role> -> pos_<role>_dir), which sits on one side only. The approach side is read
// BEFORE super (super moves the player toward the seat centre, which loses the side), then the
// snap mirrors the base point in X to the approach side. The quad is symmetric (shared bench),
// so the mirror is exact; no _L/_R memory points needed.
// Pattern: dayz-animation-pipeline references/dual-entry-action-pattern.md (runtime-mirror variant).
modded class ActionGetInTransport
{
	override void OnStartServer(ActionData action_data)
	{
		float preX = Arma2Quad_ApproachX(action_data);
		super.OnStartServer(action_data);
		Arma2Quad_RealignSeatSide(action_data, preX);
	}

	override void OnStartClient(ActionData action_data)
	{
		float preX = Arma2Quad_ApproachX(action_data);
		super.OnStartClient(action_data);
		Arma2Quad_RealignSeatSide(action_data, preX);
	}

	// Player local-X relative to the quad BEFORE super runs. 999 = not our vehicle / invalid.
	protected float Arma2Quad_ApproachX(ActionData action_data)
	{
		if (!action_data || !action_data.m_Player || !action_data.m_Target)
			return 999;
		Arma2Quad_base quad;
		if (!Class.CastTo(quad, action_data.m_Target.GetObject()))
			return 999;
		return quad.WorldToModel(action_data.m_Player.GetPosition())[0];
	}

	protected void Arma2Quad_RealignSeatSide(ActionData action_data, float preX)
	{
		if (preX > 900)
			return;
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		if (!player)
			return;
		Arma2Quad_base quad;
		if (!Class.CastTo(quad, action_data.m_Target.GetObject()))
			return;

		// Nearest seat by crew memory point (the action slot is not always reliable here).
		vector postLocal = quad.WorldToModel(player.GetPosition());
		bool isDriver = true;
		if (quad.MemoryPointExists("crewdriver") && quad.MemoryPointExists("crewcodriver"))
			isDriver = vector.Distance(postLocal, quad.GetMemoryPointPos("crewdriver")) <= vector.Distance(postLocal, quad.GetMemoryPointPos("crewcodriver"));

		string role = "codriver";
		if (isDriver)
			role = "driver";

		string memPos = "pos_" + role;
		string memDir = "pos_" + role + "_dir";
		if (!quad.MemoryPointExists(memPos) || !quad.MemoryPointExists(memDir))
			return;

		// Base point is on one side; mirror in X to the side the player approached from.
		vector pos = quad.GetMemoryPointPos(memPos);
		vector dir = quad.GetMemoryPointPos(memDir);
		if ((preX < 0) != (pos[0] < 0))
		{
			pos[0] = -pos[0];
			dir[0] = -dir[0];
		}

		vector worldPos = quad.ModelToWorld(pos);
		vector worldDir = quad.ModelToWorld(dir);
		vector look = worldDir - worldPos;
		look[1] = 0;
		if (look.LengthSq() < 0.0001)
			return;

		float yaw = look.VectorToAngles()[0];

		worldPos[1] = player.GetPosition()[1];
		player.SetPosition(worldPos);

		vector ori = player.GetOrientation();
		player.SetOrientation(Vector(yaw, ori[1], ori[2]));
	}
}
