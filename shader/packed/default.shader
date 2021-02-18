 5  FSH�O7L     	u_texture0        ����  CTAB   S    ��       �  L   0        <       u_texture ��           ps_3_0 Microsoft (R) HLSL Shader Compiler 10.1 �Q    �  ��   �          
  �  �    � �     � �B    � � �    �  �  �X   �  ��   �  U�A   �   �  ���    �  FSH�O7L     	u_texture0     �  DXBC����֡Qye�-   �     ,   �   �   ISGN�         h                    t                   t                   }                   SV_POSITION TEXCOORD COLOR �OSGN,                               SV_TARGET ��SHDR�   @   4   Z   `     X  p     UU  b �    b �    e  �      h     E  	�      �    F~      `     8  �      F     F           :      @       
     6  �      F     >       �  FSH�O7L     	u_texture0     �  DXBC.xǏͷ����[gy   �     ,   �   �   ISGN�         h                    t                   t                   }                   SV_POSITION TEXCOORD COLOR �OSGN,                               SV_TARGET ��SHEX�   P   7   j Z   `     X  p     UU  b �    b �    e  �      h     E  ��  �CU �      �    F~      `     8  �      F     F           :      @       
     6  �      F     >       &  FSH�O7L     	u_texture        varying vec4 v_color0;
varying vec2 v_texcoord0;
uniform sampler2D u_texture;
void main ()
{
  vec4 texColor_1;
  texColor_1 = (v_color0 * texture2D (u_texture, v_texcoord0));
  if ((texColor_1.w == 0.0)) {
    discard;
  };
  gl_FragColor = texColor_1;
}

  �  FSH�O7L     u_textureSampler��   u_textureTexture��   	u_texture       �  #include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct xlatMtlMain_out
{
    float4 bgfx_FragData0 [[color(0)]];
};

struct xlatMtlMain_in
{
    float4 v_color0 [[user(locn1)]];
    float2 v_texcoord0 [[user(locn2)]];
};

fragment xlatMtlMain_out xlatMtlMain(xlatMtlMain_in in [[stage_in]], texture2d<float> u_texture [[texture(0)]], sampler u_textureSampler [[sampler(0)]])
{
    xlatMtlMain_out out = {};
    float4 _163 = u_texture.sample(u_textureSampler, in.v_texcoord0);
    float4 _140 = in.v_color0 * _163;
    if (_140.w == 0.0)
    {
        discard_fragment();
    }
    out.bgfx_FragData0 = _140;
    return out;
}

     	6  FSH�O7L     u_textureSampler��   u_textureTexture��   	u_texture0 @    �  #   
  �                 GLSL.std.450              	       main    X   \   _   l                �       main      #   u_textureSampler      &   u_textureTexture      X   v_batchinfo   \   v_color0      _   v_texcoord0   l   bgfx_FragData0  G  #   "       G  #   !   P   G  &   "       G  &   !   @   G  X          G  \         G  _         G  l               !                       	                                                      "          ;  "   #          %          ;  %   &         2      +     @         P      W         ;  W   X         [         ;  [   \      ;  W   _         k         ;  k   l      6               �     =     $   #   =     '   &   =     ]   \   =     `   _   V  2   �   '   $   W     �   �   `   �     �   ]   �   Q     �   �      �  P   �   �   @   �  �       �  �   �   �   �  �   �  �  �   >  l   �   �  8        VSH    �O7L u_modelViewProj     �   ����! CTAB   W    ��        P   0         @       u_modelViewProj            vs_3_0 Microsoft (R) HLSL Shader Compiler 10.1 �Q   �  �?              
  �  �     � �    � �   � �     �  �   � �  
  � �    � �    �  �  �   � � U�    �  � �   �  �   �  � �    �  � �   �  � �    �  � �   � �   � D�   �  �    �  �   � �   � �   � ���   ~  VSH    �O7L u_modelViewProj      H  DXBCf��(�͹!�P�r��   H     ,   �   @  ISGN�         h                    n                   w                   w                  COLOR POSITION TEXCOORD OSGN�         h                    t                  t                   }                    SV_POSITION TEXCOORD COLOR �SHDR   @  �   Y  F�         _  �     _  2    _  2    _  2    g  �         e  2     e  �     e  �     h     8  �          F�          8  �     V    F�            �      F     F    8  �     F�         @    �?  �?  �?  �?   �      F     F    8  �     F�         @    �?  �?  �?  �?   �      F     F    6  2     F    6  �         6  �     F     6  �      F     6  2     �
    6  �         6  �     F    >       @ �  VSH    �O7L u_modelViewProj      L  DXBCF�;��+ .`"I�U�   L     ,   �   @  ISGN�         h                    n                   w                   w                  COLOR POSITION TEXCOORD OSGN�         h                    t                  t                   }                    SV_POSITION TEXCOORD COLOR �SHEX  P  �   j� Y  F�         _  �     _  2    _  2    _  2    g  �         e  2     e  �     e  �     h     8  �          F�          8  �     V    F�            �      F     F    8  �     F�         @    �?  �?  �?  �?   �      F     F    8  �     F�         @    �?  �?  �?  �?   �      F     F    6  2     F    6  �         6  �     F     6  �      F     6  2     �
    6  �         6  �     F    >       @ �  VSH    �O7L u_modelViewProj     �  attribute vec4 a_color0;
attribute vec2 a_position;
attribute vec2 a_texcoord0;
attribute vec2 a_texcoord1;
varying vec2 v_batchinfo;
varying vec4 v_color0;
varying vec2 v_texcoord0;
uniform mat4 u_modelViewProj;
void main ()
{
  vec4 tmpvar_1;
  tmpvar_1.zw = vec2(1.0, 1.0);
  tmpvar_1.xy = a_position;
  gl_Position = (u_modelViewProj * tmpvar_1);
  v_texcoord0 = a_texcoord0;
  v_batchinfo = a_texcoord1;
  v_color0 = a_color0;
}

 �  VSH    �O7L u_modelViewProj     �  #include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct _Global
{
    float4x4 u_modelViewProj;
};

struct xlatMtlMain_out
{
    float2 _entryPointOutput_v_batchinfo [[user(locn0)]];
    float4 _entryPointOutput_v_color0 [[user(locn1)]];
    float2 _entryPointOutput_v_texcoord0 [[user(locn2)]];
    float4 gl_Position [[position]];
};

struct xlatMtlMain_in
{
    float4 a_color0 [[attribute(0)]];
    float2 a_position [[attribute(1)]];
    float2 a_texcoord0 [[attribute(2)]];
    float2 a_texcoord1 [[attribute(3)]];
};

vertex xlatMtlMain_out xlatMtlMain(xlatMtlMain_in in [[stage_in]], constant _Global& _mtl_u [[buffer(0)]])
{
    xlatMtlMain_out out = {};
    out.gl_Position = _mtl_u.u_modelViewProj * float4(in.a_position, 1.0, 1.0);
    out._entryPointOutput_v_batchinfo = in.a_texcoord1;
    out._entryPointOutput_v_color0 = in.a_color0;
    out._entryPointOutput_v_texcoord0 = in.a_texcoord0;
    return out;
}

     @ 	b  VSH    �O7L u_modelViewProj     ,  #   
  {                 GLSL.std.450                      main    9   =   @   C   P   T   W   Z        �       main      &   UniformBlock      &       u_modelViewProj   (         9   a_color0      =   a_position    @   a_texcoord0   C   a_texcoord1  
 P   @entryPointOutput.gl_Position    
 T   @entryPointOutput.v_batchinfo    	 W   @entryPointOutput.v_color0   
 Z   @entryPointOutput.v_texcoord0   H  &          H  &       #       H  &             G  &      G  (   "       G  (   !       G  9          G  =         G  @         G  C         G  P          G  T          G  W         G  Z              !                              	                     +          �?+               %           &   %      '      &   ;  '   (         )      %      8         ;  8   9         <      	   ;  <   =      ;  <   @      ;  <   C         O         ;  O   P         S      	   ;  S   T      ;  O   W      ;  S   Z      6               �     =     :   9   =  	   >   =   =  	   A   @   =  	   D   C   Q     u   >       Q     v   >      P     w   u   v         A  )   x   (       =  %   y   x   �     z   w   y   >  P   z   >  T   D   >  W   :   >  Z   A   �  8       @ 