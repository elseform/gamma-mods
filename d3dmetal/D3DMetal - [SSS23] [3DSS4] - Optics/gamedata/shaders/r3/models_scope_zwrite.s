-- [SHADER FIX] Metal (D3DMetal/DXMT) hardening: alpha blending enabled so the
-- pixel shader can write all bound MRTs with defined results — RT0-2 output
-- alpha=0 preserves the GBuffer, RT3 output alpha=1 writes the scope mask.
-- See models_scope_zwrite.ps for details. Everything else matches 3DSS.
function normal(shader, t_base, t_second, t_detail)
    shader:begin("deffer_model_flat","models_scope_zwrite")
	: zb(false, true)
	: blend(true, blend.srcalpha, blend.invsrcalpha)
	: scopelense(2)
    shader:dx10texture("rt_tempzb", "$user$temp_zb")
    shader:dx10sampler("smp_rtlinear")
    shader:dx10stencil(true, cmp_func.equal, 2, 2, stencil_op.zero, stencil_op.zero, stencil_op.zero)
    shader:dx10stencil_ref(2)
end
