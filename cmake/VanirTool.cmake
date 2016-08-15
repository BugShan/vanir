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
function(vanir_parse MODULE INPUT_LIST OUTPUT_DIR TEMPLATE HEADER_LIST OPTIONS)
	foreach(header ${HEADER_LIST})
		list(APPEND OPTIONS "-I${header}")
	endforeach()

	set(OUTPUT_LIST "")
	foreach(input_path ${INPUT_LIST})
		#output name
		string(REPLACE "." "_" output_name ${input_path})
		string(REPLACE "/" "_" output_name ${output_name})
		set(output_path ${OUTPUT_DIR}/${output_name}.cpp)

		#create file
		file(WRITE ${output_path} "")
		list(APPEND OUTPUT_LIST ${output_path})
		source_group("_vanir_generated" FILES ${output_path})

		add_custom_command(
			OUTPUT ${output_name}
			COMMAND echo ${VANIR_TOOL_EXE} -m ${MODULE} -i ${input_path} -o ${output_path} -t ${TEMPLATE} --compile_option "${OPTIONS}" --display_message
			COMMAND ${VANIR_TOOL_EXE} -m ${MODULE} -i ${input_path} -o ${output_path} -t ${TEMPLATE} --compile_option "${OPTIONS}" --display_message
			DEPENDS ${input_path}
			)
		set_source_files_properties(${output_path}
			PROPERTIES OBJECT_DEPENDS ${output_name}
			)
	endforeach()
	target_sources(${MODULE} PUBLIC ${OUTPUT_LIST})
endfunction()
