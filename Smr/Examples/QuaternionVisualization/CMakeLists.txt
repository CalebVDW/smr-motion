PROJECT(SAMSARA_QUATVIZ)

INCLUDE_DIRECTORIES(	${SAMSARA_NEWMAT_SOURCE_DIR}
			${SAMSARA_MATH_SOURCE_DIR}
			${SAMSARA_CORE_SOURCE_DIR}
			${SAMSARA_COMMON_SOURCE_DIR}
			${SAMSARA_IO_SOURCE_DIR}
			${OPENGL_INCLUDE_DIR}
			${GLEW_INCLUDE_DIR}
			${GLUT_INCLUDE_DIR}
			${GLUT_SOURCE_DIR}
			${LOG4CPLUS_INCLUDE_DIR}
			)

LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})
 
ADD_EXECUTABLE(QuaternionVisualization MACOSX_BUNDLE
                                       quatViz.cpp)

TARGET_LINK_LIBRARIES(QuaternionVisualization newmat common math core renderer io  ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${LOG4CPLUS_LIBRARIES})
 
