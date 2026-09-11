// ============================================================
// Arma2Quad_Wheels.c
// Ruined-wheel replacement for Arma2Quad.
//
// CarWheel.EEHealthLevelChanged swaps a wheel that reaches STATE_RUINED for the
// type returned by GetRuinedReplacement (inventoryitem.c:250-279). That method is
// a switch over seven hardcoded vanilla classnames (inventoryitem.c:214-248) and
// returns "" for anything else, and an empty name means no swap at all, so a modded
// wheel keeps wearing its healthy model once destroyed. Each leaf class resolves its
// own name here; modding CarWheel would reach the wheels of every vehicle instead.
//
// A ruined wheel cannot be repaired back in play: PluginRepairing.CanRepair rejects
// a ruined item before it ever reads repairableWithKits (pluginrepairing.c:96), and
// every repair path goes through it. GetReplacement only feeds the debug "fix the
// whole car" route, compiled out of retail builds (inventoryitem.c:375-392); it is
// implemented for parity with the vanilla wheels.
// ============================================================

class Arma2Quad_Wheel_Front extends CarWheel
{
	override string GetRuinedReplacement()
	{
		return "Arma2Quad_Wheel_Front_Ruined";
	}
}

class Arma2Quad_Wheel_Rear extends CarWheel
{
	override string GetRuinedReplacement()
	{
		return "Arma2Quad_Wheel_Rear_Ruined";
	}
}

class Arma2Quad_Wheel_Front_Ruined extends CarWheel_Ruined
{
	override string GetReplacement()
	{
		return "Arma2Quad_Wheel_Front";
	}
}

class Arma2Quad_Wheel_Rear_Ruined extends CarWheel_Ruined
{
	override string GetReplacement()
	{
		return "Arma2Quad_Wheel_Rear";
	}
}
