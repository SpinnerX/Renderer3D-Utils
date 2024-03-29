
set(
	all_src
	Renderer3D/Core/RendererLogger.cpp
	Renderer3D/Core/Application.cpp
	Renderer3D/Core/EntryPoint.cpp
	Renderer3D/platforms/Linux/LinuxWindow.cpp
	Renderer3D/Event/InputPoll.cpp
	Renderer3D/platforms/Linux/LinuxInputPoll.cpp
	Renderer3D/Core/Layer.cpp
	Renderer3D/Core/LayerStack.cpp
)

set(
	all_headers
	../include/Renderer3D/Core/core.h
	../include/Renderer3D/Core/RendererLogger.h
	../include/Renderer3D/Core/EntryPoint.h
	../include/Renderer3D/Core/Window.h
	../include/Renderer3D/Core/Application.h
	../include/Renderer3D/platforms/Linux/LinuxWindow.h
	
	../include/Renderer3D/Events/KeyCodes.h
	../include/Renderer3D/Events/MouseButtonCodes.h

	../include/Renderer3D/Events/Event.h
	../include/Renderer3D/Events/KeyEvent.h
	../include/Renderer3D/Events/MouseEvent.h
	../include/Renderer3D/Events/InputPoll.h
	../include/Renderer3D/platforms/Linux/LinuxInputPoll.h
	../include/Renderer3D/Core/Layer.h
	../include/Renderer3D/Core/LayerStack.h
)

include_directories(
	../include/Renderer3D
	../include
)

# if(UNIX AND NOT APPLE)
find_package(glfw3 REQUIRED)
# endif(UNIX AND NOT APPLE)

find_package(OpenGL REQUIRED)
# find_package(GLEW REQUIRED)
# find_package(GLUT REQUIRED)

find_package(imgui REQUIRED)
find_package(Vulkan REQUIRED)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)

add_library( ${PROJECT_NAME} ${all_src} ${all_headers} )

# NOTE: Using {OPENGL_gl_LIBRARY}, if compiling on Apple.

if(UNIX AND NOT APPLE)
	target_link_libraries(
		${PROJECT_NAME}
		glfw
		# ${OPENGL_gl_LIBRARY}
		OpenGL::GL
		# GLEW::GLEW
		# ${GLUT_LIBRARIES}
		Vulkan::Vulkan
		imgui::imgui
		fmt::fmt
		glm::glm
		spdlog::spdlog
		glad::glad
	)
endif(UNIX AND NOT APPLE)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

if(MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	COMPILE_PDB_NAME ${PROJECT_NAME}
  )

  install(
	  FILES "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/${PROJECT_NAME}.pdb"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    OPTIONAL
  )
endif()

if (BUILD_SHARED_LIBS)
	target_compile_definitions(${PROJECT_NAME}
    PUBLIC
	${PROJECT_NAME}_SHARED
  )
endif()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${all_src})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/../include" PREFIX "include" FILES ${all_headers})

install(
	TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}Config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
	EXPORT ${PROJECT_NAME}Config
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion
)

install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
