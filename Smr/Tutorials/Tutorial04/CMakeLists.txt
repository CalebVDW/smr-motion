PROJECT(SAMSARA_TUTORIALS)

INCLUDE_DIRECTORIES(
			${SAMSARA_CORE_SOURCE_DIR}
			${SAMSARA_MATH_SOURCE_DIR}
			${SAMSARA_COMMON_SOURCE_DIR}
			${SAMSARA_NEWMAT_SOURCE_DIR}
			${SAMSARA_IO_SOURCE_DIR}
			${SAMSARA_UTILS_SOURCE_DIR}
			${OPENGL_INCLUDE_DIR}
			${HORDE3D_INCLUDE_DIR}
			${GLFW_INCLUDE_DIR}
	    ${LOG4CPLUS_INCLUDE_DIR})


#
# BEGIN LINK_DIRECTORIES() issue workaround
# (http://www.mail-archive.com/cmake@cmake.org/msg04341.html)
#
LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})

IF(WIN32)
LINK_DIRECTORIES(${SAMSARA_SOURCE_DIR}/thirdParty/win32/lib/)
ENDIF(WIN32)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
LINK_DIRECTORIES( ${SAMSARA_SOURCE_DIR}/thirdParty/linux_x86_64/lib/)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#
# END LINK_DIRECTORIES() issue workaround
# (http://www.mail-archive.com/cmake@cmake.org/msg04341.html)
#

ADD_EXECUTABLE(tutorial04 MACOSX_BUNDLE 
                          Tutorial04.cpp)

IF(UNIX)
  IF(APPLE)
    FIND_LIBRARY(CARBON_LIBRARY Carbon)
    FIND_LIBRARY(APPLICATION_SERVICES_LIBRARY ApplicationServices)
    FIND_LIBRARY(AGL_LIBRARY AGL)
    TARGET_LINK_LIBRARIES(tutorial04 math newmat common core io utils ${OPENGL_LIBRARIES} ${HORDE3D_LIBRARIES}  ${LOG4CPLUS_LIBRARIES} ${GLFW_LIBRARIES} ${X11_LIBRARIES} pthread ${CARBON_LIBRARY} ${APPLICATION_SERVICES_LIBRARY} ${AGL_LIBRARY})
  ELSE(APPLE)
    LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH} ${SAMSARA_SOURCE_DIR}/thirdParty/linux_x86_64/lib/)
    TARGET_LINK_LIBRARIES(tutorial04 math common core io utils newmat Horde3D Horde3DUtils ${OPENGL_LIBRARIES} ${X11_LIBRARIES} glfw Xrandr pthread ${LOG4CPLUS_LIBRARIES} )
  ENDIF(APPLE)
ENDIF(UNIX)
IF(WIN32)
  LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH} ${SAMSARA_SOURCE_DIR}/thirdParty/win32/lib/)
  TARGET_LINK_LIBRARIES(tutorial04 math newmat common core io utils glfw Horde3D Horde3DUtils ${OPENGL_LIBRARIES} ${LOG4CPLUS_LIBRARIES} )
ENDIF(WIN32)
