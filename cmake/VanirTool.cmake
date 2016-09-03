include(CMakeParseArguments)

# vanir tool path on different platform
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(VANIR_TOOL_BIN_DIR ${VANIR_ROOT_DIR}/bin/mac)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(VANIR_TOOL_BIN_DIR ${VANIR_ROOT_DIR}/bin/linux)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(VANIR_TOOL_BIN_DIR ${VANIR_ROOT_DIR}/bin/window)
else()
	message(SEND_ERROR	"Unkown platform!"
						"[Vanir] only supports @Mac, @Linux, @Window platforms now")
endif()
set(VANIR_TOOL_EXE ${VANIR_TOOL_BIN_DIR}/vanir)

# vanir parse function
# @param TARGET:			the target that the generated source file attached to
# @param MODULE:			The Module name, and the tool would generate a class named "{MODULE}MODULE" what inherited from class[vanir::Module].
# @param INPUT_LIST:		all the source or header files need to parse
# @param OUTPUT_PATH:		the path of the output file
# @param TEMPLATE:			the path of the mustache template file
# @param INCLUDE_DIR_LIST:	the include directores that the clang use to compile all the {INPUT_LIST}
# @param OPTION:			all the flag option that the clang use to compile all the {INPUT_LIST}
function(vanir_parse)
	cmake_parse_arguments(PARAM "" "TARGET;MODULE;OUTPUT_PATH;TEMPLATE" "INPUT_LIST;INCLUDE_DIR_LIST;OPTIONS" ${ARGN})
	foreach(inc ${PARAM_INCLUDE_DIR_LIST})
		list(APPEND OPTIONS "-I${inc}")
	endforeach()

	#create file
	if(NOT EXISTS ${PARAM_OUTPUT_PATH})
		file(WRITE ${PARAM_OUTPUT_PATH} "")
	endif()
	source_group("_vanir_generated" FILES ${PARAM_OUTPUT_PATH})
	target_sources(${PARAM_TARGET} PUBLIC ${PARAM_OUTPUT_PATH})

	add_custom_target(
		${PARAM_MODULE}_GENERATED
		COMMAND echo "vanir parsing..."
		COMMAND ${VANIR_TOOL_EXE} -m ${PARAM_MODULE} -i ${PARAM_INPUT_LIST} -o ${PARAM_OUTPUT_PATH} -t ${PARAM_TEMPLATE} --compile_option "${PARAM_OPTIONS}" --display_message
		)
	add_dependencies(${PARAM_TARGET} ${PARAM_MODULE}_GENERATED)
endfunction()
