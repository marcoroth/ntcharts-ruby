#include "extension.h"

static void timeserieslinechart_free(void *pointer) {
  ntcharts_timeserieslinechart_t *chart = (ntcharts_timeserieslinechart_t *)pointer;
  if (chart->handle != 0) {
    ntcharts_timeserieslinechart_free(chart->handle);
  }
  xfree(chart);
}

static size_t timeserieslinechart_memsize(const void *pointer) {
  return sizeof(ntcharts_timeserieslinechart_t);
}

const rb_data_type_t timeserieslinechart_type = {
  .wrap_struct_name = "Ntcharts::Timeserieslinechart",
  .function = {
    .dmark = NULL,
    .dfree = timeserieslinechart_free,
    .dsize = timeserieslinechart_memsize,
  },
  .flags = RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE timeserieslinechart_alloc(VALUE klass) {
  ntcharts_timeserieslinechart_t *chart = ALLOC(ntcharts_timeserieslinechart_t);
  chart->handle = 0;
  return TypedData_Wrap_Struct(klass, &timeserieslinechart_type, chart);
}

static VALUE timeserieslinechart_initialize(VALUE self, VALUE width, VALUE height) {
  GET_TIMESERIESLINECHART(self, chart);
  chart->handle = ntcharts_timeserieslinechart_new(NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE timeserieslinechart_width(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  return INT2NUM(ntcharts_timeserieslinechart_width(chart->handle));
}

static VALUE timeserieslinechart_height(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  return INT2NUM(ntcharts_timeserieslinechart_height(chart->handle));
}

static VALUE timeserieslinechart_graph_width(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  return INT2NUM(ntcharts_timeserieslinechart_graph_width(chart->handle));
}

static VALUE timeserieslinechart_graph_height(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  return INT2NUM(ntcharts_timeserieslinechart_graph_height(chart->handle));
}

static VALUE timeserieslinechart_min_x(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  long long unix_time = ntcharts_timeserieslinechart_min_x(chart->handle);
  return rb_funcall(rb_cTime, rb_intern("at"), 1, LL2NUM(unix_time));
}

static VALUE timeserieslinechart_max_x(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  long long unix_time = ntcharts_timeserieslinechart_max_x(chart->handle);
  return rb_funcall(rb_cTime, rb_intern("at"), 1, LL2NUM(unix_time));
}

static VALUE timeserieslinechart_min_y(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  return DBL2NUM(ntcharts_timeserieslinechart_min_y(chart->handle));
}

static VALUE timeserieslinechart_max_y(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  return DBL2NUM(ntcharts_timeserieslinechart_max_y(chart->handle));
}

static long long time_to_unix(VALUE time) {
  if (rb_obj_is_kind_of(time, rb_cTime)) {
    return NUM2LL(rb_funcall(time, rb_intern("to_i"), 0));
  }

  return NUM2LL(time);
}

static VALUE timeserieslinechart_set_time_range(VALUE self, VALUE min_time, VALUE max_time) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_set_time_range(chart->handle, time_to_unix(min_time), time_to_unix(max_time));
  return self;
}

static VALUE timeserieslinechart_set_y_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_set_y_range(chart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE timeserieslinechart_set_view_time_range(VALUE self, VALUE min_time, VALUE max_time) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_set_view_time_range(chart->handle, time_to_unix(min_time), time_to_unix(max_time));
  return self;
}

static VALUE timeserieslinechart_set_view_y_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_set_view_y_range(chart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE timeserieslinechart_resize(VALUE self, VALUE width, VALUE height) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_resize(chart->handle, NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE timeserieslinechart_clear(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_clear(chart->handle);
  return self;
}

static VALUE timeserieslinechart_clear_all_data(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_clear_all_data(chart->handle);
  return self;
}

static VALUE timeserieslinechart_clear_data_set(VALUE self, VALUE name) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_clear_data_set(chart->handle, StringValueCStr(name));
  return self;
}

static VALUE timeserieslinechart_push(VALUE self, VALUE time, VALUE value) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_push(chart->handle, time_to_unix(time), NUM2DBL(value));
  return self;
}

static VALUE timeserieslinechart_push_data_set(VALUE self, VALUE name, VALUE time, VALUE value) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_push_data_set(chart->handle, StringValueCStr(name), time_to_unix(time), NUM2DBL(value));
  return self;
}

static VALUE timeserieslinechart_set_line_style(VALUE self, VALUE line_style) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_set_line_style(chart->handle, NUM2INT(line_style));
  return self;
}

static VALUE timeserieslinechart_set_style(VALUE self, VALUE style) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_timeserieslinechart_set_style(chart->handle, style_ptr->handle);
  return self;
}

static VALUE timeserieslinechart_set_data_set_line_style(VALUE self, VALUE name, VALUE line_style) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_set_data_set_line_style(chart->handle, StringValueCStr(name), NUM2INT(line_style));
  return self;
}

static VALUE timeserieslinechart_set_data_set_style(VALUE self, VALUE name, VALUE style) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_timeserieslinechart_set_data_set_style(chart->handle, StringValueCStr(name), style_ptr->handle);
  return self;
}

static VALUE timeserieslinechart_set_axis_style(VALUE self, VALUE style) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_timeserieslinechart_set_axis_style(chart->handle, style_ptr->handle);
  return self;
}

static VALUE timeserieslinechart_set_label_style(VALUE self, VALUE style) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_timeserieslinechart_set_label_style(chart->handle, style_ptr->handle);
  return self;
}

static VALUE timeserieslinechart_draw(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_draw(chart->handle);
  return self;
}

static VALUE timeserieslinechart_draw_all(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_draw_all(chart->handle);
  return self;
}

static VALUE timeserieslinechart_draw_braille(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_draw_braille(chart->handle);
  return self;
}

static VALUE timeserieslinechart_draw_braille_all(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  ntcharts_timeserieslinechart_draw_braille_all(chart->handle);
  return self;
}

static VALUE timeserieslinechart_view(VALUE self) {
  GET_TIMESERIESLINECHART(self, chart);
  char *result = ntcharts_timeserieslinechart_view(chart->handle);
  VALUE rb_result = rb_utf8_str_new_cstr(result);
  ntcharts_free(result);
  return rb_result;
}

static VALUE timeserieslinechart_render(VALUE self) {
  timeserieslinechart_draw(self);
  return timeserieslinechart_view(self);
}

static VALUE timeserieslinechart_render_all(VALUE self) {
  timeserieslinechart_draw_all(self);
  return timeserieslinechart_view(self);
}

static VALUE timeserieslinechart_render_braille(VALUE self) {
  timeserieslinechart_draw_braille(self);
  return timeserieslinechart_view(self);
}

static VALUE timeserieslinechart_render_braille_all(VALUE self) {
  timeserieslinechart_draw_braille_all(self);
  return timeserieslinechart_view(self);
}

static VALUE timeserieslinechart_to_s(VALUE self) {
  return timeserieslinechart_view(self);
}

void Init_ntcharts_timeserieslinechart(void) {
  cTimeserieslinechart = rb_define_class_under(mNtcharts, "Timeserieslinechart", rb_cObject);

  rb_define_alloc_func(cTimeserieslinechart, timeserieslinechart_alloc);
  rb_define_method(cTimeserieslinechart, "initialize", timeserieslinechart_initialize, 2);

  rb_define_method(cTimeserieslinechart, "width", timeserieslinechart_width, 0);
  rb_define_method(cTimeserieslinechart, "height", timeserieslinechart_height, 0);
  rb_define_method(cTimeserieslinechart, "graph_width", timeserieslinechart_graph_width, 0);
  rb_define_method(cTimeserieslinechart, "graph_height", timeserieslinechart_graph_height, 0);

  rb_define_method(cTimeserieslinechart, "min_x", timeserieslinechart_min_x, 0);
  rb_define_method(cTimeserieslinechart, "max_x", timeserieslinechart_max_x, 0);
  rb_define_method(cTimeserieslinechart, "min_y", timeserieslinechart_min_y, 0);
  rb_define_method(cTimeserieslinechart, "max_y", timeserieslinechart_max_y, 0);

  rb_define_method(cTimeserieslinechart, "set_time_range", timeserieslinechart_set_time_range, 2);
  rb_define_method(cTimeserieslinechart, "set_y_range", timeserieslinechart_set_y_range, 2);
  rb_define_method(cTimeserieslinechart, "set_view_time_range", timeserieslinechart_set_view_time_range, 2);
  rb_define_method(cTimeserieslinechart, "set_view_y_range", timeserieslinechart_set_view_y_range, 2);

  rb_define_method(cTimeserieslinechart, "resize", timeserieslinechart_resize, 2);
  rb_define_method(cTimeserieslinechart, "clear", timeserieslinechart_clear, 0);
  rb_define_method(cTimeserieslinechart, "clear_all_data", timeserieslinechart_clear_all_data, 0);
  rb_define_method(cTimeserieslinechart, "clear_data_set", timeserieslinechart_clear_data_set, 1);

  rb_define_method(cTimeserieslinechart, "push", timeserieslinechart_push, 2);
  rb_define_method(cTimeserieslinechart, "push_data_set", timeserieslinechart_push_data_set, 3);

  rb_define_method(cTimeserieslinechart, "line_style=", timeserieslinechart_set_line_style, 1);
  rb_define_method(cTimeserieslinechart, "_set_style", timeserieslinechart_set_style, 1);
  rb_define_method(cTimeserieslinechart, "set_data_set_line_style", timeserieslinechart_set_data_set_line_style, 2);
  rb_define_method(cTimeserieslinechart, "set_data_set_style", timeserieslinechart_set_data_set_style, 2);
  rb_define_method(cTimeserieslinechart, "_set_axis_style", timeserieslinechart_set_axis_style, 1);
  rb_define_method(cTimeserieslinechart, "_set_label_style", timeserieslinechart_set_label_style, 1);

  rb_define_method(cTimeserieslinechart, "draw", timeserieslinechart_draw, 0);
  rb_define_method(cTimeserieslinechart, "draw_all", timeserieslinechart_draw_all, 0);
  rb_define_method(cTimeserieslinechart, "draw_braille", timeserieslinechart_draw_braille, 0);
  rb_define_method(cTimeserieslinechart, "draw_braille_all", timeserieslinechart_draw_braille_all, 0);
  rb_define_method(cTimeserieslinechart, "view", timeserieslinechart_view, 0);
  rb_define_method(cTimeserieslinechart, "render", timeserieslinechart_render, 0);
  rb_define_method(cTimeserieslinechart, "render_all", timeserieslinechart_render_all, 0);
  rb_define_method(cTimeserieslinechart, "render_braille", timeserieslinechart_render_braille, 0);
  rb_define_method(cTimeserieslinechart, "render_braille_all", timeserieslinechart_render_braille_all, 0);
  rb_define_method(cTimeserieslinechart, "to_s", timeserieslinechart_to_s, 0);

  rb_define_const(cTimeserieslinechart, "LINE_STYLE_THIN", INT2NUM(0));
  rb_define_const(cTimeserieslinechart, "LINE_STYLE_ARC", INT2NUM(1));
}
