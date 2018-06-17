#include <pebble.h>
#include "menuset.h"
#include "menuicon.h"

// Main window
Window *window_set;
//next window
extern Window *window_icon;

int set = 0;

// This is a simple menu layer
static SimpleMenuLayer *menu;

//////////////////////////////////////////////////

// Callback for (Yes) 
// Relays response to next menu page
static void yes_selected(int index, void *context)
{
  window_stack_push(window_icon, true);
}

// Callback for (Yes - no time) AND (no)
// Relays response back to phone
static void cant_answer(int index, void *context)
{
  if (index == 0) { // "No time"
    window_stack_push(window_icon, true);
  } else if (index == 2) { // "Didn't feel"
  window_stack_push(window_icon, true);
  }
}

// NEED TO COORDINATE ABOUT RESPONSE WHEN NO USER INPUT
// NEED TO ERASE SCREEN AFTER 1 MIN

//////////////////////////////////////////////////

static SimpleMenuItem first_menu_items[] = {
	{"Yes - no time", NULL, NULL, cant_answer},
	{"Yes", NULL, NULL, yes_selected},
	{"No", NULL, NULL, cant_answer}
};

static SimpleMenuSection first_menu_sections[] = {
	{ "Felt it?", first_menu_items, 3 }
};

//////////////////////////////////////////////////

static void window_set_load(Window *window) 
{
  Layer *layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(layer);

  // Initialize the simple menu layer
  menu = simple_menu_layer_create(bounds, 
	  window, 
	  first_menu_sections, 
	  1, NULL);

  // Add it to the window for display
  layer_add_child(layer, simple_menu_layer_get_layer(menu));
}


static void window_set_unload(Window *window) {
  simple_menu_layer_destroy(menu);
}

//////////////////////////////////////////////////

void init_menu_set()
{
  window_set = window_create();
  window_set_window_handlers(window_set, (WindowHandlers) {
    .load = window_set_load,
    .unload = window_set_unload,
  });
}

void deinit_menu_set() {
  window_destroy(window_set);
}

