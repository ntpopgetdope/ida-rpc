#include "includes.h"
#include "options.h"
#include "interface.h"

#include "utils/lib-utils/ida-utils.h"
#include "utils/lib-utils/discord-utils.h"

#ifdef _Release
	#include "utils/build-version/ver.h"
#endif
#ifdef _Release64
	#include "utils/build-version/ver64.h"
#endif	

int64_t     start_time;
const char* app_id       = "410737797914296320";

const char* IDAP_comment = "IDA plugin by shigureJ";
const char* IDAP_help	 = "IDA plugin by shigureJ";
const char* IDAP_name    = "IDA RPC";
const char* IDAP_hotkey  = "Ctrl-Alt-R";

#pragma region callbacks // collapse that nasty shit

namespace callbacks
{
	// note that all the switch statements in these callbacks are overkill you can just call
	// update discord presence in them as discord limits and queues update requests but w/e 
	int idaapi idp_callback( void* /*user_data*/, int notification_code, va_list va ) 
	{
		switch ( notification_code )
		{
			case processor_t::event_t::ev_oldfile:
			case processor_t::event_t::ev_newfile:
			case processor_t::event_t::ev_newbinary:
			case processor_t::event_t::ev_rename:
			{
				//if ( g_Options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_Options.output_enabled ) {
				//	msg( "[%s] %s called with notification code %i\n", IDAP_name, __FUNCTION__, notification_code );
				//}
				discord_utils::update_discord_presence( start_time );
			}
			break;

			default:
				break;
		}

		return 0;
	}

	int idaapi idb_callback( void* /*user_data*/, int notification_code, va_list va )
	{
		switch ( notification_code )
		{
			case idb_event::savebase:
			case idb_event::func_updated:
			case idb_event::set_func_start:
			case idb_event::renamed:
			case idb_event::func_added:
			case idb_event::deleting_func:
			case idb_event::allsegs_moved: // This event is sent when ida finishing rebasing a database
			{
				//if ( g_Options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_Options.output_enabled ) {
				//	msg( "[%s] %s called with notification code %i\n", IDAP_name, __FUNCTION__, notification_code );
				//}
				discord_utils::update_discord_presence( start_time );
			}
			break;

			default:
				break;
		}

		return 0;
	}

	int idaapi ui_callback( void* /*user_data*/, int notification_code, va_list va ) {

		switch ( notification_code )
		{
			case ui_load_file:
			case ui_updated_actions :
			case ui_refresh:
			case ui_get_cursor:
			case ui_get_curline:
			{
				//if( g_Options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_Options.output_enabled ) {
				//	msg( "[%s] %s called with notification code %i\n", IDAP_name, __FUNCTION__, notification_code );
				//}
				discord_utils::update_discord_presence( start_time );
			}
			break;

			default:
				break;
		}

		return 0;
	}

	int idaapi view_callback( void* /*user_data*/, int notification_code, va_list va ) {

		switch ( notification_code )
		{
			case view_loc_changed:
			case view_switched:
			case view_click:
			case view_curpos:
			{
				//if( g_Options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_Options.output_enabled ) {
				//	msg( "[%s] %s called with notification code %i\n", IDAP_name, __FUNCTION__, notification_code );
				//}
				discord_utils::update_discord_presence( start_time );
			}
			break;

			default:
				break;
		}

		return 0;
	}

	int idaapi output_callback( void* /*user_data*/, int notification_code, va_list va ) {

		switch ( notification_code )
		{

			default:
				break;
		}

		return 0;
	}
}

static int idaapi hook_callbacks( ) {

	// IDP callback hook ///////////////////////////////////////////////////////////////////////////////////////////////
	if ( !hook_to_notification_point( HT_IDP, ( hook_cb_t* )callbacks::idp_callback ) ) {

		if ( g_options.output_type >= ( int )output_type::errors_only && g_options.output_enabled ) {
			msg( "[%s] %s -> hook_to_notification_point( HT_IDP ) failed\n", IDAP_name, __FUNCTION__ );
		}

		return PLUGIN_SKIP;
	}
	else {

		if ( g_options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_options.output_enabled ) {
			msg( "[%s] %s -> hook_to_notification_point( HT_IDP ) was successful\n", IDAP_name, __FUNCTION__ );
		}
	}

	// IDB callback hook ///////////////////////////////////////////////////////////////////////////////////////////////
	if ( !hook_to_notification_point( HT_IDB, ( hook_cb_t* )callbacks::idb_callback ) ) {

		if ( g_options.output_type >= ( int )output_type::errors_only && g_options.output_enabled ) {
			msg( "[%s] %s -> hook_to_notification_point( HT_IDB ) failed\n", IDAP_name, __FUNCTION__ );
		}

		return PLUGIN_SKIP;
	}

	else {
		if ( g_options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_options.output_enabled ) {
			msg( "[%s] %s -> hook_to_notification_point( HT_IDB ) was successful\n", IDAP_name, __FUNCTION__ );
		}
	}

	// UI callback hook ////////////////////////////////////////////////////////////////////////////////////////////////
	if ( !hook_to_notification_point( HT_UI, ( hook_cb_t* )callbacks::ui_callback ) ) {

		if ( g_options.output_type >= ( int )output_type::errors_only && g_options.output_enabled ) {
			msg( "[%s] %s -> hook_to_notification_point( HT_UI ) failed\n", IDAP_name, __FUNCTION__ );
		}

		return PLUGIN_SKIP;
	}

	else {

		if ( g_options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_options.output_enabled ) {
			msg( "[%s] %s -> hook_to_notification_point( HT_UI ) was successful\n", IDAP_name, __FUNCTION__ );
		}
	}

	// VIEW callback hook //////////////////////////////////////////////////////////////////////////////////////////////
	if ( !hook_to_notification_point( HT_VIEW, ( hook_cb_t* )callbacks::view_callback ) ) {

		if ( g_options.output_type >= ( int )output_type::errors_only && g_options.output_enabled ) {
			msg( "[%s] %s -> hook_to_notification_point( HT_VIEW ) failed\n", IDAP_name, __FUNCTION__ );
		}

		return PLUGIN_SKIP;
	}
	else {

		if ( g_options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_options.output_enabled ) {
			msg( "[%s] %s -> hook_to_notification_point( HT_VIEW ) was successful\n", IDAP_name, __FUNCTION__ );
		}
	}

	// OUTPUT callback hook ////////////////////////////////////////////////////////////////////////////////////////////
	if ( !hook_to_notification_point( HT_OUTPUT, ( hook_cb_t* )callbacks::output_callback ) ) {

		if ( g_options.output_type >= ( int )output_type::errors_only && g_options.output_enabled ) {
			msg( "[%s] %s -> hook_to_notification_point( HT_OUTPUT ) failed\n", IDAP_name, __FUNCTION__ );
		}

		return PLUGIN_SKIP;
	}
	else {

		if ( g_options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_options.output_enabled ) {
			msg( "[%s] %s -> hook_to_notification_point( HT_OUTPUT ) was successful\n", IDAP_name, __FUNCTION__ );
		}
	}
}

static void idaapi unhook_callbacks( ) {

	unhook_from_notification_point( HT_IDP,	   ( hook_cb_t* )callbacks::idp_callback    );
	unhook_from_notification_point( HT_IDP,	   ( hook_cb_t* )callbacks::idb_callback    );
	unhook_from_notification_point( HT_UI,	   ( hook_cb_t* )callbacks::ui_callback     );
	unhook_from_notification_point( HT_UI,	   ( hook_cb_t* )callbacks::view_callback   );
	//unhook_from_notification_point( HT_OUTPUT, ( hook_cb_t* )callbacks::output_callback ); // unused
}

#pragma endregion 
	
static int idaapi IDAP_init( void ) {	

	addon_info_t addon;
	addon.id       = "shigureJ.IDA.RPC";
	addon.name     = "IDA RPC";
	addon.producer = "shigureJ";
	addon.url      = "https://www.github.com/offlineJ";
	addon.version  = AUTO_VERSION_STR;
	addon.freeform = "Copyright (c) 2018 shigureJ <https://keybase.io/shigurej>\n"
		             "All rights reserved.\n";

	register_addon( &addon );

	g_options.load( ); // loaded before callbacks so they are able to output

	msg( "[%s] v%.2f by shigureJ loaded\n", IDAP_name, AUTO_VERSION_RELEASE );

	start_time = time( 0 );

	if ( g_options.rpc_enabled ) {

		if ( hook_callbacks( ) == PLUGIN_SKIP ) {

			if( g_options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_options.output_enabled ) {
				msg( "[%s] %s -> one or more callback hooks failed plugin loading will be skipped\n", IDAP_name, __FUNCTION__ );
			}

			return PLUGIN_SKIP;
		}
	}
	if ( !ida_utils::is_idb_loaded( ) ) {

		if( g_options.output_type >= ( int )output_type::errors_results_and_interim_steps && g_options.output_enabled ) {
			msg( "[%s] %s -> no idb currently loaded setting state to idle\n", IDAP_name, __FUNCTION__ );
		}

		return PLUGIN_SKIP;
	}
	
	discord_utils::discord_init( app_id );
	
	return PLUGIN_KEEP;
}

static void idaapi IDAP_term( void ) {

	unhook_callbacks     ( );
	Discord_ClearPresence( );
	Discord_Shutdown     ( );
	return;
}

static bool idaapi IDAP_run( size_t arg ) {

	show_options( );
	
	if ( g_options.rpc_enabled ) {
			
		if ( ida_utils::is_idb_loaded( ) && g_options.output_type >= ( int )output_type::errors_and_results && g_options.output_enabled ) {
			msg( "[%s] Version: %.2f\n",		              IDAP_name, AUTO_VERSION_RELEASE  );
			msg( "[%s] Built for IDA: %i\n",	              IDAP_name, IDP_INTERFACE_VERSION );
			msg( "[%s] Processor module: %s \n",		      IDAP_name, ida_utils::get_current_processor_module( ) );
			msg( "[%s] Currently open file: %s\n",		  IDAP_name, ida_utils::get_current_filename( ) );
			msg( "[%s] Current function: %s - 0x%a\n",	  IDAP_name, ida_utils::get_current_function_name( ), ida_utils::get_current_function_start_address( ) );
			msg( "[%s] Current selected address: 0x%a\n", IDAP_name, ida_utils::get_current_cursor_address( ) );
		}

		discord_utils::update_discord_presence( start_time );
	}
	
	return true;
}		

plugin_t PLUGIN = {
	IDP_INTERFACE_VERSION,	// IDA version plugin was written for 
	PLUGIN_FIX,				// Plugin flags 
	IDAP_init,				// Init func
	IDAP_term,				// Clean up func
	IDAP_run,				// Main plugin body
	IDAP_comment,			// Comment for status line or for hints
	IDAP_help,				// Multiline help for the plugin
	IDAP_name,				// Plugin name shown in edit -> plugins menu 
	IDAP_hotkey				// Hotkey to run the plugin 
};
