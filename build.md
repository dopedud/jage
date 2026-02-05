[  0%] updating compile_commands.json by copy
[  0%] Building C object src/external/glad/CMakeFiles/glad.dir/src/glad.c.obj
[  0%] Built target glm
[  4%] Built target xxhash
[  4%] Built target zlibstatic
[  8%] Built target glfw
[ 10%] Built target spdlog
[ 10%] Built target update_compile_commands
[ 40%] Built target flecs
[ 92%] Built target assimp
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'get_proc':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:139:18: warning: ISO C forbids conversion of function pointer to object pointer type [-Wpedantic]
  139 |         result = (void*)GetProcAddress((HMODULE) libGL, namez);
      |                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_1_0':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:978:27: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  978 |         glad_glCullFace = (PFNGLCULLFACEPROC)load("glCullFace");
      |                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:979:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  979 |         glad_glFrontFace = (PFNGLFRONTFACEPROC)load("glFrontFace");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:980:23: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  980 |         glad_glHint = (PFNGLHINTPROC)load("glHint");
      |                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:981:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  981 |         glad_glLineWidth = (PFNGLLINEWIDTHPROC)load("glLineWidth");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:982:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  982 |         glad_glPointSize = (PFNGLPOINTSIZEPROC)load("glPointSize");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:983:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  983 |         glad_glPolygonMode = (PFNGLPOLYGONMODEPROC)load("glPolygonMode");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:984:26: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  984 |         glad_glScissor = (PFNGLSCISSORPROC)load("glScissor");
      |                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:985:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  985 |         glad_glTexParameterf = (PFNGLTEXPARAMETERFPROC)load("glTexParameterf");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:986:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  986 |         glad_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)load("glTexParameterfv");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:987:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  987 |         glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC)load("glTexParameteri");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:988:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  988 |         glad_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)load("glTexParameteriv");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:989:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  989 |         glad_glTexImage1D = (PFNGLTEXIMAGE1DPROC)load("glTexImage1D");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:990:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  990 |         glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC)load("glTexImage2D");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:991:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  991 |         glad_glDrawBuffer = (PFNGLDRAWBUFFERPROC)load("glDrawBuffer");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:992:24: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  992 |         glad_glClear = (PFNGLCLEARPROC)load("glClear");
      |                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:993:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  993 |         glad_glClearColor = (PFNGLCLEARCOLORPROC)load("glClearColor");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:994:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  994 |         glad_glClearStencil = (PFNGLCLEARSTENCILPROC)load("glClearStencil");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:995:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  995 |         glad_glClearDepth = (PFNGLCLEARDEPTHPROC)load("glClearDepth");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:996:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  996 |         glad_glStencilMask = (PFNGLSTENCILMASKPROC)load("glStencilMask");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:997:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  997 |         glad_glColorMask = (PFNGLCOLORMASKPROC)load("glColorMask");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:998:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  998 |         glad_glDepthMask = (PFNGLDEPTHMASKPROC)load("glDepthMask");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:999:26: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
  999 |         glad_glDisable = (PFNGLDISABLEPROC)load("glDisable");
      |                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1000:25: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1000 |         glad_glEnable = (PFNGLENABLEPROC)load("glEnable");
      |                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1001:25: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1001 |         glad_glFinish = (PFNGLFINISHPROC)load("glFinish");
      |                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1002:24: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1002 |         glad_glFlush = (PFNGLFLUSHPROC)load("glFlush");
      |                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1003:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1003 |         glad_glBlendFunc = (PFNGLBLENDFUNCPROC)load("glBlendFunc");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1004:26: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1004 |         glad_glLogicOp = (PFNGLLOGICOPPROC)load("glLogicOp");
      |                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1005:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1005 |         glad_glStencilFunc = (PFNGLSTENCILFUNCPROC)load("glStencilFunc");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1006:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1006 |         glad_glStencilOp = (PFNGLSTENCILOPPROC)load("glStencilOp");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1007:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1007 |         glad_glDepthFunc = (PFNGLDEPTHFUNCPROC)load("glDepthFunc");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1008:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1008 |         glad_glPixelStoref = (PFNGLPIXELSTOREFPROC)load("glPixelStoref");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1009:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1009 |         glad_glPixelStorei = (PFNGLPIXELSTOREIPROC)load("glPixelStorei");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1010:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1010 |         glad_glReadBuffer = (PFNGLREADBUFFERPROC)load("glReadBuffer");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1011:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1011 |         glad_glReadPixels = (PFNGLREADPIXELSPROC)load("glReadPixels");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1012:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1012 |         glad_glGetBooleanv = (PFNGLGETBOOLEANVPROC)load("glGetBooleanv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1013:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1013 |         glad_glGetDoublev = (PFNGLGETDOUBLEVPROC)load("glGetDoublev");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1014:27: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1014 |         glad_glGetError = (PFNGLGETERRORPROC)load("glGetError");
      |                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1015:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1015 |         glad_glGetFloatv = (PFNGLGETFLOATVPROC)load("glGetFloatv");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1016:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1016 |         glad_glGetIntegerv = (PFNGLGETINTEGERVPROC)load("glGetIntegerv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1017:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1017 |         glad_glGetString = (PFNGLGETSTRINGPROC)load("glGetString");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1018:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1018 |         glad_glGetTexImage = (PFNGLGETTEXIMAGEPROC)load("glGetTexImage");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1019:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1019 |         glad_glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)load("glGetTexParameterfv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1020:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1020 |         glad_glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)load("glGetTexParameteriv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1021:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1021 |         glad_glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)load("glGetTexLevelParameterfv");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1022:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1022 |         glad_glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)load("glGetTexLevelParameteriv");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1023:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1023 |         glad_glIsEnabled = (PFNGLISENABLEDPROC)load("glIsEnabled");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1024:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1024 |         glad_glDepthRange = (PFNGLDEPTHRANGEPROC)load("glDepthRange");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1025:27: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1025 |         glad_glViewport = (PFNGLVIEWPORTPROC)load("glViewport");
      |                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_1_1':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1029:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1029 |         glad_glDrawArrays = (PFNGLDRAWARRAYSPROC)load("glDrawArrays");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1030:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1030 |         glad_glDrawElements = (PFNGLDRAWELEMENTSPROC)load("glDrawElements");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1031:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1031 |         glad_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)load("glPolygonOffset");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1032:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1032 |         glad_glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)load("glCopyTexImage1D");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1033:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1033 |         glad_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)load("glCopyTexImage2D");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1034:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1034 |         glad_glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)load("glCopyTexSubImage1D");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1035:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1035 |         glad_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)load("glCopyTexSubImage2D");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1036:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1036 |         glad_glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)load("glTexSubImage1D");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1037:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1037 |         glad_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)load("glTexSubImage2D");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1038:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1038 |         glad_glBindTexture = (PFNGLBINDTEXTUREPROC)load("glBindTexture");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1039:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1039 |         glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC)load("glDeleteTextures");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1040:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1040 |         glad_glGenTextures = (PFNGLGENTEXTURESPROC)load("glGenTextures");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1041:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1041 |         glad_glIsTexture = (PFNGLISTEXTUREPROC)load("glIsTexture");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_1_2':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1045:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1045 |         glad_glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)load("glDrawRangeElements");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1046:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1046 |         glad_glTexImage3D = (PFNGLTEXIMAGE3DPROC)load("glTexImage3D");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1047:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1047 |         glad_glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)load("glTexSubImage3D");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1048:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1048 |         glad_glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)load("glCopyTexSubImage3D");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_1_3':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1052:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1052 |         glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC)load("glActiveTexture");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1053:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1053 |         glad_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)load("glSampleCoverage");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1054:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1054 |         glad_glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)load("glCompressedTexImage3D");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1055:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1055 |         glad_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)load("glCompressedTexImage2D");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1056:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1056 |         glad_glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)load("glCompressedTexImage1D");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1057:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1057 |         glad_glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)load("glCompressedTexSubImage3D");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1058:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1058 |         glad_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)load("glCompressedTexSubImage2D");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1059:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1059 |         glad_glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)load("glCompressedTexSubImage1D");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1060:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1060 |         glad_glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)load("glGetCompressedTexImage");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_1_4':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1064:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1064 |         glad_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)load("glBlendFuncSeparate");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1065:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1065 |         glad_glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)load("glMultiDrawArrays");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1066:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1066 |         glad_glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)load("glMultiDrawElements");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1067:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1067 |         glad_glPointParameterf = (PFNGLPOINTPARAMETERFPROC)load("glPointParameterf");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1068:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1068 |         glad_glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)load("glPointParameterfv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1069:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1069 |         glad_glPointParameteri = (PFNGLPOINTPARAMETERIPROC)load("glPointParameteri");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1070:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1070 |         glad_glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)load("glPointParameteriv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1071:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1071 |         glad_glBlendColor = (PFNGLBLENDCOLORPROC)load("glBlendColor");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1072:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1072 |         glad_glBlendEquation = (PFNGLBLENDEQUATIONPROC)load("glBlendEquation");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_1_5':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1076:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1076 |         glad_glGenQueries = (PFNGLGENQUERIESPROC)load("glGenQueries");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1077:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1077 |         glad_glDeleteQueries = (PFNGLDELETEQUERIESPROC)load("glDeleteQueries");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1078:26: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1078 |         glad_glIsQuery = (PFNGLISQUERYPROC)load("glIsQuery");
      |                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1079:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1079 |         glad_glBeginQuery = (PFNGLBEGINQUERYPROC)load("glBeginQuery");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1080:27: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1080 |         glad_glEndQuery = (PFNGLENDQUERYPROC)load("glEndQuery");
      |                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1081:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1081 |         glad_glGetQueryiv = (PFNGLGETQUERYIVPROC)load("glGetQueryiv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1082:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1082 |         glad_glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)load("glGetQueryObjectiv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1083:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1083 |         glad_glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)load("glGetQueryObjectuiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1084:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1084 |         glad_glBindBuffer = (PFNGLBINDBUFFERPROC)load("glBindBuffer");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1085:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1085 |         glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)load("glDeleteBuffers");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1086:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1086 |         glad_glGenBuffers = (PFNGLGENBUFFERSPROC)load("glGenBuffers");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1087:27: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1087 |         glad_glIsBuffer = (PFNGLISBUFFERPROC)load("glIsBuffer");
      |                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1088:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1088 |         glad_glBufferData = (PFNGLBUFFERDATAPROC)load("glBufferData");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1089:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1089 |         glad_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)load("glBufferSubData");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1090:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1090 |         glad_glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)load("glGetBufferSubData");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1091:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1091 |         glad_glMapBuffer = (PFNGLMAPBUFFERPROC)load("glMapBuffer");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1092:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1092 |         glad_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)load("glUnmapBuffer");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1093:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1093 |         glad_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)load("glGetBufferParameteriv");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1094:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1094 |         glad_glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)load("glGetBufferPointerv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_2_0':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1098:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1098 |         glad_glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)load("glBlendEquationSeparate");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1099:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1099 |         glad_glDrawBuffers = (PFNGLDRAWBUFFERSPROC)load("glDrawBuffers");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1100:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1100 |         glad_glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)load("glStencilOpSeparate");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1101:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1101 |         glad_glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)load("glStencilFuncSeparate");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1102:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1102 |         glad_glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)load("glStencilMaskSeparate");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1103:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1103 |         glad_glAttachShader = (PFNGLATTACHSHADERPROC)load("glAttachShader");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1104:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1104 |         glad_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)load("glBindAttribLocation");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1105:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1105 |         glad_glCompileShader = (PFNGLCOMPILESHADERPROC)load("glCompileShader");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1106:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1106 |         glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)load("glCreateProgram");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1107:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1107 |         glad_glCreateShader = (PFNGLCREATESHADERPROC)load("glCreateShader");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1108:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1108 |         glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)load("glDeleteProgram");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1109:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1109 |         glad_glDeleteShader = (PFNGLDELETESHADERPROC)load("glDeleteShader");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1110:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1110 |         glad_glDetachShader = (PFNGLDETACHSHADERPROC)load("glDetachShader");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1111:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1111 |         glad_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)load("glDisableVertexAttribArray");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1112:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1112 |         glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load("glEnableVertexAttribArray");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1113:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1113 |         glad_glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)load("glGetActiveAttrib");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1114:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1114 |         glad_glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)load("glGetActiveUniform");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1115:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1115 |         glad_glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)load("glGetAttachedShaders");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1116:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1116 |         glad_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)load("glGetAttribLocation");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1117:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1117 |         glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)load("glGetProgramiv");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1118:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1118 |         glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)load("glGetProgramInfoLog");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1119:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1119 |         glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)load("glGetShaderiv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1120:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1120 |         glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load("glGetShaderInfoLog");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1121:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1121 |         glad_glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)load("glGetShaderSource");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1122:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1122 |         glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)load("glGetUniformLocation");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1123:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1123 |         glad_glGetUniformfv = (PFNGLGETUNIFORMFVPROC)load("glGetUniformfv");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1124:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1124 |         glad_glGetUniformiv = (PFNGLGETUNIFORMIVPROC)load("glGetUniformiv");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1125:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1125 |         glad_glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)load("glGetVertexAttribdv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1126:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1126 |         glad_glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)load("glGetVertexAttribfv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1127:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1127 |         glad_glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)load("glGetVertexAttribiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1128:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1128 |         glad_glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)load("glGetVertexAttribPointerv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1129:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1129 |         glad_glIsProgram = (PFNGLISPROGRAMPROC)load("glIsProgram");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1130:27: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1130 |         glad_glIsShader = (PFNGLISSHADERPROC)load("glIsShader");
      |                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1131:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1131 |         glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)load("glLinkProgram");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1132:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1132 |         glad_glShaderSource = (PFNGLSHADERSOURCEPROC)load("glShaderSource");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1133:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1133 |         glad_glUseProgram = (PFNGLUSEPROGRAMPROC)load("glUseProgram");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1134:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1134 |         glad_glUniform1f = (PFNGLUNIFORM1FPROC)load("glUniform1f");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1135:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1135 |         glad_glUniform2f = (PFNGLUNIFORM2FPROC)load("glUniform2f");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1136:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1136 |         glad_glUniform3f = (PFNGLUNIFORM3FPROC)load("glUniform3f");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1137:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1137 |         glad_glUniform4f = (PFNGLUNIFORM4FPROC)load("glUniform4f");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1138:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1138 |         glad_glUniform1i = (PFNGLUNIFORM1IPROC)load("glUniform1i");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1139:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1139 |         glad_glUniform2i = (PFNGLUNIFORM2IPROC)load("glUniform2i");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1140:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1140 |         glad_glUniform3i = (PFNGLUNIFORM3IPROC)load("glUniform3i");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1141:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1141 |         glad_glUniform4i = (PFNGLUNIFORM4IPROC)load("glUniform4i");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1142:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1142 |         glad_glUniform1fv = (PFNGLUNIFORM1FVPROC)load("glUniform1fv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1143:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1143 |         glad_glUniform2fv = (PFNGLUNIFORM2FVPROC)load("glUniform2fv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1144:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1144 |         glad_glUniform3fv = (PFNGLUNIFORM3FVPROC)load("glUniform3fv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1145:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1145 |         glad_glUniform4fv = (PFNGLUNIFORM4FVPROC)load("glUniform4fv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1146:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1146 |         glad_glUniform1iv = (PFNGLUNIFORM1IVPROC)load("glUniform1iv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1147:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1147 |         glad_glUniform2iv = (PFNGLUNIFORM2IVPROC)load("glUniform2iv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1148:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1148 |         glad_glUniform3iv = (PFNGLUNIFORM3IVPROC)load("glUniform3iv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1149:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1149 |         glad_glUniform4iv = (PFNGLUNIFORM4IVPROC)load("glUniform4iv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1150:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1150 |         glad_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)load("glUniformMatrix2fv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1151:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1151 |         glad_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)load("glUniformMatrix3fv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1152:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1152 |         glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)load("glUniformMatrix4fv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1153:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1153 |         glad_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)load("glValidateProgram");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1154:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1154 |         glad_glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)load("glVertexAttrib1d");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1155:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1155 |         glad_glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)load("glVertexAttrib1dv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1156:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1156 |         glad_glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)load("glVertexAttrib1f");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1157:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1157 |         glad_glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)load("glVertexAttrib1fv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1158:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1158 |         glad_glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)load("glVertexAttrib1s");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1159:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1159 |         glad_glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)load("glVertexAttrib1sv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1160:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1160 |         glad_glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)load("glVertexAttrib2d");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1161:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1161 |         glad_glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)load("glVertexAttrib2dv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1162:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1162 |         glad_glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)load("glVertexAttrib2f");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1163:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1163 |         glad_glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)load("glVertexAttrib2fv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1164:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1164 |         glad_glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)load("glVertexAttrib2s");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1165:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1165 |         glad_glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)load("glVertexAttrib2sv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1166:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1166 |         glad_glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)load("glVertexAttrib3d");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1167:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1167 |         glad_glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)load("glVertexAttrib3dv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1168:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1168 |         glad_glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)load("glVertexAttrib3f");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1169:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1169 |         glad_glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)load("glVertexAttrib3fv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1170:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1170 |         glad_glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)load("glVertexAttrib3s");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1171:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1171 |         glad_glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)load("glVertexAttrib3sv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1172:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1172 |         glad_glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)load("glVertexAttrib4Nbv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1173:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1173 |         glad_glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)load("glVertexAttrib4Niv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1174:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1174 |         glad_glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)load("glVertexAttrib4Nsv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1175:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1175 |         glad_glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)load("glVertexAttrib4Nub");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1176:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1176 |         glad_glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)load("glVertexAttrib4Nubv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1177:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1177 |         glad_glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)load("glVertexAttrib4Nuiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1178:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1178 |         glad_glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)load("glVertexAttrib4Nusv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1179:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1179 |         glad_glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)load("glVertexAttrib4bv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1180:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1180 |         glad_glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)load("glVertexAttrib4d");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1181:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1181 |         glad_glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)load("glVertexAttrib4dv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1182:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1182 |         glad_glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)load("glVertexAttrib4f");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1183:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1183 |         glad_glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)load("glVertexAttrib4fv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1184:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1184 |         glad_glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)load("glVertexAttrib4iv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1185:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1185 |         glad_glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)load("glVertexAttrib4s");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1186:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1186 |         glad_glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)load("glVertexAttrib4sv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1187:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1187 |         glad_glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)load("glVertexAttrib4ubv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1188:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1188 |         glad_glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)load("glVertexAttrib4uiv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1189:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1189 |         glad_glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)load("glVertexAttrib4usv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1190:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1190 |         glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)load("glVertexAttribPointer");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_2_1':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1194:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1194 |         glad_glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)load("glUniformMatrix2x3fv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1195:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1195 |         glad_glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)load("glUniformMatrix3x2fv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1196:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1196 |         glad_glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)load("glUniformMatrix2x4fv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1197:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1197 |         glad_glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)load("glUniformMatrix4x2fv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1198:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1198 |         glad_glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)load("glUniformMatrix3x4fv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1199:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1199 |         glad_glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)load("glUniformMatrix4x3fv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_3_0':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1203:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1203 |         glad_glColorMaski = (PFNGLCOLORMASKIPROC)load("glColorMaski");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1204:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1204 |         glad_glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)load("glGetBooleani_v");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1205:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1205 |         glad_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)load("glGetIntegeri_v");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1206:26: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1206 |         glad_glEnablei = (PFNGLENABLEIPROC)load("glEnablei");
      |                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1207:27: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1207 |         glad_glDisablei = (PFNGLDISABLEIPROC)load("glDisablei");
      |                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1208:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1208 |         glad_glIsEnabledi = (PFNGLISENABLEDIPROC)load("glIsEnabledi");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1209:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1209 |         glad_glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)load("glBeginTransformFeedback");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1210:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1210 |         glad_glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)load("glEndTransformFeedback");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1211:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1211 |         glad_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)load("glBindBufferRange");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1212:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1212 |         glad_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)load("glBindBufferBase");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1213:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1213 |         glad_glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)load("glTransformFeedbackVaryings");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1214:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1214 |         glad_glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)load("glGetTransformFeedbackVarying");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1215:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1215 |         glad_glClampColor = (PFNGLCLAMPCOLORPROC)load("glClampColor");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1216:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1216 |         glad_glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)load("glBeginConditionalRender");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1217:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1217 |         glad_glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)load("glEndConditionalRender");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1218:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1218 |         glad_glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)load("glVertexAttribIPointer");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1219:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1219 |         glad_glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)load("glGetVertexAttribIiv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1220:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1220 |         glad_glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)load("glGetVertexAttribIuiv");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1221:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1221 |         glad_glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)load("glVertexAttribI1i");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1222:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1222 |         glad_glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)load("glVertexAttribI2i");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1223:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1223 |         glad_glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)load("glVertexAttribI3i");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1224:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1224 |         glad_glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)load("glVertexAttribI4i");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1225:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1225 |         glad_glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)load("glVertexAttribI1ui");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1226:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1226 |         glad_glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)load("glVertexAttribI2ui");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1227:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1227 |         glad_glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)load("glVertexAttribI3ui");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1228:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1228 |         glad_glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)load("glVertexAttribI4ui");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1229:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1229 |         glad_glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)load("glVertexAttribI1iv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1230:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1230 |         glad_glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)load("glVertexAttribI2iv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1231:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1231 |         glad_glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)load("glVertexAttribI3iv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1232:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1232 |         glad_glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)load("glVertexAttribI4iv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1233:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1233 |         glad_glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)load("glVertexAttribI1uiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1234:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1234 |         glad_glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)load("glVertexAttribI2uiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1235:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1235 |         glad_glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)load("glVertexAttribI3uiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1236:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1236 |         glad_glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)load("glVertexAttribI4uiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1237:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1237 |         glad_glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)load("glVertexAttribI4bv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1238:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1238 |         glad_glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)load("glVertexAttribI4sv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1239:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1239 |         glad_glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)load("glVertexAttribI4ubv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1240:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1240 |         glad_glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)load("glVertexAttribI4usv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1241:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1241 |         glad_glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)load("glGetUniformuiv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1242:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1242 |         glad_glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)load("glBindFragDataLocation");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1243:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1243 |         glad_glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)load("glGetFragDataLocation");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1244:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1244 |         glad_glUniform1ui = (PFNGLUNIFORM1UIPROC)load("glUniform1ui");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1245:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1245 |         glad_glUniform2ui = (PFNGLUNIFORM2UIPROC)load("glUniform2ui");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1246:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1246 |         glad_glUniform3ui = (PFNGLUNIFORM3UIPROC)load("glUniform3ui");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1247:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1247 |         glad_glUniform4ui = (PFNGLUNIFORM4UIPROC)load("glUniform4ui");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1248:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1248 |         glad_glUniform1uiv = (PFNGLUNIFORM1UIVPROC)load("glUniform1uiv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1249:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1249 |         glad_glUniform2uiv = (PFNGLUNIFORM2UIVPROC)load("glUniform2uiv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1250:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1250 |         glad_glUniform3uiv = (PFNGLUNIFORM3UIVPROC)load("glUniform3uiv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1251:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1251 |         glad_glUniform4uiv = (PFNGLUNIFORM4UIVPROC)load("glUniform4uiv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1252:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1252 |         glad_glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)load("glTexParameterIiv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1253:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1253 |         glad_glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)load("glTexParameterIuiv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1254:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1254 |         glad_glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)load("glGetTexParameterIiv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1255:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1255 |         glad_glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)load("glGetTexParameterIuiv");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1256:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1256 |         glad_glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)load("glClearBufferiv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1257:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1257 |         glad_glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)load("glClearBufferuiv");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1258:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1258 |         glad_glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)load("glClearBufferfv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1259:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1259 |         glad_glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)load("glClearBufferfi");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1260:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1260 |         glad_glGetStringi = (PFNGLGETSTRINGIPROC)load("glGetStringi");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1261:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1261 |         glad_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)load("glIsRenderbuffer");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1262:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1262 |         glad_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)load("glBindRenderbuffer");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1263:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1263 |         glad_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)load("glDeleteRenderbuffers");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1264:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1264 |         glad_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)load("glGenRenderbuffers");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1265:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1265 |         glad_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)load("glRenderbufferStorage");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1266:45: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1266 |         glad_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)load("glGetRenderbufferParameteriv");
      |                                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1267:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1267 |         glad_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)load("glIsFramebuffer");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1268:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1268 |         glad_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)load("glBindFramebuffer");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1269:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1269 |         glad_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)load("glDeleteFramebuffers");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1270:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1270 |         glad_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)load("glGenFramebuffers");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1271:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1271 |         glad_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)load("glCheckFramebufferStatus");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1272:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1272 |         glad_glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)load("glFramebufferTexture1D");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1273:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1273 |         glad_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)load("glFramebufferTexture2D");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1274:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1274 |         glad_glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)load("glFramebufferTexture3D");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1275:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1275 |         glad_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)load("glFramebufferRenderbuffer");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1276:54: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1276 |         glad_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)load("glGetFramebufferAttachmentParameteriv");
      |                                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1277:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1277 |         glad_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)load("glGenerateMipmap");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1278:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1278 |         glad_glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)load("glBlitFramebuffer");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1279:49: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1279 |         glad_glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)load("glRenderbufferStorageMultisample");
      |                                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1280:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1280 |         glad_glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)load("glFramebufferTextureLayer");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1281:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1281 |         glad_glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)load("glMapBufferRange");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1282:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1282 |         glad_glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)load("glFlushMappedBufferRange");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1283:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1283 |         glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load("glBindVertexArray");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1284:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1284 |         glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)load("glDeleteVertexArrays");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1285:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1285 |         glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)load("glGenVertexArrays");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1286:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1286 |         glad_glIsVertexArray = (PFNGLISVERTEXARRAYPROC)load("glIsVertexArray");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_3_1':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1290:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1290 |         glad_glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)load("glDrawArraysInstanced");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1291:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1291 |         glad_glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)load("glDrawElementsInstanced");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1292:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1292 |         glad_glTexBuffer = (PFNGLTEXBUFFERPROC)load("glTexBuffer");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1293:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1293 |         glad_glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)load("glPrimitiveRestartIndex");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1294:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1294 |         glad_glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)load("glCopyBufferSubData");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1295:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1295 |         glad_glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)load("glGetUniformIndices");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1296:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1296 |         glad_glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)load("glGetActiveUniformsiv");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1297:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1297 |         glad_glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)load("glGetActiveUniformName");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1298:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1298 |         glad_glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)load("glGetUniformBlockIndex");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1299:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1299 |         glad_glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)load("glGetActiveUniformBlockiv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1300:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1300 |         glad_glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)load("glGetActiveUniformBlockName");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1301:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1301 |         glad_glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)load("glUniformBlockBinding");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1302:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1302 |         glad_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)load("glBindBufferRange");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1303:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1303 |         glad_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)load("glBindBufferBase");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1304:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1304 |         glad_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)load("glGetIntegeri_v");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_3_2':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1308:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1308 |         glad_glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)load("glDrawElementsBaseVertex");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1309:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1309 |         glad_glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)load("glDrawRangeElementsBaseVertex");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1310:50: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1310 |         glad_glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)load("glDrawElementsInstancedBaseVertex");
      |                                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1311:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1311 |         glad_glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)load("glMultiDrawElementsBaseVertex");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1312:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1312 |         glad_glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)load("glProvokingVertex");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1313:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1313 |         glad_glFenceSync = (PFNGLFENCESYNCPROC)load("glFenceSync");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1314:25: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1314 |         glad_glIsSync = (PFNGLISSYNCPROC)load("glIsSync");
      |                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1315:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1315 |         glad_glDeleteSync = (PFNGLDELETESYNCPROC)load("glDeleteSync");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1316:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1316 |         glad_glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)load("glClientWaitSync");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1317:27: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1317 |         glad_glWaitSync = (PFNGLWAITSYNCPROC)load("glWaitSync");
      |                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1318:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1318 |         glad_glGetInteger64v = (PFNGLGETINTEGER64VPROC)load("glGetInteger64v");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1319:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1319 |         glad_glGetSynciv = (PFNGLGETSYNCIVPROC)load("glGetSynciv");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1320:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1320 |         glad_glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)load("glGetInteger64i_v");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1321:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1321 |         glad_glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)load("glGetBufferParameteri64v");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1322:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1322 |         glad_glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)load("glFramebufferTexture");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1323:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1323 |         glad_glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)load("glTexImage2DMultisample");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1324:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1324 |         glad_glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)load("glTexImage3DMultisample");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1325:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1325 |         glad_glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)load("glGetMultisamplefv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1326:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1326 |         glad_glSampleMaski = (PFNGLSAMPLEMASKIPROC)load("glSampleMaski");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_3_3':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1330:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1330 |         glad_glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)load("glBindFragDataLocationIndexed");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1331:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1331 |         glad_glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)load("glGetFragDataIndex");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1332:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1332 |         glad_glGenSamplers = (PFNGLGENSAMPLERSPROC)load("glGenSamplers");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1333:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1333 |         glad_glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)load("glDeleteSamplers");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1334:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1334 |         glad_glIsSampler = (PFNGLISSAMPLERPROC)load("glIsSampler");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1335:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1335 |         glad_glBindSampler = (PFNGLBINDSAMPLERPROC)load("glBindSampler");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1336:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1336 |         glad_glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)load("glSamplerParameteri");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1337:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1337 |         glad_glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)load("glSamplerParameteriv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1338:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1338 |         glad_glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)load("glSamplerParameterf");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1339:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1339 |         glad_glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)load("glSamplerParameterfv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1340:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1340 |         glad_glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)load("glSamplerParameterIiv");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1341:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1341 |         glad_glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)load("glSamplerParameterIuiv");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1342:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1342 |         glad_glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)load("glGetSamplerParameteriv");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1343:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1343 |         glad_glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)load("glGetSamplerParameterIiv");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1344:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1344 |         glad_glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)load("glGetSamplerParameterfv");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1345:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1345 |         glad_glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)load("glGetSamplerParameterIuiv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1346:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1346 |         glad_glQueryCounter = (PFNGLQUERYCOUNTERPROC)load("glQueryCounter");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1347:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1347 |         glad_glGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)load("glGetQueryObjecti64v");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1348:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1348 |         glad_glGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)load("glGetQueryObjectui64v");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1349:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1349 |         glad_glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)load("glVertexAttribDivisor");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1350:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1350 |         glad_glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)load("glVertexAttribP1ui");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1351:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1351 |         glad_glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)load("glVertexAttribP1uiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1352:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1352 |         glad_glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)load("glVertexAttribP2ui");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1353:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1353 |         glad_glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)load("glVertexAttribP2uiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1354:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1354 |         glad_glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)load("glVertexAttribP3ui");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1355:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1355 |         glad_glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)load("glVertexAttribP3uiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1356:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1356 |         glad_glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)load("glVertexAttribP4ui");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1357:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1357 |         glad_glVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)load("glVertexAttribP4uiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1358:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1358 |         glad_glVertexP2ui = (PFNGLVERTEXP2UIPROC)load("glVertexP2ui");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1359:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1359 |         glad_glVertexP2uiv = (PFNGLVERTEXP2UIVPROC)load("glVertexP2uiv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1360:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1360 |         glad_glVertexP3ui = (PFNGLVERTEXP3UIPROC)load("glVertexP3ui");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1361:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1361 |         glad_glVertexP3uiv = (PFNGLVERTEXP3UIVPROC)load("glVertexP3uiv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1362:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1362 |         glad_glVertexP4ui = (PFNGLVERTEXP4UIPROC)load("glVertexP4ui");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1363:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1363 |         glad_glVertexP4uiv = (PFNGLVERTEXP4UIVPROC)load("glVertexP4uiv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1364:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1364 |         glad_glTexCoordP1ui = (PFNGLTEXCOORDP1UIPROC)load("glTexCoordP1ui");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1365:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1365 |         glad_glTexCoordP1uiv = (PFNGLTEXCOORDP1UIVPROC)load("glTexCoordP1uiv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1366:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1366 |         glad_glTexCoordP2ui = (PFNGLTEXCOORDP2UIPROC)load("glTexCoordP2ui");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1367:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1367 |         glad_glTexCoordP2uiv = (PFNGLTEXCOORDP2UIVPROC)load("glTexCoordP2uiv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1368:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1368 |         glad_glTexCoordP3ui = (PFNGLTEXCOORDP3UIPROC)load("glTexCoordP3ui");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1369:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1369 |         glad_glTexCoordP3uiv = (PFNGLTEXCOORDP3UIVPROC)load("glTexCoordP3uiv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1370:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1370 |         glad_glTexCoordP4ui = (PFNGLTEXCOORDP4UIPROC)load("glTexCoordP4ui");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1371:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1371 |         glad_glTexCoordP4uiv = (PFNGLTEXCOORDP4UIVPROC)load("glTexCoordP4uiv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1372:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1372 |         glad_glMultiTexCoordP1ui = (PFNGLMULTITEXCOORDP1UIPROC)load("glMultiTexCoordP1ui");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1373:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1373 |         glad_glMultiTexCoordP1uiv = (PFNGLMULTITEXCOORDP1UIVPROC)load("glMultiTexCoordP1uiv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1374:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1374 |         glad_glMultiTexCoordP2ui = (PFNGLMULTITEXCOORDP2UIPROC)load("glMultiTexCoordP2ui");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1375:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1375 |         glad_glMultiTexCoordP2uiv = (PFNGLMULTITEXCOORDP2UIVPROC)load("glMultiTexCoordP2uiv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1376:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1376 |         glad_glMultiTexCoordP3ui = (PFNGLMULTITEXCOORDP3UIPROC)load("glMultiTexCoordP3ui");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1377:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1377 |         glad_glMultiTexCoordP3uiv = (PFNGLMULTITEXCOORDP3UIVPROC)load("glMultiTexCoordP3uiv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1378:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1378 |         glad_glMultiTexCoordP4ui = (PFNGLMULTITEXCOORDP4UIPROC)load("glMultiTexCoordP4ui");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1379:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1379 |         glad_glMultiTexCoordP4uiv = (PFNGLMULTITEXCOORDP4UIVPROC)load("glMultiTexCoordP4uiv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1380:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1380 |         glad_glNormalP3ui = (PFNGLNORMALP3UIPROC)load("glNormalP3ui");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1381:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1381 |         glad_glNormalP3uiv = (PFNGLNORMALP3UIVPROC)load("glNormalP3uiv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1382:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1382 |         glad_glColorP3ui = (PFNGLCOLORP3UIPROC)load("glColorP3ui");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1383:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1383 |         glad_glColorP3uiv = (PFNGLCOLORP3UIVPROC)load("glColorP3uiv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1384:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1384 |         glad_glColorP4ui = (PFNGLCOLORP4UIPROC)load("glColorP4ui");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1385:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1385 |         glad_glColorP4uiv = (PFNGLCOLORP4UIVPROC)load("glColorP4uiv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1386:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1386 |         glad_glSecondaryColorP3ui = (PFNGLSECONDARYCOLORP3UIPROC)load("glSecondaryColorP3ui");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1387:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1387 |         glad_glSecondaryColorP3uiv = (PFNGLSECONDARYCOLORP3UIVPROC)load("glSecondaryColorP3uiv");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_4_0':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1391:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1391 |         glad_glMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)load("glMinSampleShading");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1392:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1392 |         glad_glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)load("glBlendEquationi");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1393:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1393 |         glad_glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)load("glBlendEquationSeparatei");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1394:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1394 |         glad_glBlendFunci = (PFNGLBLENDFUNCIPROC)load("glBlendFunci");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1395:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1395 |         glad_glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)load("glBlendFuncSeparatei");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1396:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1396 |         glad_glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)load("glDrawArraysIndirect");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1397:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1397 |         glad_glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)load("glDrawElementsIndirect");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1398:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1398 |         glad_glUniform1d = (PFNGLUNIFORM1DPROC)load("glUniform1d");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1399:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1399 |         glad_glUniform2d = (PFNGLUNIFORM2DPROC)load("glUniform2d");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1400:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1400 |         glad_glUniform3d = (PFNGLUNIFORM3DPROC)load("glUniform3d");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1401:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1401 |         glad_glUniform4d = (PFNGLUNIFORM4DPROC)load("glUniform4d");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1402:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1402 |         glad_glUniform1dv = (PFNGLUNIFORM1DVPROC)load("glUniform1dv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1403:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1403 |         glad_glUniform2dv = (PFNGLUNIFORM2DVPROC)load("glUniform2dv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1404:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1404 |         glad_glUniform3dv = (PFNGLUNIFORM3DVPROC)load("glUniform3dv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1405:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1405 |         glad_glUniform4dv = (PFNGLUNIFORM4DVPROC)load("glUniform4dv");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1406:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1406 |         glad_glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)load("glUniformMatrix2dv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1407:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1407 |         glad_glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)load("glUniformMatrix3dv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1408:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1408 |         glad_glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)load("glUniformMatrix4dv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1409:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1409 |         glad_glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)load("glUniformMatrix2x3dv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1410:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1410 |         glad_glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)load("glUniformMatrix2x4dv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1411:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1411 |         glad_glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)load("glUniformMatrix3x2dv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1412:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1412 |         glad_glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)load("glUniformMatrix3x4dv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1413:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1413 |         glad_glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)load("glUniformMatrix4x2dv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1414:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1414 |         glad_glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)load("glUniformMatrix4x3dv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1415:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1415 |         glad_glGetUniformdv = (PFNGLGETUNIFORMDVPROC)load("glGetUniformdv");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1416:47: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1416 |         glad_glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)load("glGetSubroutineUniformLocation");
      |                                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1417:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1417 |         glad_glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)load("glGetSubroutineIndex");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1418:47: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1418 |         glad_glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)load("glGetActiveSubroutineUniformiv");
      |                                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1419:49: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1419 |         glad_glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)load("glGetActiveSubroutineUniformName");
      |                                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1420:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1420 |         glad_glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)load("glGetActiveSubroutineName");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1421:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1421 |         glad_glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)load("glUniformSubroutinesuiv");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1422:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1422 |         glad_glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)load("glGetUniformSubroutineuiv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1423:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1423 |         glad_glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)load("glGetProgramStageiv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1424:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1424 |         glad_glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)load("glPatchParameteri");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1425:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1425 |         glad_glPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)load("glPatchParameterfv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1426:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1426 |         glad_glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)load("glBindTransformFeedback");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1427:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1427 |         glad_glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)load("glDeleteTransformFeedbacks");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1428:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1428 |         glad_glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)load("glGenTransformFeedbacks");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1429:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1429 |         glad_glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)load("glIsTransformFeedback");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1430:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1430 |         glad_glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)load("glPauseTransformFeedback");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1431:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1431 |         glad_glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)load("glResumeTransformFeedback");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1432:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1432 |         glad_glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)load("glDrawTransformFeedback");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1433:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1433 |         glad_glDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)load("glDrawTransformFeedbackStream");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1434:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1434 |         glad_glBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)load("glBeginQueryIndexed");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1435:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1435 |         glad_glEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)load("glEndQueryIndexed");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1436:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1436 |         glad_glGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)load("glGetQueryIndexediv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_4_1':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1440:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1440 |         glad_glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)load("glReleaseShaderCompiler");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1441:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1441 |         glad_glShaderBinary = (PFNGLSHADERBINARYPROC)load("glShaderBinary");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1442:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1442 |         glad_glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)load("glGetShaderPrecisionFormat");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1443:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1443 |         glad_glDepthRangef = (PFNGLDEPTHRANGEFPROC)load("glDepthRangef");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1444:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1444 |         glad_glClearDepthf = (PFNGLCLEARDEPTHFPROC)load("glClearDepthf");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1445:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1445 |         glad_glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)load("glGetProgramBinary");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1446:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1446 |         glad_glProgramBinary = (PFNGLPROGRAMBINARYPROC)load("glProgramBinary");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1447:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1447 |         glad_glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)load("glProgramParameteri");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1448:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1448 |         glad_glUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC)load("glUseProgramStages");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1449:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1449 |         glad_glActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC)load("glActiveShaderProgram");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1450:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1450 |         glad_glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)load("glCreateShaderProgramv");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1451:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1451 |         glad_glBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC)load("glBindProgramPipeline");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1452:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1452 |         glad_glDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)load("glDeleteProgramPipelines");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1453:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1453 |         glad_glGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC)load("glGenProgramPipelines");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1454:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1454 |         glad_glIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC)load("glIsProgramPipeline");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1455:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1455 |         glad_glGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)load("glGetProgramPipelineiv");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1456:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1456 |         glad_glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)load("glProgramParameteri");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1457:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1457 |         glad_glProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)load("glProgramUniform1i");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1458:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1458 |         glad_glProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)load("glProgramUniform1iv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1459:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1459 |         glad_glProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC)load("glProgramUniform1f");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1460:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1460 |         glad_glProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)load("glProgramUniform1fv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1461:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1461 |         glad_glProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC)load("glProgramUniform1d");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1462:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1462 |         glad_glProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)load("glProgramUniform1dv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1463:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1463 |         glad_glProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)load("glProgramUniform1ui");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1464:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1464 |         glad_glProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)load("glProgramUniform1uiv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1465:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1465 |         glad_glProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC)load("glProgramUniform2i");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1466:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1466 |         glad_glProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)load("glProgramUniform2iv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1467:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1467 |         glad_glProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC)load("glProgramUniform2f");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1468:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1468 |         glad_glProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)load("glProgramUniform2fv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1469:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1469 |         glad_glProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC)load("glProgramUniform2d");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1470:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1470 |         glad_glProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)load("glProgramUniform2dv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1471:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1471 |         glad_glProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)load("glProgramUniform2ui");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1472:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1472 |         glad_glProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)load("glProgramUniform2uiv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1473:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1473 |         glad_glProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC)load("glProgramUniform3i");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1474:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1474 |         glad_glProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)load("glProgramUniform3iv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1475:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1475 |         glad_glProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC)load("glProgramUniform3f");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1476:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1476 |         glad_glProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)load("glProgramUniform3fv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1477:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1477 |         glad_glProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC)load("glProgramUniform3d");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1478:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1478 |         glad_glProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)load("glProgramUniform3dv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1479:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1479 |         glad_glProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)load("glProgramUniform3ui");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1480:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1480 |         glad_glProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)load("glProgramUniform3uiv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1481:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1481 |         glad_glProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)load("glProgramUniform4i");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1482:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1482 |         glad_glProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)load("glProgramUniform4iv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1483:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1483 |         glad_glProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)load("glProgramUniform4f");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1484:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1484 |         glad_glProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)load("glProgramUniform4fv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1485:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1485 |         glad_glProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC)load("glProgramUniform4d");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1486:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1486 |         glad_glProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)load("glProgramUniform4dv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1487:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1487 |         glad_glProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)load("glProgramUniform4ui");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1488:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1488 |         glad_glProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)load("glProgramUniform4uiv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1489:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1489 |         glad_glProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)load("glProgramUniformMatrix2fv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1490:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1490 |         glad_glProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)load("glProgramUniformMatrix3fv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1491:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1491 |         glad_glProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)load("glProgramUniformMatrix4fv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1492:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1492 |         glad_glProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)load("glProgramUniformMatrix2dv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1493:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1493 |         glad_glProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)load("glProgramUniformMatrix3dv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1494:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1494 |         glad_glProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)load("glProgramUniformMatrix4dv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1495:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1495 |         glad_glProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)load("glProgramUniformMatrix2x3fv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1496:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1496 |         glad_glProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)load("glProgramUniformMatrix3x2fv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1497:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1497 |         glad_glProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)load("glProgramUniformMatrix2x4fv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1498:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1498 |         glad_glProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)load("glProgramUniformMatrix4x2fv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1499:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1499 |         glad_glProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)load("glProgramUniformMatrix3x4fv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1500:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1500 |         glad_glProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)load("glProgramUniformMatrix4x3fv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1501:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1501 |         glad_glProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)load("glProgramUniformMatrix2x3dv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1502:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1502 |         glad_glProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)load("glProgramUniformMatrix3x2dv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1503:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1503 |         glad_glProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)load("glProgramUniformMatrix2x4dv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1504:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1504 |         glad_glProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)load("glProgramUniformMatrix4x2dv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1505:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1505 |         glad_glProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)load("glProgramUniformMatrix3x4dv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1506:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1506 |         glad_glProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)load("glProgramUniformMatrix4x3dv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1507:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1507 |         glad_glValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)load("glValidateProgramPipeline");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1508:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1508 |         glad_glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)load("glGetProgramPipelineInfoLog");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1509:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1509 |         glad_glVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC)load("glVertexAttribL1d");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1510:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1510 |         glad_glVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC)load("glVertexAttribL2d");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1511:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1511 |         glad_glVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC)load("glVertexAttribL3d");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1512:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1512 |         glad_glVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC)load("glVertexAttribL4d");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1513:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1513 |         glad_glVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC)load("glVertexAttribL1dv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1514:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1514 |         glad_glVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC)load("glVertexAttribL2dv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1515:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1515 |         glad_glVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC)load("glVertexAttribL3dv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1516:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1516 |         glad_glVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC)load("glVertexAttribL4dv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1517:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1517 |         glad_glVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)load("glVertexAttribLPointer");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1518:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1518 |         glad_glGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC)load("glGetVertexAttribLdv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1519:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1519 |         glad_glViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)load("glViewportArrayv");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1520:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1520 |         glad_glViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)load("glViewportIndexedf");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1521:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1521 |         glad_glViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)load("glViewportIndexedfv");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1522:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1522 |         glad_glScissorArrayv = (PFNGLSCISSORARRAYVPROC)load("glScissorArrayv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1523:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1523 |         glad_glScissorIndexed = (PFNGLSCISSORINDEXEDPROC)load("glScissorIndexed");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1524:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1524 |         glad_glScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)load("glScissorIndexedv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1525:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1525 |         glad_glDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)load("glDepthRangeArrayv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1526:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1526 |         glad_glDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)load("glDepthRangeIndexed");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1527:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1527 |         glad_glGetFloati_v = (PFNGLGETFLOATI_VPROC)load("glGetFloati_v");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1528:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1528 |         glad_glGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)load("glGetDoublei_v");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_4_2':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1532:50: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1532 |         glad_glDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)load("glDrawArraysInstancedBaseInstance");
      |                                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1533:52: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1533 |         glad_glDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)load("glDrawElementsInstancedBaseInstance");
      |                                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1534:62: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1534 |         glad_glDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)load("glDrawElementsInstancedBaseVertexBaseInstance");
      |                                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1535:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1535 |         glad_glGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC)load("glGetInternalformativ");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1536:49: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1536 |         glad_glGetActiveAtomicCounterBufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)load("glGetActiveAtomicCounterBufferiv");
      |                                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1537:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1537 |         glad_glBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC)load("glBindImageTexture");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1538:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1538 |         glad_glMemoryBarrier = (PFNGLMEMORYBARRIERPROC)load("glMemoryBarrier");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1539:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1539 |         glad_glTexStorage1D = (PFNGLTEXSTORAGE1DPROC)load("glTexStorage1D");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1540:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1540 |         glad_glTexStorage2D = (PFNGLTEXSTORAGE2DPROC)load("glTexStorage2D");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1541:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1541 |         glad_glTexStorage3D = (PFNGLTEXSTORAGE3DPROC)load("glTexStorage3D");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1542:49: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1542 |         glad_glDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)load("glDrawTransformFeedbackInstanced");
      |                                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1543:55: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1543 |         glad_glDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)load("glDrawTransformFeedbackStreamInstanced");
      |                                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_4_3':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1547:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1547 |         glad_glClearBufferData = (PFNGLCLEARBUFFERDATAPROC)load("glClearBufferData");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1548:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1548 |         glad_glClearBufferSubData = (PFNGLCLEARBUFFERSUBDATAPROC)load("glClearBufferSubData");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1549:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1549 |         glad_glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)load("glDispatchCompute");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1550:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1550 |         glad_glDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)load("glDispatchComputeIndirect");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1551:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1551 |         glad_glCopyImageSubData = (PFNGLCOPYIMAGESUBDATAPROC)load("glCopyImageSubData");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1552:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1552 |         glad_glFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC)load("glFramebufferParameteri");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1553:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1553 |         glad_glGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC)load("glGetFramebufferParameteriv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1554:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1554 |         glad_glGetInternalformati64v = (PFNGLGETINTERNALFORMATI64VPROC)load("glGetInternalformati64v");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1555:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1555 |         glad_glInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC)load("glInvalidateTexSubImage");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1556:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1556 |         glad_glInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC)load("glInvalidateTexImage");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1557:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1557 |         glad_glInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC)load("glInvalidateBufferSubData");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1558:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1558 |         glad_glInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC)load("glInvalidateBufferData");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1559:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1559 |         glad_glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)load("glInvalidateFramebuffer");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1560:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1560 |         glad_glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)load("glInvalidateSubFramebuffer");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1561:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1561 |         glad_glMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)load("glMultiDrawArraysIndirect");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1562:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1562 |         glad_glMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)load("glMultiDrawElementsIndirect");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1563:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1563 |         glad_glGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC)load("glGetProgramInterfaceiv");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1564:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1564 |         glad_glGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC)load("glGetProgramResourceIndex");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1565:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1565 |         glad_glGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC)load("glGetProgramResourceName");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1566:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1566 |         glad_glGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC)load("glGetProgramResourceiv");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1567:45: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1567 |         glad_glGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC)load("glGetProgramResourceLocation");
      |                                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1568:50: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1568 |         glad_glGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)load("glGetProgramResourceLocationIndex");
      |                                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1569:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1569 |         glad_glShaderStorageBlockBinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC)load("glShaderStorageBlockBinding");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1570:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1570 |         glad_glTexBufferRange = (PFNGLTEXBUFFERRANGEPROC)load("glTexBufferRange");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1571:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1571 |         glad_glTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)load("glTexStorage2DMultisample");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1572:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1572 |         glad_glTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC)load("glTexStorage3DMultisample");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1573:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1573 |         glad_glTextureView = (PFNGLTEXTUREVIEWPROC)load("glTextureView");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1574:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1574 |         glad_glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)load("glBindVertexBuffer");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1575:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1575 |         glad_glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)load("glVertexAttribFormat");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1576:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1576 |         glad_glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC)load("glVertexAttribIFormat");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1577:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1577 |         glad_glVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC)load("glVertexAttribLFormat");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1578:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1578 |         glad_glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)load("glVertexAttribBinding");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1579:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1579 |         glad_glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC)load("glVertexBindingDivisor");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1580:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1580 |         glad_glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)load("glDebugMessageControl");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1581:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1581 |         glad_glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)load("glDebugMessageInsert");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1582:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1582 |         glad_glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)load("glDebugMessageCallback");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1583:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1583 |         glad_glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)load("glGetDebugMessageLog");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1584:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1584 |         glad_glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)load("glPushDebugGroup");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1585:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1585 |         glad_glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)load("glPopDebugGroup");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1586:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1586 |         glad_glObjectLabel = (PFNGLOBJECTLABELPROC)load("glObjectLabel");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1587:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1587 |         glad_glGetObjectLabel = (PFNGLGETOBJECTLABELPROC)load("glGetObjectLabel");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1588:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1588 |         glad_glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)load("glObjectPtrLabel");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1589:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1589 |         glad_glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)load("glGetObjectPtrLabel");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1590:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1590 |         glad_glGetPointerv = (PFNGLGETPOINTERVPROC)load("glGetPointerv");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_4_4':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1594:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1594 |         glad_glBufferStorage = (PFNGLBUFFERSTORAGEPROC)load("glBufferStorage");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1595:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1595 |         glad_glClearTexImage = (PFNGLCLEARTEXIMAGEPROC)load("glClearTexImage");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1596:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1596 |         glad_glClearTexSubImage = (PFNGLCLEARTEXSUBIMAGEPROC)load("glClearTexSubImage");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1597:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1597 |         glad_glBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC)load("glBindBuffersBase");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1598:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1598 |         glad_glBindBuffersRange = (PFNGLBINDBUFFERSRANGEPROC)load("glBindBuffersRange");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1599:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1599 |         glad_glBindTextures = (PFNGLBINDTEXTURESPROC)load("glBindTextures");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1600:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1600 |         glad_glBindSamplers = (PFNGLBINDSAMPLERSPROC)load("glBindSamplers");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1601:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1601 |         glad_glBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC)load("glBindImageTextures");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1602:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1602 |         glad_glBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC)load("glBindVertexBuffers");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_4_5':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1606:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1606 |         glad_glClipControl = (PFNGLCLIPCONTROLPROC)load("glClipControl");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1607:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1607 |         glad_glCreateTransformFeedbacks = (PFNGLCREATETRANSFORMFEEDBACKSPROC)load("glCreateTransformFeedbacks");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1608:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1608 |         glad_glTransformFeedbackBufferBase = (PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)load("glTransformFeedbackBufferBase");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1609:47: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1609 |         glad_glTransformFeedbackBufferRange = (PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)load("glTransformFeedbackBufferRange");
      |                                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1610:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1610 |         glad_glGetTransformFeedbackiv = (PFNGLGETTRANSFORMFEEDBACKIVPROC)load("glGetTransformFeedbackiv");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1611:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1611 |         glad_glGetTransformFeedbacki_v = (PFNGLGETTRANSFORMFEEDBACKI_VPROC)load("glGetTransformFeedbacki_v");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1612:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1612 |         glad_glGetTransformFeedbacki64_v = (PFNGLGETTRANSFORMFEEDBACKI64_VPROC)load("glGetTransformFeedbacki64_v");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1613:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1613 |         glad_glCreateBuffers = (PFNGLCREATEBUFFERSPROC)load("glCreateBuffers");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1614:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1614 |         glad_glNamedBufferStorage = (PFNGLNAMEDBUFFERSTORAGEPROC)load("glNamedBufferStorage");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1615:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1615 |         glad_glNamedBufferData = (PFNGLNAMEDBUFFERDATAPROC)load("glNamedBufferData");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1616:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1616 |         glad_glNamedBufferSubData = (PFNGLNAMEDBUFFERSUBDATAPROC)load("glNamedBufferSubData");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1617:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1617 |         glad_glCopyNamedBufferSubData = (PFNGLCOPYNAMEDBUFFERSUBDATAPROC)load("glCopyNamedBufferSubData");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1618:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1618 |         glad_glClearNamedBufferData = (PFNGLCLEARNAMEDBUFFERDATAPROC)load("glClearNamedBufferData");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1619:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1619 |         glad_glClearNamedBufferSubData = (PFNGLCLEARNAMEDBUFFERSUBDATAPROC)load("glClearNamedBufferSubData");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1620:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1620 |         glad_glMapNamedBuffer = (PFNGLMAPNAMEDBUFFERPROC)load("glMapNamedBuffer");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1621:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1621 |         glad_glMapNamedBufferRange = (PFNGLMAPNAMEDBUFFERRANGEPROC)load("glMapNamedBufferRange");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1622:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1622 |         glad_glUnmapNamedBuffer = (PFNGLUNMAPNAMEDBUFFERPROC)load("glUnmapNamedBuffer");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1623:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1623 |         glad_glFlushMappedNamedBufferRange = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)load("glFlushMappedNamedBufferRange");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1624:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1624 |         glad_glGetNamedBufferParameteriv = (PFNGLGETNAMEDBUFFERPARAMETERIVPROC)load("glGetNamedBufferParameteriv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1625:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1625 |         glad_glGetNamedBufferParameteri64v = (PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)load("glGetNamedBufferParameteri64v");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1626:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1626 |         glad_glGetNamedBufferPointerv = (PFNGLGETNAMEDBUFFERPOINTERVPROC)load("glGetNamedBufferPointerv");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1627:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1627 |         glad_glGetNamedBufferSubData = (PFNGLGETNAMEDBUFFERSUBDATAPROC)load("glGetNamedBufferSubData");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1628:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1628 |         glad_glCreateFramebuffers = (PFNGLCREATEFRAMEBUFFERSPROC)load("glCreateFramebuffers");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1629:47: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1629 |         glad_glNamedFramebufferRenderbuffer = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)load("glNamedFramebufferRenderbuffer");
      |                                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1630:45: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1630 |         glad_glNamedFramebufferParameteri = (PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)load("glNamedFramebufferParameteri");
      |                                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1631:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1631 |         glad_glNamedFramebufferTexture = (PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)load("glNamedFramebufferTexture");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1632:47: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1632 |         glad_glNamedFramebufferTextureLayer = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)load("glNamedFramebufferTextureLayer");
      |                                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1633:45: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1633 |         glad_glNamedFramebufferDrawBuffer = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)load("glNamedFramebufferDrawBuffer");
      |                                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1634:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1634 |         glad_glNamedFramebufferDrawBuffers = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)load("glNamedFramebufferDrawBuffers");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1635:45: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1635 |         glad_glNamedFramebufferReadBuffer = (PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)load("glNamedFramebufferReadBuffer");
      |                                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1636:49: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1636 |         glad_glInvalidateNamedFramebufferData = (PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)load("glInvalidateNamedFramebufferData");
      |                                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1637:52: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1637 |         glad_glInvalidateNamedFramebufferSubData = (PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)load("glInvalidateNamedFramebufferSubData");
      |                                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1638:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1638 |         glad_glClearNamedFramebufferiv = (PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)load("glClearNamedFramebufferiv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1639:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1639 |         glad_glClearNamedFramebufferuiv = (PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)load("glClearNamedFramebufferuiv");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1640:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1640 |         glad_glClearNamedFramebufferfv = (PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)load("glClearNamedFramebufferfv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1641:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1641 |         glad_glClearNamedFramebufferfi = (PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)load("glClearNamedFramebufferfi");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1642:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1642 |         glad_glBlitNamedFramebuffer = (PFNGLBLITNAMEDFRAMEBUFFERPROC)load("glBlitNamedFramebuffer");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1643:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1643 |         glad_glCheckNamedFramebufferStatus = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)load("glCheckNamedFramebufferStatus");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1644:49: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1644 |         glad_glGetNamedFramebufferParameteriv = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)load("glGetNamedFramebufferParameteriv");
      |                                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1645:59: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1645 |         glad_glGetNamedFramebufferAttachmentParameteriv = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)load("glGetNamedFramebufferAttachmentParameteriv");
      |                                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1646:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1646 |         glad_glCreateRenderbuffers = (PFNGLCREATERENDERBUFFERSPROC)load("glCreateRenderbuffers");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1647:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1647 |         glad_glNamedRenderbufferStorage = (PFNGLNAMEDRENDERBUFFERSTORAGEPROC)load("glNamedRenderbufferStorage");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1648:54: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1648 |         glad_glNamedRenderbufferStorageMultisample = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)load("glNamedRenderbufferStorageMultisample");
      |                                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1649:50: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1649 |         glad_glGetNamedRenderbufferParameteriv = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)load("glGetNamedRenderbufferParameteriv");
      |                                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1650:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1650 |         glad_glCreateTextures = (PFNGLCREATETEXTURESPROC)load("glCreateTextures");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1651:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1651 |         glad_glTextureBuffer = (PFNGLTEXTUREBUFFERPROC)load("glTextureBuffer");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1652:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1652 |         glad_glTextureBufferRange = (PFNGLTEXTUREBUFFERRANGEPROC)load("glTextureBufferRange");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1653:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1653 |         glad_glTextureStorage1D = (PFNGLTEXTURESTORAGE1DPROC)load("glTextureStorage1D");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1654:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1654 |         glad_glTextureStorage2D = (PFNGLTEXTURESTORAGE2DPROC)load("glTextureStorage2D");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1655:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1655 |         glad_glTextureStorage3D = (PFNGLTEXTURESTORAGE3DPROC)load("glTextureStorage3D");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1656:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1656 |         glad_glTextureStorage2DMultisample = (PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)load("glTextureStorage2DMultisample");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1657:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1657 |         glad_glTextureStorage3DMultisample = (PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)load("glTextureStorage3DMultisample");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1658:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1658 |         glad_glTextureSubImage1D = (PFNGLTEXTURESUBIMAGE1DPROC)load("glTextureSubImage1D");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1659:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1659 |         glad_glTextureSubImage2D = (PFNGLTEXTURESUBIMAGE2DPROC)load("glTextureSubImage2D");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1660:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1660 |         glad_glTextureSubImage3D = (PFNGLTEXTURESUBIMAGE3DPROC)load("glTextureSubImage3D");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1661:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1661 |         glad_glCompressedTextureSubImage1D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)load("glCompressedTextureSubImage1D");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1662:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1662 |         glad_glCompressedTextureSubImage2D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)load("glCompressedTextureSubImage2D");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1663:46: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1663 |         glad_glCompressedTextureSubImage3D = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)load("glCompressedTextureSubImage3D");
      |                                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1664:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1664 |         glad_glCopyTextureSubImage1D = (PFNGLCOPYTEXTURESUBIMAGE1DPROC)load("glCopyTextureSubImage1D");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1665:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1665 |         glad_glCopyTextureSubImage2D = (PFNGLCOPYTEXTURESUBIMAGE2DPROC)load("glCopyTextureSubImage2D");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1666:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1666 |         glad_glCopyTextureSubImage3D = (PFNGLCOPYTEXTURESUBIMAGE3DPROC)load("glCopyTextureSubImage3D");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1667:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1667 |         glad_glTextureParameterf = (PFNGLTEXTUREPARAMETERFPROC)load("glTextureParameterf");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1668:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1668 |         glad_glTextureParameterfv = (PFNGLTEXTUREPARAMETERFVPROC)load("glTextureParameterfv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1669:36: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1669 |         glad_glTextureParameteri = (PFNGLTEXTUREPARAMETERIPROC)load("glTextureParameteri");
      |                                    ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1670:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1670 |         glad_glTextureParameterIiv = (PFNGLTEXTUREPARAMETERIIVPROC)load("glTextureParameterIiv");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1671:39: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1671 |         glad_glTextureParameterIuiv = (PFNGLTEXTUREPARAMETERIUIVPROC)load("glTextureParameterIuiv");
      |                                       ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1672:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1672 |         glad_glTextureParameteriv = (PFNGLTEXTUREPARAMETERIVPROC)load("glTextureParameteriv");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1673:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1673 |         glad_glGenerateTextureMipmap = (PFNGLGENERATETEXTUREMIPMAPPROC)load("glGenerateTextureMipmap");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1674:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1674 |         glad_glBindTextureUnit = (PFNGLBINDTEXTUREUNITPROC)load("glBindTextureUnit");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1675:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1675 |         glad_glGetTextureImage = (PFNGLGETTEXTUREIMAGEPROC)load("glGetTextureImage");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1676:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1676 |         glad_glGetCompressedTextureImage = (PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)load("glGetCompressedTextureImage");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1677:45: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1677 |         glad_glGetTextureLevelParameterfv = (PFNGLGETTEXTURELEVELPARAMETERFVPROC)load("glGetTextureLevelParameterfv");
      |                                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1678:45: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1678 |         glad_glGetTextureLevelParameteriv = (PFNGLGETTEXTURELEVELPARAMETERIVPROC)load("glGetTextureLevelParameteriv");
      |                                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1679:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1679 |         glad_glGetTextureParameterfv = (PFNGLGETTEXTUREPARAMETERFVPROC)load("glGetTextureParameterfv");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1680:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1680 |         glad_glGetTextureParameterIiv = (PFNGLGETTEXTUREPARAMETERIIVPROC)load("glGetTextureParameterIiv");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1681:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1681 |         glad_glGetTextureParameterIuiv = (PFNGLGETTEXTUREPARAMETERIUIVPROC)load("glGetTextureParameterIuiv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1682:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1682 |         glad_glGetTextureParameteriv = (PFNGLGETTEXTUREPARAMETERIVPROC)load("glGetTextureParameteriv");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1683:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1683 |         glad_glCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC)load("glCreateVertexArrays");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1684:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1684 |         glad_glDisableVertexArrayAttrib = (PFNGLDISABLEVERTEXARRAYATTRIBPROC)load("glDisableVertexArrayAttrib");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1685:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1685 |         glad_glEnableVertexArrayAttrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC)load("glEnableVertexArrayAttrib");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1686:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1686 |         glad_glVertexArrayElementBuffer = (PFNGLVERTEXARRAYELEMENTBUFFERPROC)load("glVertexArrayElementBuffer");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1687:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1687 |         glad_glVertexArrayVertexBuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC)load("glVertexArrayVertexBuffer");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1688:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1688 |         glad_glVertexArrayVertexBuffers = (PFNGLVERTEXARRAYVERTEXBUFFERSPROC)load("glVertexArrayVertexBuffers");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1689:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1689 |         glad_glVertexArrayAttribBinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC)load("glVertexArrayAttribBinding");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1690:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1690 |         glad_glVertexArrayAttribFormat = (PFNGLVERTEXARRAYATTRIBFORMATPROC)load("glVertexArrayAttribFormat");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1691:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1691 |         glad_glVertexArrayAttribIFormat = (PFNGLVERTEXARRAYATTRIBIFORMATPROC)load("glVertexArrayAttribIFormat");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1692:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1692 |         glad_glVertexArrayAttribLFormat = (PFNGLVERTEXARRAYATTRIBLFORMATPROC)load("glVertexArrayAttribLFormat");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1693:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1693 |         glad_glVertexArrayBindingDivisor = (PFNGLVERTEXARRAYBINDINGDIVISORPROC)load("glVertexArrayBindingDivisor");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1694:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1694 |         glad_glGetVertexArrayiv = (PFNGLGETVERTEXARRAYIVPROC)load("glGetVertexArrayiv");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1695:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1695 |         glad_glGetVertexArrayIndexediv = (PFNGLGETVERTEXARRAYINDEXEDIVPROC)load("glGetVertexArrayIndexediv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1696:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1696 |         glad_glGetVertexArrayIndexed64iv = (PFNGLGETVERTEXARRAYINDEXED64IVPROC)load("glGetVertexArrayIndexed64iv");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1697:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1697 |         glad_glCreateSamplers = (PFNGLCREATESAMPLERSPROC)load("glCreateSamplers");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1698:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1698 |         glad_glCreateProgramPipelines = (PFNGLCREATEPROGRAMPIPELINESPROC)load("glCreateProgramPipelines");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1699:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1699 |         glad_glCreateQueries = (PFNGLCREATEQUERIESPROC)load("glCreateQueries");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1700:43: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1700 |         glad_glGetQueryBufferObjecti64v = (PFNGLGETQUERYBUFFEROBJECTI64VPROC)load("glGetQueryBufferObjecti64v");
      |                                           ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1701:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1701 |         glad_glGetQueryBufferObjectiv = (PFNGLGETQUERYBUFFEROBJECTIVPROC)load("glGetQueryBufferObjectiv");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1702:44: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1702 |         glad_glGetQueryBufferObjectui64v = (PFNGLGETQUERYBUFFEROBJECTUI64VPROC)load("glGetQueryBufferObjectui64v");
      |                                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1703:42: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1703 |         glad_glGetQueryBufferObjectuiv = (PFNGLGETQUERYBUFFEROBJECTUIVPROC)load("glGetQueryBufferObjectuiv");
      |                                          ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1704:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1704 |         glad_glMemoryBarrierByRegion = (PFNGLMEMORYBARRIERBYREGIONPROC)load("glMemoryBarrierByRegion");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1705:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1705 |         glad_glGetTextureSubImage = (PFNGLGETTEXTURESUBIMAGEPROC)load("glGetTextureSubImage");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1706:47: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1706 |         glad_glGetCompressedTextureSubImage = (PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)load("glGetCompressedTextureSubImage");
      |                                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1707:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1707 |         glad_glGetGraphicsResetStatus = (PFNGLGETGRAPHICSRESETSTATUSPROC)load("glGetGraphicsResetStatus");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1708:41: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1708 |         glad_glGetnCompressedTexImage = (PFNGLGETNCOMPRESSEDTEXIMAGEPROC)load("glGetnCompressedTexImage");
      |                                         ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1709:31: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1709 |         glad_glGetnTexImage = (PFNGLGETNTEXIMAGEPROC)load("glGetnTexImage");
      |                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1710:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1710 |         glad_glGetnUniformdv = (PFNGLGETNUNIFORMDVPROC)load("glGetnUniformdv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1711:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1711 |         glad_glGetnUniformfv = (PFNGLGETNUNIFORMFVPROC)load("glGetnUniformfv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1712:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1712 |         glad_glGetnUniformiv = (PFNGLGETNUNIFORMIVPROC)load("glGetnUniformiv");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1713:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1713 |         glad_glGetnUniformuiv = (PFNGLGETNUNIFORMUIVPROC)load("glGetnUniformuiv");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1714:30: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1714 |         glad_glReadnPixels = (PFNGLREADNPIXELSPROC)load("glReadnPixels");
      |                              ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1715:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1715 |         glad_glGetnMapdv = (PFNGLGETNMAPDVPROC)load("glGetnMapdv");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1716:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1716 |         glad_glGetnMapfv = (PFNGLGETNMAPFVPROC)load("glGetnMapfv");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1717:28: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1717 |         glad_glGetnMapiv = (PFNGLGETNMAPIVPROC)load("glGetnMapiv");
      |                            ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1718:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1718 |         glad_glGetnPixelMapfv = (PFNGLGETNPIXELMAPFVPROC)load("glGetnPixelMapfv");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1719:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1719 |         glad_glGetnPixelMapuiv = (PFNGLGETNPIXELMAPUIVPROC)load("glGetnPixelMapuiv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1720:34: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1720 |         glad_glGetnPixelMapusv = (PFNGLGETNPIXELMAPUSVPROC)load("glGetnPixelMapusv");
      |                                  ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1721:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1721 |         glad_glGetnPolygonStipple = (PFNGLGETNPOLYGONSTIPPLEPROC)load("glGetnPolygonStipple");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1722:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1722 |         glad_glGetnColorTable = (PFNGLGETNCOLORTABLEPROC)load("glGetnColorTable");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1723:40: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1723 |         glad_glGetnConvolutionFilter = (PFNGLGETNCONVOLUTIONFILTERPROC)load("glGetnConvolutionFilter");
      |                                        ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1724:38: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1724 |         glad_glGetnSeparableFilter = (PFNGLGETNSEPARABLEFILTERPROC)load("glGetnSeparableFilter");
      |                                      ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1725:32: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1725 |         glad_glGetnHistogram = (PFNGLGETNHISTOGRAMPROC)load("glGetnHistogram");
      |                                ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1726:29: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1726 |         glad_glGetnMinmax = (PFNGLGETNMINMAXPROC)load("glGetnMinmax");
      |                             ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1727:33: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1727 |         glad_glTextureBarrier = (PFNGLTEXTUREBARRIERPROC)load("glTextureBarrier");
      |                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'load_GL_VERSION_4_6':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1731:35: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1731 |         glad_glSpecializeShader = (PFNGLSPECIALIZESHADERPROC)load("glSpecializeShader");
      |                                   ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1732:47: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1732 |         glad_glMultiDrawArraysIndirectCount = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)load("glMultiDrawArraysIndirectCount");
      |                                               ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1733:49: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1733 |         glad_glMultiDrawElementsIndirectCount = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)load("glMultiDrawElementsIndirectCount");
      |                                                 ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1734:37: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1734 |         glad_glPolygonOffsetClamp = (PFNGLPOLYGONOFFSETCLAMPPROC)load("glPolygonOffsetClamp");
      |                                     ^
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c: In function 'gladLoadGLLoader':
C:\Users\theab\Desktop\jage\src\external\glad\src\glad.c:1806:23: warning: ISO C forbids conversion of object pointer to function pointer type [-Wpedantic]
 1806 |         glGetString = (PFNGLGETSTRINGPROC)load("glGetString");
      |                       ^
[ 92%] Linking C static library ..\..\..\build\lib\glad.a
[ 92%] Built target glad
[ 94%] Built target dear_imgui
[ 94%] Building CXX object src/CMakeFiles/JAGE.dir/cmake_pch.hxx.gch
[ 94%] Building CXX object src/CMakeFiles/JAGE.dir/jgpch.cxx.obj
[ 94%] Building CXX object src/CMakeFiles/JAGE.dir/init.cxx.obj
[ 94%] Building CXX object src/CMakeFiles/JAGE.dir/log.cxx.obj
[ 95%] Building CXX object src/CMakeFiles/JAGE.dir/event.cxx.obj
[ 95%] Building CXX object src/CMakeFiles/JAGE.dir/input.cxx.obj
[ 95%] Building CXX object src/CMakeFiles/JAGE.dir/timing.cxx.obj
[ 95%] Building CXX object src/CMakeFiles/JAGE.dir/window.cxx.obj
[ 96%] Building CXX object src/CMakeFiles/JAGE.dir/renderer.cxx.obj
[ 96%] Building CXX object src/CMakeFiles/JAGE.dir/resources.cxx.obj
C:\Users\theab\Desktop\jage\src\init.cxx: In function 'void JAGE::Init(int, char**)':
C:\Users\theab\Desktop\jage\src\init.cxx:11:19: warning: unused parameter 'argc' [-Wunused-parameter]
   11 |     void Init(int argc, char** argv)
      |               ~~~~^~~~
[ 96%] Building CXX object src/CMakeFiles/JAGE.dir/ecs.cxx.obj
[ 96%] Building CXX object src/CMakeFiles/JAGE.dir/math.cxx.obj
[ 96%] Building CXX object src/CMakeFiles/JAGE.dir/game_layer.cxx.obj
C:\Users\theab\Desktop\jage\src\resources.cxx: In function 'JAGE::ImageData JAGE::process_embedded_texture(const aiTexture*, const aiScene*)':
C:\Users\theab\Desktop\jage\src\resources.cxx:352:91: warning: unused parameter 'ai_scene' [-Wunused-parameter]
  352 |     static ImageData process_embedded_texture(const aiTexture* ai_texture, const aiScene* ai_scene)
      |                                                                            ~~~~~~~~~~~~~~~^~~~~~~~
C:\Users\theab\Desktop\jage\src\resources.cxx: In function 'JAGE::MeshData JAGE::process_mesh(const aiMesh*, const aiScene*)':
C:\Users\theab\Desktop\jage\src\resources.cxx:408:72: warning: unused parameter 'ai_scene' [-Wunused-parameter]
  408 |     static MeshData process_mesh(const aiMesh* ai_mesh, const aiScene* ai_scene)
      |                                                         ~~~~~~~~~~~~~~~^~~~~~~~
[ 97%] Building CXX object src/CMakeFiles/JAGE.dir/platform/glfw/input.cxx.obj
[ 97%] Building CXX object src/CMakeFiles/JAGE.dir/platform/glfw/opengl3/window.cxx.obj
[ 97%] Building CXX object src/CMakeFiles/JAGE.dir/platform/glfw/opengl3/renderer.cxx.obj
C:\Users\theab\Desktop\jage\src\ecs.cxx: In function 'void JAGE::TransformSystem(ecs_iter_t*)':
C:\Users\theab\Desktop\jage\src\ecs.cxx:196:31: warning: comparison of integer expressions of different signedness: 'unsigned int' and 'int32_t' {aka 'int'} [-Wsign-compare]
  196 |         for (unsigned i {}; i < it->count; i++)
      |                             ~~^~~~~~~~~~~
C:\Users\theab\Desktop\jage\src\ecs.cxx: In function 'void JAGE::MeshRenderSystem(ecs_iter_t*)':
C:\Users\theab\Desktop\jage\src\ecs.cxx:297:31: warning: comparison of integer expressions of different signedness: 'unsigned int' and 'int32_t' {aka 'int'} [-Wsign-compare]
  297 |         for (unsigned i {}; i < it->count; i++)
      |                             ~~^~~~~~~~~~~
[ 97%] Building CXX object src/CMakeFiles/JAGE.dir/platform/glfw/opengl3/imgui_layer.cxx.obj
C:\Users\theab\Desktop\jage\src\platform\glfw\opengl3\renderer.cxx: In lambda function:
C:\Users\theab\Desktop\jage\src\platform\glfw\opengl3\renderer.cxx:53:24: warning: unused parameter 'window' [-Wunused-parameter]
   53 |         [](GLFWwindow* window, int width, int height) -> void
      |            ~~~~~~~~~~~~^~~~~~
C:\Users\theab\Desktop\jage\src\platform\glfw\opengl3\renderer.cxx: In member function 'virtual void JAGE::OpenGLDebugRenderer::RenderGridLines(unsigned int, float)':
C:\Users\theab\Desktop\jage\src\platform\glfw\opengl3\renderer.cxx:416:25: warning: unused variable 'm_major' [-Wunused-variable]
  416 |         static unsigned m_major {};
      |                         ^~~~~~~
[ 98%] Linking CXX shared library ..\build\bin\JAGE.dll
[ 98%] Built target JAGE
[ 98%] Linking CXX executable ..\build\bin\game.exe
[100%] Built target game
