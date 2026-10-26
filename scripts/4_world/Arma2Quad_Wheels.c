// ============================================================
// Arma2Quad_Wheels.c
// Script classes of the Arma2Quad wheels and of their ruined twins.
//
// A wheel that reaches the ruined state is replaced by the class with
// the same name plus "_Ruined" (CarWheel.EEHealthLevelChanged,
// inventoryitem.c:220-248). Each wheel type resolves that name when its
// first entity is created and logs an error when the config class is
// missing (CarWheelType.SetReplacementTypes, inventoryitemtype.c:17-46).
// The ruined config classes, with their own models, are in config.cpp;
// like the vanilla ruined wheels (inventoryitem.c:449-468) they take
// their behaviour from CarWheel_Ruined.
// ============================================================
class Arma2Quad_Wheel_Front extends CarWheel {};
class Arma2Quad_Wheel_Rear extends CarWheel {};
class Arma2Quad_Wheel_Front_Ruined extends CarWheel_Ruined {};
class Arma2Quad_Wheel_Rear_Ruined extends CarWheel_Ruined {};
