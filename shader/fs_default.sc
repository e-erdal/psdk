$input v_texcoord0, v_color0, v_batchinfo

#include "../vendor/bgfx.cmake/bgfx/src/bgfx_shader.sh"

SAMPLER2D(u_texture, 0);

void main()
{
	vec4 texColor = v_color0;
	texColor *= texture2D(u_texture, v_texcoord0);
	
	if (texColor.a == 0)
      discard; 
	
	gl_FragColor = texColor;
}
