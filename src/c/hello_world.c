#include <pebble.h>
#include "menuset.h"
#include "menuicon.h"
#include "icon.h"
#include "menurest.h"

extern Window *window_set;
extern Window *window_icon;
extern Window *window_rest;

static void init(void) {
	icon_init();
    init_menu_rest();
    init_menu_set();
    init_menu_icon();
    window_stack_push(window_set, true); // GET RID OF THIS
    window_stack_push(window_rest, true);
}

static void deinit(void) {
	// Destroy the text layer
   deinit_menu_rest();
    deinit_menu_set();
    deinit_menu_icon();
	window_destroy(window_set);
	window_destroy(window_icon);
	window_destroy(window_rest);
}

int main(void) {
    init();
    
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window_rest);
    
    app_event_loop();
    deinit();
}
