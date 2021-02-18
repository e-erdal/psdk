shaderc.exe -f vs_default.sc -o compiled/vs_default.d3d9.h   --type vertex --varyingdef varying.def.sc --bin2c vs_default_d3d9   --platform windows -p vs_3_0
shaderc.exe -f vs_default.sc -o compiled/vs_default.d3d11.h  --type vertex --varyingdef varying.def.sc --bin2c vs_default_d3d11  --platform windows -p vs_4_0
shaderc.exe -f vs_default.sc -o compiled/vs_default.d3d12.h  --type vertex --varyingdef varying.def.sc --bin2c vs_default_d3d12  --platform windows -p vs_5_0
shaderc.exe -f vs_default.sc -o compiled/vs_default.vulkan.h --type vertex --varyingdef varying.def.sc --bin2c vs_default_vulkan --platform linux   -p spirv
shaderc.exe -f vs_default.sc -o compiled/vs_default.metal.h  --type vertex --varyingdef varying.def.sc --bin2c vs_default_metal  --platform osx     -p metal
shaderc.exe -f vs_default.sc -o compiled/vs_default.glsl.h   --type vertex --varyingdef varying.def.sc --bin2c vs_default_glsl   --platform windows -p 120

pause