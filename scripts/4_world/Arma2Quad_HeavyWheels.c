// ============================================================
// Arma2Quad_HeavyWheels.c
// Registers the Arma2Quad wheels as heavy, two-handed carry items.
//
// A wheel taken in hands defaults to the one-handed tools profile
// (Inventory_Base catch-all, dayzplayercfgbase.c:373) because the heavy
// in-hands IK profile is registered per exact leaf class and CarWheel is
// not in that list. Vanilla wheels register explicitly (e.g. CivSedanWheel,
// dayzplayercfgbase.c:868). Reuse the vanilla sedan-wheel heavy IK assets;
// the .asi workspace and .anm are present in base DayZ.
//
// The ruined classes are separate leaf types, so they need their own entry or a
// destroyed wheel taken in hands falls back to the one-handed profile. Vanilla
// registers every ruined wheel too; the sedan set carries a destroyed pose of its
// own, used by CivSedanWheel_Ruined (dayzplayercfgbase.c:869).
// ============================================================
modded class ModItemRegisterCallbacks
{
	override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterHeavy(pType, pBehavior);
		pType.AddItemInHandsProfileIK("Arma2Quad_Wheel_Front", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/vehicles/sedan/sedan_wheel.anm");
		pType.AddItemInHandsProfileIK("Arma2Quad_Wheel_Rear",  "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/vehicles/sedan/sedan_wheel.anm");
		pType.AddItemInHandsProfileIK("Arma2Quad_Wheel_Front_Ruined", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/vehicles/sedan/sedan_wheeldestroyed.anm");
		pType.AddItemInHandsProfileIK("Arma2Quad_Wheel_Rear_Ruined",  "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/vehicles/sedan/sedan_wheeldestroyed.anm");
	}
}
