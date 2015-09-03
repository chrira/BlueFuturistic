#include <pebble.h>
#include "main.h"
  
#define KEY_COLOR 0
#define COLOR_KEY 1
#define KEY_COLORS 2
#define COLORS_KEY 3
#define KEY_COLOR1 4
#define COLOR1_KEY 5
  
char *upcase(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 0x20;
        }
    }

    return str;
}

static void line_layer_update_callback(Layer *layer, GContext* ctx) 
{
  if (persist_exists(COLORS_KEY)) 
{
  char colorname[20];
  persist_read_string(COLORS_KEY, colorname, sizeof(colorname));  
      if(strcmp(colorname, "1") == 0){  graphics_context_set_fill_color(ctx, GColorPictonBlue);}
      else if(strcmp(colorname, "2") == 0){  graphics_context_set_fill_color(ctx, GColorDukeBlue);}
      else if(strcmp(colorname, "3") == 0){  graphics_context_set_fill_color(ctx, GColorOxfordBlue);}
      else if(strcmp(colorname, "4") == 0){  graphics_context_set_fill_color(ctx, GColorWhite);}
      else if(strcmp(colorname, "5") == 0){  graphics_context_set_fill_color(ctx, GColorLightGray);}
      else if(strcmp(colorname, "6") == 0){  graphics_context_set_fill_color(ctx, GColorBlack);}
      else if(strcmp(colorname, "7") == 0){  graphics_context_set_fill_color(ctx, GColorYellow);}
      else if(strcmp(colorname, "8") == 0){  graphics_context_set_fill_color(ctx, GColorChromeYellow);}
      else if(strcmp(colorname, "9") == 0){  graphics_context_set_fill_color(ctx, GColorRed);}
      else if(strcmp(colorname, "10") == 0){  graphics_context_set_fill_color(ctx, GColorDarkCandyAppleRed);}
      else if(strcmp(colorname, "11") == 0){  graphics_context_set_fill_color(ctx, GColorBrightGreen);}
      else if(strcmp(colorname, "12") == 0){  graphics_context_set_fill_color(ctx, GColorGreen);}
      else if(strcmp(colorname, "13") == 0){  graphics_context_set_fill_color(ctx, GColorIslamicGreen);}
      else if(strcmp(colorname, "14") == 0){  graphics_context_set_fill_color(ctx, GColorVividViolet);}
      else if(strcmp(colorname, "15") == 0){  graphics_context_set_fill_color(ctx, GColorPurple);}
      else if(strcmp(colorname, "16") == 0){  graphics_context_set_fill_color(ctx, GColorImperialPurple);}
    else {  graphics_context_set_fill_color(ctx, GColorBlack);}
    
}
  else
  {  
    graphics_context_set_fill_color(ctx, GColorWhite);
  } //sets color of top block
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}  

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";
  static char buffer2[] = "XXXXXXXXX"; //Month Date
  static char buffer2A[] = "00"; //Month Date Number
  static char buffer3[] = "XXXXXXXXX"; //Day of Week

  strftime(buffer2, sizeof(buffer2), "%B", tick_time);

  strftime(buffer2A, sizeof(buffer2A), "%e", tick_time);

  upcase(buffer2);

  //strftime(buffer3, 10, "%A", tick_time);
  strftime(buffer3, sizeof(buffer3), "%A", tick_time);
  upcase(buffer3);
  
  
  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);

    text_layer_set_text(s_time_layer, buffer);
  } else 
    {
  // Use 12 hour format
  strftime(buffer, sizeof(buffer), "%I:%M", tick_time);
  text_layer_set_text(s_time_layer,buffer+(('0' == buffer[0])?1:0));  
}
    
    // Use 12 hour format
    //strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer2, buffer2);
  text_layer_set_text(s_time_layer2A, buffer2A);
  text_layer_set_text(s_time_layer3, buffer3);
}  
  
static void main_window_load(Window *window) {
  
  //Check for saved option
  //bool inverted = persist_read_bool(KEY_COLOR);
  
  g_Color = GColorDukeBlue;
  g_Color1 = GColorWhite;
  g_Color2 = GColorDarkCandyAppleRed;

  GRect line_frame = GRect(0, 0, 144, 168);//Position for top block
  s_line_layer = layer_create(line_frame);  
  layer_set_update_proc(s_line_layer, line_layer_update_callback);
  layer_add_child(window_get_root_layer(window), s_line_layer);
  
  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 42, 144, 168)); //Coordinates for Time
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, g_Color2); //Sets color for Time
  text_layer_set_text(s_time_layer, "15:45");
  
    // Improve the layout to be more like a watchface
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  
  s_time_layer2 = text_layer_create(GRect(0, 120, 100, 168)); //Coordinates for Date
  text_layer_set_background_color(s_time_layer2, GColorClear);
  text_layer_set_text_color(s_time_layer2, g_Color); //Sets color for Date
  text_layer_set_text(s_time_layer2, "AUGUST");
  
  s_time_layer2A = text_layer_create(GRect(80, 120, 64, 168)); //Coordinates for Date Number
  text_layer_set_background_color(s_time_layer2A, GColorClear);
  text_layer_set_text_color(s_time_layer2A, g_Color2); //Sets color for Date Number
  text_layer_set_text(s_time_layer2A, "15");
  
    // Improve the layout to be more like a watchface
  text_layer_set_text_alignment(s_time_layer2, GTextAlignmentCenter);

  text_layer_set_text_alignment(s_time_layer2A, GTextAlignmentCenter);


  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer2));

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer2A));


  s_time_layer3 = text_layer_create(GRect(0, 22, 144, 168)); //Coordinates for day
  text_layer_set_background_color(s_time_layer3, GColorClear);
  text_layer_set_text_color(s_time_layer3, g_Color); //Sets color for day
  text_layer_set_text(s_time_layer3, "THURSDAY");
  
    // Improve the layout to be more like a watchface
  text_layer_set_text_alignment(s_time_layer3, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer3));
  
  // Create GFont  
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TNGMONITORSA_REGULAR_75));
  s_time_font2 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TNGMONITORSA_REGULAR_25));

  
  //RESOURCE_ID_FONT_TNGMONITOR_REGULAR_75
//  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GOTHAMNIGHTS_REGULAR_75));

  if (persist_exists(COLOR_KEY)) 
{
  char colorname[20];
  persist_read_string(COLOR_KEY, colorname, sizeof(colorname));
  if(strcmp(colorname, "1") == 0){g_Color = GColorPictonBlue;}
      else if(strcmp(colorname, "2") == 0){g_Color = GColorDukeBlue;}
      else if(strcmp(colorname, "3") == 0){g_Color = GColorOxfordBlue;}
      else if(strcmp(colorname, "4") == 0){g_Color = GColorWhite;}
      else if(strcmp(colorname, "5") == 0){g_Color = GColorLightGray;}
      else if(strcmp(colorname, "6") == 0){g_Color = GColorBlack;}
      else if(strcmp(colorname, "7") == 0){g_Color = GColorYellow;}
      else if(strcmp(colorname, "8") == 0){g_Color = GColorChromeYellow;}
      else if(strcmp(colorname, "9") == 0){g_Color = GColorRed;}
      else if(strcmp(colorname, "10") == 0){g_Color = GColorDarkCandyAppleRed;}
      else if(strcmp(colorname, "11") == 0){g_Color = GColorBrightGreen;}
      else if(strcmp(colorname, "12") == 0){g_Color = GColorGreen;}
      else if(strcmp(colorname, "13") == 0){g_Color = GColorIslamicGreen;}
      else if(strcmp(colorname, "14") == 0){g_Color = GColorVividViolet;}
      else if(strcmp(colorname, "15") == 0){g_Color = GColorPurple;}
      else if(strcmp(colorname, "16") == 0){g_Color = GColorImperialPurple;}
      else {g_Color = GColorPictonBlue;}
  
  text_layer_set_text_color(s_time_layer2, g_Color); //Sets color for Day
  text_layer_set_text_color(s_time_layer3, g_Color); //Sets color for month
}
  
  if (persist_exists(COLORS_KEY)) 
{
  char colorname[20];
  persist_read_string(COLORS_KEY, colorname, sizeof(colorname));
  if(strcmp(colorname, "1") == 0){g_Color1 = GColorPictonBlue;}
      else if(strcmp(colorname, "2") == 0){g_Color1 = GColorDukeBlue;}
      else if(strcmp(colorname, "3") == 0){g_Color1 = GColorOxfordBlue;}
      else if(strcmp(colorname, "4") == 0){g_Color1 = GColorWhite;}
      else if(strcmp(colorname, "5") == 0){g_Color1 = GColorLightGray;}
      else if(strcmp(colorname, "6") == 0){g_Color1 = GColorBlack;}
      else if(strcmp(colorname, "7") == 0){g_Color1 = GColorYellow;}
      else if(strcmp(colorname, "8") == 0){g_Color1 = GColorChromeYellow;}
      else if(strcmp(colorname, "9") == 0){g_Color1 = GColorRed;}
      else if(strcmp(colorname, "10") == 0){g_Color1 = GColorDarkCandyAppleRed;}
      else if(strcmp(colorname, "11") == 0){g_Color1 = GColorBrightGreen;}
      else if(strcmp(colorname, "12") == 0){g_Color1 = GColorGreen;}
      else if(strcmp(colorname, "13") == 0){g_Color1 = GColorIslamicGreen;}
      else if(strcmp(colorname, "14") == 0){g_Color1 = GColorVividViolet;}
      else if(strcmp(colorname, "15") == 0){g_Color1 = GColorPurple;}
      else if(strcmp(colorname, "16") == 0){g_Color1 = GColorImperialPurple;}

      else {g_Color1 = GColorPictonBlue;}
    
  layer_set_update_proc(s_line_layer, line_layer_update_callback);
}

    if (persist_exists(COLOR1_KEY)) 
{
  char colorname[20];
  persist_read_string(COLOR1_KEY, colorname, sizeof(colorname));
  if(strcmp(colorname, "1") == 0){g_Color2 = GColorPictonBlue;}
      else if(strcmp(colorname, "2") == 0){g_Color2 = GColorDukeBlue;}
      else if(strcmp(colorname, "3") == 0){g_Color2 = GColorOxfordBlue;}
      else if(strcmp(colorname, "4") == 0){g_Color2 = GColorWhite;}
      else if(strcmp(colorname, "5") == 0){g_Color2 = GColorLightGray;}
      else if(strcmp(colorname, "6") == 0){g_Color2 = GColorBlack;}
      else if(strcmp(colorname, "7") == 0){g_Color2 = GColorYellow;}
      else if(strcmp(colorname, "8") == 0){g_Color2 = GColorChromeYellow;}
      else if(strcmp(colorname, "9") == 0){g_Color2 = GColorRed;}
      else if(strcmp(colorname, "10") == 0){g_Color2 = GColorDarkCandyAppleRed;}
      else if(strcmp(colorname, "11") == 0){g_Color2 = GColorBrightGreen;}
      else if(strcmp(colorname, "12") == 0){g_Color2 = GColorGreen;}
      else if(strcmp(colorname, "13") == 0){g_Color2 = GColorIslamicGreen;}
      else if(strcmp(colorname, "14") == 0){g_Color2 = GColorVividViolet;}
      else if(strcmp(colorname, "15") == 0){g_Color2 = GColorPurple;}
      else if(strcmp(colorname, "16") == 0){g_Color2 = GColorImperialPurple;}

      else {g_Color2 = GColorPictonBlue;}
    
  text_layer_set_text_color(s_time_layer, g_Color2); //Sets color for Time
  text_layer_set_text_color(s_time_layer2A, g_Color2); //Sets color for Day
}
  
// Apply to TextLayer
text_layer_set_font(s_time_layer, s_time_font);
text_layer_set_font(s_time_layer2, s_time_font2);  
text_layer_set_font(s_time_layer2A, s_time_font2);  
text_layer_set_font(s_time_layer3, s_time_font2);  
  
}

static void main_window_unload(Window *window) {
    // Destroy TextLayer
    text_layer_destroy(s_time_layer);
    text_layer_destroy(s_time_layer2);

    text_layer_destroy(s_time_layer2A);

    text_layer_destroy(s_time_layer3);

    // Unload GFont
    fonts_unload_custom_font(s_time_font);
    fonts_unload_custom_font(s_time_font2);

  // Unload blocks
    layer_destroy(s_line_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}
  
static void in_recv_handler(DictionaryIterator *iterator, void *context)
{
  //Get Tuple
  Tuple *t = dict_read_first(iterator);
  
  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
    case KEY_COLOR1:
       //It's the KEY_COLOR key
      if(strcmp(t->value->cstring, "1") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorPictonBlue;
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "2") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorDukeBlue;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }     
      else if(strcmp(t->value->cstring, "3") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorOxfordBlue;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }    
     else if(strcmp(t->value->cstring, "4") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorWhite;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }     
      else if(strcmp(t->value->cstring, "5") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorLightGray;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }   
      else if(strcmp(t->value->cstring, "6") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorBlack;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "7") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorYellow;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "8") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorChromeYellow;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "9") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorRed;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "10") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorDarkCandyAppleRed;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "11") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorBrightGreen;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "12") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorGreen;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "13") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorIslamicGreen;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "14") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorVividViolet;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "15") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorPurple;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "16") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorImperialPurple;

        persist_write_string(COLOR1_KEY, t->value->cstring);
      }
      else {g_Color2 = GColorPictonBlue;persist_write_string(COLOR1_KEY, t->value->cstring);}
      break;
    case KEY_COLORS:
       //It's the KEY_COLOR key
      if(strcmp(t->value->cstring, "1") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorPictonBlue;
        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "2") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorDukeBlue;
        
        persist_write_string(COLORS_KEY, t->value->cstring);
      }     
      else if(strcmp(t->value->cstring, "3") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorOxfordBlue;
        
        persist_write_string(COLORS_KEY, t->value->cstring);
      }    
     else if(strcmp(t->value->cstring, "4") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorWhite;
        
        persist_write_string(COLORS_KEY, t->value->cstring);
      }     
      else if(strcmp(t->value->cstring, "5") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorLightGray;
        
        persist_write_string(COLORS_KEY, t->value->cstring);
      }   
      else if(strcmp(t->value->cstring, "6") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorBlack;
        
        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "7") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorYellow;
        
        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "8") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorChromeYellow;
        
        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "9") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorRed;

        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "10") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorDarkCandyAppleRed;

        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "11") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorBrightGreen;

        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "12") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorGreen;

        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "13") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorIslamicGreen;

        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "14") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorVividViolet;

        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "15") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorPurple;

        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "16") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorImperialPurple;

        persist_write_string(COLORS_KEY, t->value->cstring);
      }
      else {g_Color1 = GColorPictonBlue;persist_write_string(COLORS_KEY, t->value->cstring);}
      break;
    case KEY_COLOR:
      //It's the KEY_COLOR key
            if(strcmp(t->value->cstring, "1") == 0)
      {
        //Set and save the color 
        g_Color = GColorPictonBlue;
        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "2") == 0)
      {
        //Set and save the color 
        g_Color = GColorDukeBlue;
        
        persist_write_string(COLOR_KEY, t->value->cstring);
      }     
      else if(strcmp(t->value->cstring, "3") == 0)
      {
        //Set and save the color 
        g_Color = GColorOxfordBlue;
        
        persist_write_string(COLOR_KEY, t->value->cstring);
      }    
     else if(strcmp(t->value->cstring, "4") == 0)
      {
        //Set and save the color 
        g_Color = GColorWhite;
        
        persist_write_string(COLOR_KEY, t->value->cstring);
      }     
      else if(strcmp(t->value->cstring, "5") == 0)
      {
        //Set and save the color 
        g_Color = GColorLightGray;
        
        persist_write_string(COLOR_KEY, t->value->cstring);
      }   
      else if(strcmp(t->value->cstring, "6") == 0)
      {
        //Set and save the color 
        g_Color = GColorBlack;
        
        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "7") == 0)
      {
        //Set and save the color 
        g_Color = GColorYellow;
        
        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "8") == 0)
      {
        //Set and save the color 
        g_Color = GColorChromeYellow;
        
        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "9") == 0)
      {
        //Set and save the color 
        g_Color = GColorRed;

        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "10") == 0)
      {
        //Set and save the color 
        g_Color = GColorDarkCandyAppleRed;

        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "11") == 0)
      {
        //Set and save the color 
        g_Color = GColorBrightGreen;

        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "12") == 0)
      {
        //Set and save the color 
        g_Color = GColorGreen;

        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "13") == 0)
      {
        //Set and save the color 
        g_Color = GColorIslamicGreen;

        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "14") == 0)
      {
        //Set and save the color 
        g_Color = GColorVividViolet;

        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "15") == 0)
      {
        //Set and save the color 
        g_Color = GColorPurple;

        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else if(strcmp(t->value->cstring, "16") == 0)
      {
        //Set and save the color 
        g_Color = GColorImperialPurple;

        persist_write_string(COLOR_KEY, t->value->cstring);
      }
      else {g_Color = GColorPictonBlue;persist_write_string(COLOR_KEY, t->value->cstring);}
      break;
          default:
      break;
    }
        // Look for next item
    t = dict_read_next(iterator);
  }
  
  text_layer_set_text_color(s_time_layer, g_Color2); //Sets color for Time
  text_layer_set_text_color(s_time_layer2, g_Color); //Sets color for Day
  text_layer_set_text_color(s_time_layer2A, g_Color2); //Sets color for Day
  text_layer_set_text_color(s_time_layer3, g_Color); //Sets color for Date
  layer_set_update_proc(s_line_layer, line_layer_update_callback);
}

static void init() {
    
  // Create main Window element and assign to pointer
  s_main_window = window_create();
  
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  app_message_register_inbox_received((AppMessageInboxReceived) in_recv_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Make sure the time is displayed from the start
  update_time();
}

static void deinit() {  
    // Destroy Window
    window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}