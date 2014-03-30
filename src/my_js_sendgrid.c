#include <pebble.h>
#include <stdlib.h>

static Window *window;
static TextLayer *text_layer;
static TextLayer *text_layer2;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  DictionaryIterator *iter2;
  app_message_outbox_begin(&iter2);
  BatteryChargeState cs = battery_state_service_peek();
  Tuplet value = TupletInteger(1, cs.charge_percent);
  dict_write_tuplet(iter2, &value);
  app_message_outbox_send();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  //text_layer = text_layer_create((GRect) { .origin = { 0,72 }, .size = { bounds.size.w, 20 } });
  //BatteryChargeState cs = battery_state_service_peek();
  //char buf[16];
  //text_layer_set_text(text_layer, "Your current Battery level is:");
  //snprintf(&buf[0], 8, "%d", cs.charge_percent); 
  //text_layer_set_text(text_layer, buf);
  //text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  //layer_add_child(window_layer, text_layer_get_layer(text_layer));
  
  text_layer2 = text_layer_create((GRect) { .origin = {0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer2, "Press select to send an email");
  text_layer_set_text_alignment(text_layer2, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer2));
  
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void handle_battery(){
  BatteryChargeState cs = battery_state_service_peek();
  if (cs.charge_percent < 95){
      DictionaryIterator *iter;
      app_message_outbox_begin(&iter);
      BatteryChargeState cs = battery_state_service_peek();
      Tuplet value = TupletInteger(1, cs.charge_percent);
      dict_write_tuplet(iter, &value);
      app_message_outbox_send();
  }
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  battery_state_service_subscribe(&handle_battery);
  const bool animated = true;
  window_stack_push(window, animated);
  app_message_open(64, 64);
}

static void deinit(void) {
  window_destroy(window);
}

static void sendAppMessage(){


}
int main(void) {
  init();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
  app_event_loop();
  deinit();
}
