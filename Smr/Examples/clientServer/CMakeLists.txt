PROJECT(SAMSARA_CLIENTSERVER)

INCLUDE_DIRECTORIES(    ${SAMSARA_CLIENTSERVER_SOURCE_DIR}
			${BOOST_INCLUDE_PATH}
			${SAMSARA_CORE_SOURCE_DIR}
			${SAMSARA_MATH_SOURCE_DIR}
			${SAMSARA_RENDERER_SOURCE_DIR}
			${SAMSARA_IO_SOURCE_DIR}
			${SAMSARA_COMMON_SOURCE_DIR}
			${SAMSARA_NEWMAT_SOURCE_DIR}
			${OPENGL_INCLUDE_DIR}
			${GLEW_INCLUDE_DIR}
			${GLUT_INCLUDE_DIR}
			)
LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH} ${BOOST_FS_MT_D_LIB_PATH})
ADD_EXECUTABLE(client client.cpp)
ADD_EXECUTABLE(server server.cpp server.h)

IF(WIN32)
	TARGET_LINK_LIBRARIES(client Ws2_32.lib )
	TARGET_LINK_LIBRARIES(server Ws2_32.lib )
ENDIF(WIN32)
