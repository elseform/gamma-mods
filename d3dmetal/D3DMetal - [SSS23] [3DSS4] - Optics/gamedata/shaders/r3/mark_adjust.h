#define MARK_ADJUST 1

uniform float4 markswitch_current;
uniform float4 markswitch_count;

int mark_sides()
{
	// [elseform] Metal loop guard: clamp the constant before looping. D3D
	// defines int(NaN) as 0, but Metal fast-math does not — garbage in
	// markswitch_count could otherwise spin this loop ~46k iterations per
	// pixel before signed overflow exits it. Clamp bounds the loop to <=64
	// iterations (4096 marks is far above any real mark count).
	int count = clamp(int(markswitch_count.x), 1, 4096);
	int sides = 1;
	while (sides * sides < count)
	{
		sides += 1;
	}

	return sides;
}

float2 mark_adjust(float2 pos)
{
	int sides = mark_sides();
	
	float d_x = int(markswitch_current.x) % sides;
	float d_y = int(markswitch_current.x) / sides;
	
	float p_x = clamp(d_x + pos.x, d_x, d_x + 1) / sides;
	float p_y = clamp(d_y + pos.y, d_y, d_y + 1) / sides;
	
	return float2(p_x, p_y);
}
