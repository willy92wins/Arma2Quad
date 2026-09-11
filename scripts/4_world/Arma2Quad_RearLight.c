class Arma2Quad_RearLight extends CarRearLightBase
{
	void Arma2Quad_RearLight()
	{
		m_SegregatedBrakeBrightness = 4;
		m_SegregatedBrakeRadius = 10;
		m_SegregatedBrakeAngle = 180;
		m_SegregatedBrakeColorRGB = Vector(1.0, 0.05, 0.025);

		// El ATV no tiene una lente separada de marcha atras: REVERSE_ONLY queda inerte.
		m_SegregatedBrightness = 0;
		m_SegregatedRadius = 0;
		m_SegregatedAngle = 180;
		m_SegregatedColorRGB = Vector(0, 0, 0);

		// BRAKES_AND_REVERSE conserva la proyeccion roja del freno, sin inventar luz blanca.
		m_AggregatedBrightness = 4;
		m_AggregatedRadius = 10;
		m_AggregatedAngle = 180;
		m_AggregatedColorRGB = Vector(1.0, 0.05, 0.025);

		SetVisibleDuringDaylight(false);
		SetCastShadow(false);
		SetFlareVisible(false);
		SegregateLight();
	}
}
