#pragma once
#include "includes.h"

#define OPTION( type, variable, value ) type variable = value

enum class address_type : int {
	function_base_address,
	current_cursor_address
};

enum class output_type : int {
	errors_only,
	errors_and_results,
	errors_results_and_interim_steps
};

class Options
{
public:
	void save( const char* config_name = "ida-rpc.save" );
	void load( const char* config_name = "ida-rpc.save" );

public:
	OPTION( bool, rpc_enabled, true );

	OPTION( bool, filename_enabled, true );
	
	OPTION( bool, functionname_enabled, true );

	OPTION( bool, address_enabled, true );
	OPTION( int,  address_type, ( int )address_type::function_base_address );

	OPTION( bool, timeelapsed_enabled, true );

	OPTION( bool, output_enabled, true );
	OPTION( int,  output_type, ( int )output_type::errors_only );
};

extern Options g_options;