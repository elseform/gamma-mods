/*
	=====================================================================
	Original Author  : vegeta1k95
	Link             : https://www.moddb.com/mods/stalker-anomaly/addons/heatvision-v02-extension-for-beefs-nvg-dx11engine-mod
	=====================================================================
*/

#include "common.h"

#ifdef USE_MSAA
	#ifndef SM_5
        Texture2DMS<float4,MSAA_SAMPLES> s_heat;
	#else
        Texture2DMS<float4> s_heat;
	#endif
#else
    Texture2D   s_heat;
#endif

#define COLOR_COLD_MIN 0.24
#define COLOR_COLD_MAX 0.36
#define COLOR_HOT 0.8
#define COLOR_SKY 0.1
	
float3 normal_blur(float2 pos2d, int samples) 
{
    float3 accum = float3(0.0, 0.0, 0.0); // D3DMetal: explicit ctor, not comma-operator

    for (int i = -samples; i < samples; i++) {        
        for (int j = -samples; j < samples; j++) {
    		accum += gbuf_unpack_normal(s_position.Load(int3(pos2d + float2(i, j), 0), 0).xy);
        }
	}
    
    return normalize(accum);
}

float infrared(gbuffer_data gbd, float2 HPos, float2 Tex0) 
{	
    float3 hotness3 = s_heat.Load(int3(Tex0 * screen_res.xy, 0 ), 0).rgb;
	float hotness = max(hotness3.r, max(hotness3.g, hotness3.b));
    
    float depth = gbd.P.z;
	if (depth <= SKY_EPS)
	{
		return COLOR_SKY;
	}
	
	float hot_color = COLOR_COLD_MAX; // D3DMetal: init to avoid NaN via lerp(...,hot_color,0) on cold pixels
    if (hotness > 0.0)
    {
        int samples = lerp(15, 4, smoothstep(0.0, 60, depth));
        float3 normal = normal_blur(HPos, samples);
        float projection = dot(normal, float3(0.0, 0.0, -1.0));
        
        if (projection <= 0.f) {
            hot_color = COLOR_COLD_MAX;
        } else {        
            hot_color = lerp(COLOR_COLD_MAX, COLOR_HOT, smoothstep(0, 1.0, projection));
        }
	}
	
	float projection = dot(normalize(gbd.N), float3(0.0, 0.0, -1.0));
	float mixed = lerp(COLOR_COLD_MIN, COLOR_COLD_MAX, projection);

    return lerp(mixed, hot_color, hotness);
}