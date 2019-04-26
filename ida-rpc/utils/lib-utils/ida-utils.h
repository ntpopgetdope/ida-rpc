#pragma once

#define STRINGIFY_IDA_INPUT_FIELD( field_identifier_str, field_id ) field_identifier_str #field_id
#define DROPDOWN_FIELD( field_id ) STRINGIFY_IDA_INPUT_FIELD( "b", field_id ) // lowercase b is dropdown see https://www.hex-rays.com/products/ida/support/sdkdoc/group___f_o_r_m___c.html for reference

namespace ida_utils
{
	bool is_idb_loaded( ) {

		return ( strlen( get_path( PATH_TYPE_IDB ) ) != 0 );
	}

	const char* get_current_filename( ) {

		char filename[ MAXSTR ];
		ssize_t read_size = 0;

		read_size = get_root_filename( filename, sizeof( filename ) );

		if ( read_size > 0 ) {
			return filename;
		}
	}

	const char* get_current_processor_module( ) {

		char processor_module[ MAXSTR ];

		if ( get_idp_name( processor_module, sizeof( processor_module ) ) != NULL ) {
			return processor_module;
		}
	}

	ea_t get_current_cursor_address( ) {

		ea_t cur_addr = get_screen_ea( );

		if ( is_code( get_flags( cur_addr ) ) && cur_addr != NULL ) {
			return cur_addr;
		}
	}

	ea_t get_current_function_start_address( ) {

		ea_t cur_addr = get_current_cursor_address( );

		func_t *func = get_func( cur_addr );

		if ( func != NULL ) {
			return func->start_ea;
		}
	}

	const char* get_current_function_name( ) {

		ea_t cur_addr = get_current_cursor_address( );

		func_t *func = get_func( cur_addr );

		ssize_t size_read = 0;

		if ( func != NULL ) {

			qstring func_name;

			size_read = get_func_name( &func_name, func->start_ea );

			if ( size_read > 0 ) {
				return func_name.c_str( );
			}
		}
	}
}
