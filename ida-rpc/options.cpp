#include "options.h"

Options g_options;

void Options::save( const char* config_name ) {

	char save_location[ MAXSTR ];
	qsnprintf( save_location, MAXSTR - 1, "%s\\%s", get_user_idadir( ), config_name );

	if ( this->output_type >= ( int )output_type::errors_results_and_interim_steps && this->output_enabled ) {
		msg( "[%s] Found IDA install directory at %s\n", plugin_name, get_user_idadir( ) );
	}
	if ( this->output_type >= ( int )output_type::errors_and_results && this->output_enabled ) {
		msg( "[%s] Saving config to %s\n", plugin_name, save_location );
	}

	FILE* file = qfopen( save_location, "wb" );

	if ( file ) {
		qfwrite( file, this, sizeof( Options ) );
		qfclose( file );

		beep( beep_default );
	}
	else {
		if ( this->output_type >= ( int )output_type::errors_only && this->output_enabled )
			msg( "[%s] Could not write config to %s\n", plugin_name, save_location );
	}
}

void Options::load( const char* config_name ) {

	char save_location[ MAXSTR ];
	qsnprintf( save_location, MAXSTR - 1, "%s\\%s", get_user_idadir( ), config_name );

	if ( this->output_type >= ( int )output_type::errors_results_and_interim_steps && this->output_enabled ) {
		msg( "[%s] Found IDA install directory at %s\n", plugin_name, get_user_idadir( ) );
	}
	if ( this->output_type >= ( int )output_type::errors_and_results && this->output_enabled ) {
		msg( "[%s] Loading config from %s\n", plugin_name, save_location );
	}

	FILE* file = qfopen( save_location, "rb" );

	if ( file ) {
		qfread ( file, this, sizeof( Options ) );
		qfclose( file );
	}
	else {
		if ( this->output_type >= ( int )output_type::errors_only && this->output_enabled ) {
			msg( "[%s] Could not read config from %s\n", plugin_name, save_location );
		}
	}
}
