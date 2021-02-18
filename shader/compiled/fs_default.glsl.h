static const uint8_t fs_default_glsl[294] =
{
	0x46, 0x53, 0x48, 0x08, 0x97, 0x4f, 0x37, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x09, 0x75, // FSH..O7L.......u
	0x5f, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // _texture........
	0x01, 0x01, 0x00, 0x00, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x76, 0x65, 0x63, 0x34, // ....varying vec4
	0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x76, 0x61, 0x72, 0x79, 0x69, //  v_color0;.varyi
	0x6e, 0x67, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, // ng vec2 v_texcoo
	0x72, 0x64, 0x30, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, // rd0;.uniform sam
	0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, 0x75, 0x5f, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, // pler2D u_texture
	0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, // ;.void main ().{
	0x0a, 0x20, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, // .  vec4 texColor
	0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x5f, 0x31, // _1;.  texColor_1
	0x20, 0x3d, 0x20, 0x28, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x20, 0x2a, 0x20, 0x74, //  = (v_color0 * t
	0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x75, 0x5f, 0x74, 0x65, 0x78, 0x74, // exture2D (u_text
	0x75, 0x72, 0x65, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, // ure, v_texcoord0
	0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x28, 0x74, 0x65, 0x78, 0x43, 0x6f, // ));.  if ((texCo
	0x6c, 0x6f, 0x72, 0x5f, 0x31, 0x2e, 0x77, 0x20, 0x3d, 0x3d, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, // lor_1.w == 0.0))
	0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x64, 0x69, 0x73, 0x63, 0x61, 0x72, 0x64, 0x3b, 0x0a, //  {.    discard;.
	0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, //   };.  gl_FragCo
	0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x5f, 0x31, // lor = texColor_1
	0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                                             // ;.}...
};
