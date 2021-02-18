shaderc.exe -f fs_default.sc -o compiled/fs_default.d3d9.h   --type fragment --varyingdef varying.def.sc --bin2c fs_default_d3d9   --platform windows -p ps_3_0  -O 3
shaderc.exe -f fs_default.sc -o compiled/fs_default.d3d11.h  --type fragment --varyingdef varying.def.sc --bin2c fs_default_d3d11  --platform windows -p ps_4_0  -O 3
shaderc.exe -f fs_default.sc -o compiled/fs_default.d3d12.h  --type fragment --varyingdef varying.def.sc --bin2c fs_default_d3d12  --platform windows -p ps_5_0  -O 3
shaderc.exe -f fs_default.sc -o compiled/fs_default.vulkan.h --type fragment --varyingdef varying.def.sc --bin2c fs_default_vulkan --platform linux   -p spirv
shaderc.exe -f fs_default.sc -o compiled/fs_default.metal.h  --type fragment --varyingdef varying.def.sc --bin2c fs_default_metal  --platform osx     -p metal
shaderc.exe -f fs_default.sc -o compiled/fs_default.glsl.h   --type fragment --varyingdef varying.def.sc --bin2c fs_default_glsl   --platform windows -p 120

pause