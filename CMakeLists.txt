cmake_minimum_required( VERSION 3.25 )
set( _language_list "CXX" )

project( basic-list-select
	VERSION 0.0.1
	DESCRIPTION "Simple CLI for selecting a single item from a list"
	LANGUAGES ${_language_list}
)

include(GenerateExportHeader)
include(GNUInstallDirs)
include( cmake/gcmake-variables.cmake )
include( cmake/CPM.cmake )
include( cmake/gcmake-cross-compilation-utils.cmake )
include( cmake/gcmake-emscripten-utils.cmake )
include( cmake/gcmake-dir-config.cmake )
include( cmake/gcmake-toggle-lib-util.cmake )
include( cmake/gcmake-pre-build-configuration-utils.cmake )
include( cmake/gcmake-resource-copy-util.cmake )
include( cmake/gcmake-general-utils.cmake )
include( cmake/gcmake-windows-rc-file-utils.cmake )
include( cmake/gcmake-pgo-utils.cmake )
include( cmake/gcmake-installation-utils.cmake )
include( cmake/gcmake-cpack-utils.cmake )
include( cmake/gcmake-config-file-writer.cmake )
include( cmake/gcmake-features-util.cmake )
include( cmake/gcmake-cppfront-utils.cmake )
include( cmake/gcmake-documentation-utils.cmake )
initialize_deb_list()
initialize_minimal_installs()
initialize_target_list()
initialize_needed_bin_files_list()
initialize_additional_dependency_install_list()
initialize_generated_export_headers_list()
gcmake_init_documentable_files_list()
initialize_uncached_dep_list()
initialize_actual_dep_list()
initialize_custom_find_modules_list()


# ////////////////////////////////////////////////////////////////////////////////
# Toplevel-project-only configuration
# ////////////////////////////////////////////////////////////////////////////////
gcmake_begin_config_file()
set( IN_GCMAKE_CONTEXT TRUE )
set( PROJECT_VENDOR scupit )
ensure_gcmake_config_dirs_exist()
if( USING_EMSCRIPTEN )
	configure_emscripten_mode( WITH_HTML )
endif()

if( USING_MINGW )
	initialize_mingw_dll_install_options()
endif()

get_property( isMultiConfigGenerator GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
set( GCMAKE_SANITIZER_FLAGS "" CACHE STRING "SEMICOLON SEPARATED list of sanitizer flags to build the project with. These are included in both compiler flags and linker flags" )
set( GCMAKE_ADDITIONAL_COMPILER_FLAGS "" CACHE STRING "SEMICOLON SEPARATED list of additional compiler flags to build the project with. Useful for static analyzers or flags like -march which shouldn't be included by default" )
set( GCMAKE_ADDITIONAL_CUDA_FLAGS "" CACHE STRING "SEMICOLON SEPARATED list of additional compiler flags to build the project with. Useful for static analyzers or flags like -march which shouldn't be included by default" )
set( GCMAKE_ADDITIONAL_LINK_TIME_FLAGS "" CACHE STRING "SEMICOLON SEPARATED list of additional link-time flags to build the project with" )
set( GCMAKE_ADDITIONAL_LINKER_FLAGS "" CACHE STRING "SEMICOLON SEPARATED list of additional linker flags to build the project with" )
set( ${PROJECT_NAME}_SANITIZER_FLAGS "" CACHE STRING "SEMICOLON SEPARATED list of sanitizer flags to build project '${PROJECT_NAME}' with. These are included in both compiler flags and linker flags" )
set( ${PROJECT_NAME}_ADDITIONAL_COMPILER_FLAGS "" CACHE STRING "SEMICOLON SEPARATED list of additional compiler flags to build project '${PROJECT_NAME}' with. Useful for static analyzers or flags like -march which shouldn't be included by default" )
set( ${PROJECT_NAME}_ADDITIONAL_CUDA_FLAGS "" CACHE STRING "SEMICOLON SEPARATED list of additional CUDA flags to build project '${PROJECT_NAME}' with. Useful for static analyzers or flags like -march which shouldn't be included by default" )
set( ${PROJECT_NAME}_ADDITIONAL_LINK_TIME_FLAGS "" CACHE STRING "SEMICOLON SEPARATED list of additional link-time flags to build project '${PROJECT_NAME}' with" )
set( ${PROJECT_NAME}_ADDITIONAL_LINKER_FLAGS "" CACHE STRING "SEMICOLON SEPARATED list of additional linker flags to build project '${PROJECT_NAME}' with" )
set( CMAKE_INSTALL_DEFAULT_COMPONENT_NAME Dependencies )
set( LOCAL_TOPLEVEL_PROJECT_NAME "basic-list-select" )
set( TOPLEVEL_INCLUDE_PREFIX BASIC_LIST_SELECT )
set( TOPLEVEL_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )

list( APPEND CMAKE_MODULE_PATH "${TOPLEVEL_PROJECT_DIR}/cmake/modules" )
set( LOCAL_BUILD_SHARED_LIBS_DOC_STRING "Build compiled libraries as SHARED when their type is not explicitly specified" )
set( LOCAL_BUILD_STATIC_LIBS_DOC_STRING "Build compiled libraries as STATIC when their type is not explicitly specified" )
set( LOCAL_CMAKE_BUILD_TYPE_DOC_STRING "Which project configuration to build" )
initialize_lib_type_options( STATIC )
option( BUILD_TESTING "Build the testing tree for all non-GCMake projects. Testing trees for GCMake projects are enabled per-project. For example, this project uses the ${LOCAL_TOPLEVEL_PROJECT_NAME}_BUILD_TESTS variable." OFF )

initialize_build_tests_var()

gcmake_initialize_build_docs_var()
set( ALL_VALID_BUILD_TYPES Debug Release MinSizeRel RelWithDebInfo )
set( PROJECT_VALID_BUILD_TYPES Debug Release MinSizeRel RelWithDebInfo )
if( ${isMultiConfigGenerator} )
set( CMAKE_CONFIGURATION_TYPES ${PROJECT_VALID_BUILD_TYPES} )
else()
	set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${PROJECT_VALID_BUILD_TYPES} )

	if( NOT "${CMAKE_BUILD_TYPE}" IN_LIST ALL_VALID_BUILD_TYPES )
		set( CMAKE_BUILD_TYPE "Release" CACHE STRING "${LOCAL_CMAKE_BUILD_TYPE_DOC_STRING}" FORCE )
	endif()

	message( "Building configuration: ${CMAKE_BUILD_TYPE}" )
endif()

set( MY_RUNTIME_OUTPUT_DIR "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/$<CONFIG>" )
set( MY_LIBRARY_OUTPUT_DIR "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/$<CONFIG>" )

if( CMAKE_SOURCE_DIR STREQUAL TOPLEVEL_PROJECT_DIR )
	set( IN_GCMAKE_CONTEXT TRUE )
	cmake_path( GET CMAKE_INSTALL_INCLUDEDIR STEM _the_includedir_stem )
	if( NOT _the_includedir_stem STREQUAL PROJECT_NAME )
		set( CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}" CACHE PATH "Header file installation dir" FORCE )
	endif()
	cmake_path( GET CMAKE_INSTALL_LIBDIR STEM _the_libdir_stem )
	set( ORIGINAL_CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}" )
	if( NOT _the_libdir_stem STREQUAL PROJECT_NAME )
		if( NOT TARGET_SYSTEM_IS_WINDOWS )
			set( CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}/dependencies/${PROJECT_NAME}" CACHE PATH "Library installation dir" FORCE )
endif()
	endif()
endif()
if( "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}" )
	set( CMAKE_EXPORT_COMPILE_COMMANDS TRUE )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MY_RUNTIME_OUTPUT_DIR} )
	set( CMAKE_PDB_OUTPUT_DIRECTORY ${MY_RUNTIME_OUTPUT_DIR} )
	set( CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${MY_LIBRARY_OUTPUT_DIR} )
	set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MY_LIBRARY_OUTPUT_DIR} )
	set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MY_LIBRARY_OUTPUT_DIR} )
endif()

initialize_ipo_defaults( RELEASE MINSIZEREL RELWITHDEBINFO )
initialize_pgo_defaults()
initialize_install_mode()
if( TOPLEVEL_PROJECT_DIR STREQUAL CMAKE_SOURCE_DIR AND ( GCMAKE_INSTALL_MODE STREQUAL "NORMAL" OR GCMAKE_INSTALL_MODE STREQUAL "EXE_ONLY"  ) )
	mark_gcmake_target_usage( list-select FULL )
endif()
if( (TRUE) AND (( NOT CMAKE_SOURCE_DIR STREQUAL TOPLEVEL_PROJECT_DIR AND DEFINED TARGET_list-select_INSTALL_MODE ) OR (CMAKE_SOURCE_DIR STREQUAL TOPLEVEL_PROJECT_DIR AND (GCMAKE_INSTALL_MODE STREQUAL "NORMAL" OR GCMAKE_INSTALL_MODE STREQUAL "EXE_ONLY" )) ) )
	mark_gcmake_project_usage( ftxui MINIMAL )
	mark_gcmake_project_usage( ftxui MINIMAL )
endif()
if( NOT DEFINED ${LOCAL_TOPLEVEL_PROJECT_NAME}_USE_DEFAULT_FEATURES )
gcmake_set_use_default_features( ${LOCAL_TOPLEVEL_PROJECT_NAME} ON )
endif()
if( ${LOCAL_TOPLEVEL_PROJECT_NAME}_USE_DEFAULT_FEATURES )
endif()


# ////////////////////////////////////////////////////////////////////////////////
# Language Configuration
# ////////////////////////////////////////////////////////////////////////////////

set( PROJECT_CXX_LANGUAGE_MINIMUM_STANDARD 17 )

if( "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}" )
	message( "${PROJECT_NAME} is using at least C++${PROJECT_CXX_LANGUAGE_MINIMUM_STANDARD}" )
endif()

# ////////////////////////////////////////////////////////////////////////////////
# Predefined dependency config
# ////////////////////////////////////////////////////////////////////////////////
if( (DEFINED TARGET_list-select_INSTALL_MODE AND (TRUE)) )
option( FTXUI_BUILD_DOCS "Set to ON to build FTXUI docs. GCMake sets this to OFF by default." OFF )
option( FTXUI_BUILD_EXAMPLES "Set to ON to build FTXUI examples. GCMake sets this to OFF by default." OFF )

set( ftxui_RELATIVE_DEP_PATH ftxui )
if( "${PROJECT_ftxui_INSTALL_MODE}" STREQUAL "FULL" )
	set( FTXUI_ENABLE_INSTALL_DEFAULT_VALUE ON )
elseif( "${PROJECT_ftxui_INSTALL_MODE}" STREQUAL "MINIMAL" )
	set( FTXUI_ENABLE_INSTALL_DEFAULT_VALUE OFF )
endif()
option( FTXUI_ENABLE_INSTALL "Whether to install ftxui. GCMake sets this to ${FTXUI_ENABLE_INSTALL_DEFAULT_VALUE} by default." ${FTXUI_ENABLE_INSTALL_DEFAULT_VALUE} )
CPMAddPackage(
	NAME ftxui
	DOWNLOAD_ONLY OFF
	GIT_REPOSITORY "git@github.com:scupit/FTXUI.git"
	GIT_TAG "other-stream-support"
	GIT_SUBMODULES_RECURSE TRUE
	SYSTEM
)
append_to_actual_dep_list( ftxui )
endif()
if( (DEFINED TARGET_list-select_INSTALL_MODE AND (TRUE)) )
endif()
set( DEPENDENCY_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}" )
if( NOT TARGET_SYSTEM_IS_WINDOWS )
	set( CMAKE_INSTALL_LIBDIR "${ORIGINAL_CMAKE_INSTALL_LIBDIR}" CACHE PATH "Library installation dir" FORCE )
endif()

# ////////////////////////////////////////////////////////////////////////////////
# Build Configurations
# ////////////////////////////////////////////////////////////////////////////////

initialize_build_config_vars()

list( APPEND RELEASE_LOCAL_DEFINES
	"NDEBUG"
)

list( APPEND MINSIZEREL_LOCAL_DEFINES
	"NDEBUG"
)

list( APPEND RELWITHDEBINFO_LOCAL_DEFINES
	"NDEBUG"
)

if( USING_GCC )
	list( APPEND DEBUG_LOCAL_COMPILER_FLAGS
		 "-O0"
		"-g"
		"-Wall"
		"-Wextra"
		"-Wconversion"
		"-Wuninitialized"
		"-pedantic"
		"-pedantic-errors" 
	)
	list( APPEND DEBUG_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -O0>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -g>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -Wall>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -Wextra>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -Wconversion>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -Wuninitialized>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -pedantic>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -pedantic-errors>" 
	)
	list( APPEND RELEASE_LOCAL_COMPILER_FLAGS
		 "-O3" 
	)
	list( APPEND RELEASE_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -O3>" 
	)
	list( APPEND RELEASE_LOCAL_LINK_FLAGS
		"LINKER:-s"
	)
	list( APPEND MINSIZEREL_LOCAL_COMPILER_FLAGS
		 "-Os" 
	)
	list( APPEND MINSIZEREL_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -Os>" 
	)
	list( APPEND MINSIZEREL_LOCAL_LINK_FLAGS
		"LINKER:-s"
	)
	list( APPEND RELWITHDEBINFO_LOCAL_COMPILER_FLAGS
		 "-O2"
		"-g" 
	)
	list( APPEND RELWITHDEBINFO_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -O2>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -g>" 
	)
endif()
if( USING_CLANG )
	list( APPEND DEBUG_LOCAL_COMPILER_FLAGS
		 "-O0"
		"-g"
		"-Wall"
		"-Wextra"
		"-Wconversion"
		"-Wuninitialized"
		"-pedantic"
		"-pedantic-errors" 
	)
	list( APPEND DEBUG_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -O0>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -g>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -Wall>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -Wextra>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -Wconversion>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -Wuninitialized>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -pedantic>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -pedantic-errors>" 
	)
	list( APPEND RELEASE_LOCAL_COMPILER_FLAGS
		 "-O3" 
	)
	list( APPEND RELEASE_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -O3>" 
	)
	list( APPEND RELEASE_LOCAL_LINK_FLAGS
		"LINKER:-s"
	)
	list( APPEND MINSIZEREL_LOCAL_COMPILER_FLAGS
		 "-Os" 
	)
	list( APPEND MINSIZEREL_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -Os>" 
	)
	list( APPEND MINSIZEREL_LOCAL_LINK_FLAGS
		"LINKER:-s"
	)
	list( APPEND RELWITHDEBINFO_LOCAL_COMPILER_FLAGS
		 "-O2"
		"-g" 
	)
	list( APPEND RELWITHDEBINFO_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -O2>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler -g>" 
	)
endif()
if( USING_MSVC )
	list( APPEND DEBUG_LOCAL_COMPILER_FLAGS
		 "/Od"
		"/W4"
		"/DEBUG"
		"/RTC1" 
	)
	list( APPEND DEBUG_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler /Od>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler /W4>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler /DEBUG>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler /RTC1>" 
	)
	list( APPEND RELEASE_LOCAL_COMPILER_FLAGS
		 "/O2" 
	)
	list( APPEND RELEASE_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler /O2>" 
	)
	list( APPEND MINSIZEREL_LOCAL_COMPILER_FLAGS
		 "/O1" 
	)
	list( APPEND MINSIZEREL_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler /O1>" 
	)
	list( APPEND RELWITHDEBINFO_LOCAL_COMPILER_FLAGS
		 "/O2"
		"/DEBUG" 
	)
	list( APPEND RELWITHDEBINFO_LOCAL_CUDA_FLAGS
		 "$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler /O2>"
		"$<$<BOOL:${USING_CUDA}>:SHELL:-Xcompiler /DEBUG>" 
	)
endif()
_gcmake_clear_scope_default_compiler_flags()
set( PROJECT_INCLUDE_PREFIX "BASIC_LIST_SELECT" )
set( PROJECT_BASE_NAME basic-list-select )
set( basic-list-select_ENTRY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" )
set( basic-list-select_SRC_ROOT "${basic-list-select_ENTRY_ROOT}/src/${PROJECT_INCLUDE_PREFIX}" )
set( basic-list-select_GENERATED_SOURCE_ROOT "${CMAKE_CURRENT_BINARY_DIR}/GENERATED_SOURCES" )
set( basic-list-select_HEADER_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_INCLUDE_PREFIX}" )
set( basic-list-select_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" )
set( basic-list-select_PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" )


# ////////////////////////////////////////////////////////////////////////////////
# Pre-build script configuration
# ////////////////////////////////////////////////////////////////////////////////
initialize_prebuild_step( "PRE_BUILD_SCRIPT_basic-list-select" )


# ////////////////////////////////////////////////////////////////////////////////
# 'resources' build-time directory copier
# ////////////////////////////////////////////////////////////////////////////////
copy_resource_dir_if_exists(
	${CMAKE_CURRENT_SOURCE_DIR}/resources
	${MY_RUNTIME_OUTPUT_DIR}/resources
)

# ////////////////////////////////////////////////////////////////////////////////
# Outputs
# ////////////////////////////////////////////////////////////////////////////////

set( basic-list-select_SOURCES
)

set( basic-list-select_PRIVATE_HEADERS
)

list( APPEND basic-list-select_SOURCES ${basic-list-select_PRIVATE_HEADERS} )
set( basic-list-select_HEADERS
)

set( basic-list-select_TEMPLATE_IMPLS
)

list( APPEND basic-list-select_HEADERS ${basic-list-select_TEMPLATE_IMPLS} )
if( DEFINED TARGET_list-select_INSTALL_MODE AND (TRUE) )

# ========== list-select ==========
add_library( list-select_INTERNAL_RECEIVER_LIB INTERFACE )

add_executable( list-select )
add_executable( basic-list-select::list-select ALIAS list-select )

if( USING_EMSCRIPTEN )
	apply_emscripten_specifics( list-select_INTERNAL_RECEIVER_LIB list-select )
endif()
exe_add_lib_relative_install_rpath( list-select )
if( DEFINED TARGET_list-select_INSTALL_MODE )
	add_to_target_installation_list( list-select )
endif()
gcmake_apply_include_dirs( list-select_INTERNAL_RECEIVER_LIB EXE_RECEIVER "${basic-list-select_INCLUDE_DIR}" "${basic-list-select_PRIVATE_INCLUDE_DIR}" )
gcmake_apply_exe_files( list-select list-select_INTERNAL_RECEIVER_LIB 
	"${basic-list-select_ENTRY_ROOT}/main.cpp"
	basic-list-select_SOURCES
	basic-list-select_HEADERS
)

set_target_properties( list-select PROPERTIES
	CXX_EXTENSIONS OFF
	C_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${MY_RUNTIME_OUTPUT_DIR}
)

if( ( USING_MINGW ) )
	set_target_properties( list-select PROPERTIES 
		NO_SYSTEM_FROM_IMPORTED TRUE
	)
endif()

add_depends_on_pre_build( list-select_INTERNAL_RECEIVER_LIB )
add_depends_on_pre_build( list-select )
set( list-select_DEBUG_OWN_LINK_FLAGS "${DEBUG_LOCAL_LINK_FLAGS}" )
set( list-select_DEBUG_OWN_COMPILER_FLAGS "${DEBUG_LOCAL_COMPILER_FLAGS}" )
set( list-select_DEBUG_OWN_CUDA_FLAGS "${DEBUG_LOCAL_CUDA_FLAGS}" )
set( list-select_DEBUG_OWN_DEFINES "${DEBUG_LOCAL_DEFINES}" )
set( list-select_RELEASE_OWN_LINK_FLAGS "${RELEASE_LOCAL_LINK_FLAGS}" )
set( list-select_RELEASE_OWN_COMPILER_FLAGS "${RELEASE_LOCAL_COMPILER_FLAGS}" )
set( list-select_RELEASE_OWN_CUDA_FLAGS "${RELEASE_LOCAL_CUDA_FLAGS}" )
set( list-select_RELEASE_OWN_DEFINES "${RELEASE_LOCAL_DEFINES}" )
set( list-select_MINSIZEREL_OWN_LINK_FLAGS "${MINSIZEREL_LOCAL_LINK_FLAGS}" )
set( list-select_MINSIZEREL_OWN_COMPILER_FLAGS "${MINSIZEREL_LOCAL_COMPILER_FLAGS}" )
set( list-select_MINSIZEREL_OWN_CUDA_FLAGS "${MINSIZEREL_LOCAL_CUDA_FLAGS}" )
set( list-select_MINSIZEREL_OWN_DEFINES "${MINSIZEREL_LOCAL_DEFINES}" )
set( list-select_RELWITHDEBINFO_OWN_LINK_FLAGS "${RELWITHDEBINFO_LOCAL_LINK_FLAGS}" )
set( list-select_RELWITHDEBINFO_OWN_COMPILER_FLAGS "${RELWITHDEBINFO_LOCAL_COMPILER_FLAGS}" )
set( list-select_RELWITHDEBINFO_OWN_CUDA_FLAGS "${RELWITHDEBINFO_LOCAL_CUDA_FLAGS}" )
set( list-select_RELWITHDEBINFO_OWN_DEFINES "${RELWITHDEBINFO_LOCAL_DEFINES}" )
target_compile_definitions( list-select_INTERNAL_RECEIVER_LIB
	INTERFACE 
		"$<$<CONFIG:Debug>:${list-select_DEBUG_OWN_DEFINES}>"
		"$<$<CONFIG:Release>:${list-select_RELEASE_OWN_DEFINES}>"
		"$<$<CONFIG:MinSizeRel>:${list-select_MINSIZEREL_OWN_DEFINES}>"
		"$<$<CONFIG:RelWithDebInfo>:${list-select_RELWITHDEBINFO_OWN_DEFINES}>"
)

target_link_options( list-select
	PRIVATE 
		"$<$<CONFIG:Debug>:${list-select_DEBUG_OWN_LINK_FLAGS}>"
		"$<$<CONFIG:Release>:${list-select_RELEASE_OWN_LINK_FLAGS}>"
		"$<$<CONFIG:MinSizeRel>:${list-select_MINSIZEREL_OWN_LINK_FLAGS}>"
		"$<$<CONFIG:RelWithDebInfo>:${list-select_RELWITHDEBINFO_OWN_LINK_FLAGS}>"
)

target_compile_options( list-select
	PRIVATE 
		"$<$<AND:$<CONFIG:Debug>,$<NOT:$<COMPILE_LANGUAGE:CUDA>>>:${list-select_DEBUG_OWN_COMPILER_FLAGS}>"
		"$<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CUDA>>:${list-select_DEBUG_OWN_CUDA_FLAGS}>"
		"$<$<AND:$<CONFIG:Release>,$<NOT:$<COMPILE_LANGUAGE:CUDA>>>:${list-select_RELEASE_OWN_COMPILER_FLAGS}>"
		"$<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CUDA>>:${list-select_RELEASE_OWN_CUDA_FLAGS}>"
		"$<$<AND:$<CONFIG:MinSizeRel>,$<NOT:$<COMPILE_LANGUAGE:CUDA>>>:${list-select_MINSIZEREL_OWN_COMPILER_FLAGS}>"
		"$<$<AND:$<CONFIG:MinSizeRel>,$<COMPILE_LANGUAGE:CUDA>>:${list-select_MINSIZEREL_OWN_CUDA_FLAGS}>"
		"$<$<AND:$<CONFIG:RelWithDebInfo>,$<NOT:$<COMPILE_LANGUAGE:CUDA>>>:${list-select_RELWITHDEBINFO_OWN_COMPILER_FLAGS}>"
		"$<$<AND:$<CONFIG:RelWithDebInfo>,$<COMPILE_LANGUAGE:CUDA>>:${list-select_RELWITHDEBINFO_OWN_CUDA_FLAGS}>"
)

target_compile_features( list-select
	PRIVATE 
		cxx_std_${PROJECT_CXX_LANGUAGE_MINIMUM_STANDARD}
)

set_target_properties( list-select PROPERTIES
	CXX_STANDARD_REQUIRED TRUE
)

if( TRUE )
	gcmake_unaliased_target_name( ftxui::dom _UNALIASED_ftxui__dom )
endif()
if( TRUE )
	gcmake_unaliased_target_name( ftxui::component _UNALIASED_ftxui__component )
endif()
target_link_libraries( list-select_INTERNAL_RECEIVER_LIB 
	INTERFACE
		$<BUILD_INTERFACE:ftxui::dom> $<INSTALL_INTERFACE:${LOCAL_TOPLEVEL_PROJECT_NAME}::${_UNALIASED_ftxui__dom}>
		$<BUILD_INTERFACE:ftxui::component> $<INSTALL_INTERFACE:${LOCAL_TOPLEVEL_PROJECT_NAME}::${_UNALIASED_ftxui__component}>
)
if( DEFINED TARGET_list-select_INTERNAL_RECEIVER_LIB_INSTALL_MODE )
	if( TRUE )
		add_to_minimal_installs( ftxui::dom "${ftxui_RELATIVE_DEP_PATH}")
	endif()
	if( TRUE )
		add_to_minimal_installs( ftxui::component "${ftxui_RELATIVE_DEP_PATH}")
	endif()
endif()
target_link_libraries( list-select PRIVATE list-select_INTERNAL_RECEIVER_LIB )
endif()

# ////////////////////////////////////////////////////////////////////////////////
# Documentation Generation
# ////////////////////////////////////////////////////////////////////////////////
gcmake_add_to_documentable_files_list( ${PROJECT_BASE_NAME}_HEADERS )
if( NOT ${LOCAL_TOPLEVEL_PROJECT_NAME}_DOCUMENT_HEADERS_ONLY )

gcmake_add_to_documentable_files_list( ${PROJECT_BASE_NAME}_SOURCES )
endif()

if( ${LOCAL_TOPLEVEL_PROJECT_NAME}_DOCUMENT_PRIVATE_HEADERS )

gcmake_add_to_documentable_files_list( ${PROJECT_BASE_NAME}_PRIVATE_HEADERS )
endif()

set( PROJECT_DOCS_OUTPUT_DIR  )

# ////////////////////////////////////////////////////////////////////////////////
# Installation and Export configuration
# ////////////////////////////////////////////////////////////////////////////////
gcmake_end_config_file()
if( GCMAKE_INSTALL )
		configure_installation( LOCAL_PROJECT_COMPONENT_NAME )
		if( NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${TOPLEVEL_PROJECT_DIR}" )
		raise_deb_list()
		raise_minimal_installs()
		raise_target_list()
		raise_needed_bin_files_list()
		raise_additional_dependency_install_list()
		raise_generated_export_headers_list()
	endif()
endif()

if( GCMAKE_INSTALL AND "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}" )
	gcmake_configure_cpack(
		VENDOR "${PROJECT_VENDOR}"
		PROJECT_COMPONENT ${LOCAL_PROJECT_COMPONENT_NAME}
		INSTALLER_TITLE "basic-list-select"
		INSTALLER_DESCRIPTION "Simple CLI for selecting a single item from a list"
		INSTALLER_EXE_PREFIX "basic-list-select"
		SHORTCUT_MAP ""
	)
endif()
