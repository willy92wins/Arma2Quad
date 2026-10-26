// Arma2Quad light profiles for the DayZ 1.30 VehicleLightsComponent, registered in the
// Arma2Quad_base constructor. They replace the CarLightBase subclasses that
// CreateFrontLight/CreateRearLight returned up to 1.29; CarScript no longer calls those
// factories. Values carried over unchanged from the 1.29 Arma2Quad_FrontLight and
// Arma2Quad_RearLight.

// Headlight: a dim, wide, warm beam sized for a quad. Segregated = one bulb left,
// aggregated = both bulbs as one light.
class Arma2Quad_LightProfileFront : VehicleLightProfileFront
{
	void Arma2Quad_LightProfileFront()
	{
		m_SegregatedBrightness = 3;
		m_SegregatedRadius = 55;
		m_SegregatedAngle = 110;
		m_SegregatedColorRGB = Vector(1.0, 0.8, 0.6);

		m_AggregatedBrightness = 6;
		m_AggregatedRadius = 75;
		m_AggregatedAngle = 120;
		m_AggregatedColorRGB = Vector(1.0, 0.8, 0.6);
	}
}

// Rear light: the ATV has brake and tail lenses but no separate reverse lens.
class Arma2Quad_LightProfileRear : VehicleLightProfileBrakeAndReverse
{
	void Arma2Quad_LightProfileRear()
	{
		// Brake light only
		m_SegregatedBrakeBrightness = 4;
		m_SegregatedBrakeRadius = 10;
		m_SegregatedBrakeAngle = 180;
		m_SegregatedBrakeColorRGB = Vector(1.0, 0.05, 0.025);

		// Reverse light only: no lens, so it emits nothing
		m_SegregatedBrightness = 0;
		m_SegregatedRadius = 0;
		m_SegregatedAngle = 180;
		m_SegregatedColorRGB = Vector(0, 0, 0);

		// Brake and reverse together: the red brake beam, without inventing white light
		m_AggregatedBrightness = 4;
		m_AggregatedRadius = 10;
		m_AggregatedAngle = 180;
		m_AggregatedColorRGB = Vector(1.0, 0.05, 0.025);

		// The fade-out the 1.29 rear light used for the brake and reverse states
		m_FadeOutTime = 0.1;
	}
}
