#pragma once
#include "discord-rpc.h"

namespace discord_utils
{
	static void handle_discord_ready( ) {

		if ( g_options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_options.output_enabled )
			msg( "Discord: ready\n" );
	}

	static void handle_discord_disconnected( int errcode, const char* message ) {

		if ( g_options.output_type >= ( int )output_type::errors_only && g_options.output_enabled )
			msg( "Discord: disconnected (%d: %s)\n", errcode, message );
	}

	static void handle_discord_error( int errcode, const char* message ) {

		if ( g_options.output_type >= ( int )output_type::errors_only && g_options.output_enabled )
			msg( "Discord: error (%d: %s)\n", errcode, message );
	}

	static void discord_init( const char* app_id ) {

		DiscordEventHandlers handlers;
		memset( &handlers, 0, sizeof( handlers ) );

		handlers.ready		  = handle_discord_ready;
		handlers.disconnected = handle_discord_disconnected;
		handlers.errored	      = handle_discord_error;

		Discord_Initialize( app_id, &handlers, 1, NULL );
	}

	static void update_discord_presence( int64_t start_time ) {

		if ( g_options.rpc_enabled ) {

			DiscordRichPresence rpc;
			memset( &rpc, 0, sizeof( rpc ) );

			( g_options.filename_enabled ) ? rpc.details = ida_utils::get_current_filename( ) : rpc.details = "";

			char state[ MAXSTR ]; // heh *teleports behind you*

			const char* current_function = ida_utils::get_current_function_name( );

			if ( current_function != NULL && strcmp( current_function, "(null)" ) != 0 ) {
				
				if ( g_options.address_enabled ) {

					switch ( g_options.address_type )
					{
						case ( int )address_type::function_base_address:

							qsnprintf( state, sizeof( state ) - 1, "Reversing %s ( 0x%a )", current_function, ida_utils::get_current_function_start_address( ) );
							break;

						case ( int )address_type::current_cursor_address:
							qsnprintf( state, sizeof( state ) - 1, "Reversing %s ( 0x%a )", current_function, ida_utils::get_current_cursor_address( ) );
							break;

						default:
							break;
					}
				}

				else if ( !g_options.address_enabled ) {

					qsnprintf( state, sizeof( state ) - 1, "Reversing %s", current_function );
				}
			}
			else {

				qsnprintf( state, sizeof( state ) - 1, "Idle" );
			}
			
			( g_options.functionname_enabled ) ? rpc.state = state : rpc.state = "";

			( g_options.timeelapsed_enabled ) ? rpc.startTimestamp = start_time : rpc.startTimestamp = NULL;

			#ifdef _Release
			rpc.largeImageKey = "ida-pro";
			//rpc.smallImageKey = "ida-pro";
			#endif

			#ifdef _Release64
			rpc.largeImageKey = "ida-pro64";
			//rpc.smallImageKey = "ida-pro64";
			#endif

			Discord_UpdatePresence( &rpc );
		}

		else if ( !g_options.rpc_enabled ) {

			Discord_ClearPresence( );

			return;
		}
	}
}
