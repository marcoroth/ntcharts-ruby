#include "extension.h"

static void wavelinechart_free(void *pointer) {
  ntcharts_wavelinechart_t *chart = (ntcharts_wavelinechart_t *)pointer;
  if (chart->handle != 0) {
    ntcharts_wavelinechart_free(chart->handle);
  }
  xfree(chart);
}

static size_t wavelinechart_memsize(const void *pointer) {
  return sizeof(ntcharts_wavelinechart_t);
}

const rb_data_type_t wavelinechart_type = {
  .wrap_struct_name = "Ntcharts::Wavelinechart",
  .function = {
    .dmark = NULL,
    .dfree = wavelinechart_free,
    .dsize = wavelinechart_memsize,
  },
  .flags = RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE wavelinechart_alloc(VALUE klass) {
  ntcharts_wavelinechart_t *chart = ALLOC(ntcharts_wavelinechart_t);
  chart->handle = 0;
  return TypedData_Wrap_Struct(klass, &wavelinechart_type, chart);
}

static VALUE wavelinechart_initialize(VALUE self, VALUE width, VALUE height) {
  GET_WAVELINECHART(self, chart);
  chart->handle = ntcharts_wavelinechart_new(NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE wavelinechart_width(VALUE self) {
  GET_WAVELINECHART(self, chart);
  return INT2NUM(ntcharts_wavelinechart_width(chart->handle));
}

static VALUE wavelinechart_height(VALUE self) {
  GET_WAVELINECHART(self, chart);
  return INT2NUM(ntcharts_wavelinechart_height(chart->handle));
}

static VALUE wavelinechart_graph_width(VALUE self) {
  GET_WAVELINECHART(self, chart);
  return INT2NUM(ntcharts_wavelinechart_graph_width(chart->handle));
}

static VALUE wavelinechart_graph_height(VALUE self) {
  GET_WAVELINECHART(self, chart);
  return INT2NUM(ntcharts_wavelinechart_graph_height(chart->handle));
}

static VALUE wavelinechart_min_x(VALUE self) {
  GET_WAVELINECHART(self, chart);
  return DBL2NUM(ntcharts_wavelinechart_min_x(chart->handle));
}

static VALUE wavelinechart_max_x(VALUE self) {
  GET_WAVELINECHART(self, chart);
  return DBL2NUM(ntcharts_wavelinechart_max_x(chart->handle));
}

static VALUE wavelinechart_min_y(VALUE self) {
  GET_WAVELINECHART(self, chart);
  return DBL2NUM(ntcharts_wavelinechart_min_y(chart->handle));
}

static VALUE wavelinechart_max_y(VALUE self) {
  GET_WAVELINECHART(self, chart);
  return DBL2NUM(ntcharts_wavelinechart_max_y(chart->handle));
}

static VALUE wavelinechart_set_y_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_set_y_range(chart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE wavelinechart_set_view_x_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_set_view_x_range(chart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE wavelinechart_set_view_y_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_set_view_y_range(chart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE wavelinechart_resize(VALUE self, VALUE width, VALUE height) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_resize(chart->handle, NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE wavelinechart_clear(VALUE self) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_clear(chart->handle);
  return self;
}

static VALUE wavelinechart_clear_all_data(VALUE self) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_clear_all_data(chart->handle);
  return self;
}

static VALUE wavelinechart_clear_data_set(VALUE self, VALUE name) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_clear_data_set(chart->handle, StringValueCStr(name));
  return self;
}

static VALUE wavelinechart_plot(VALUE self, VALUE x, VALUE y) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_plot(chart->handle, NUM2DBL(x), NUM2DBL(y));
  return self;
}

static VALUE wavelinechart_plot_data_set(VALUE self, VALUE name, VALUE x, VALUE y) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_plot_data_set(chart->handle, StringValueCStr(name), NUM2DBL(x), NUM2DBL(y));
  return self;
}

static VALUE wavelinechart_set_styles(VALUE self, VALUE line_style, VALUE style) {
  GET_WAVELINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_wavelinechart_set_styles(chart->handle, NUM2INT(line_style), style_ptr->handle);
  return self;
}

static VALUE wavelinechart_set_data_set_styles(VALUE self, VALUE name, VALUE line_style, VALUE style) {
  GET_WAVELINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_wavelinechart_set_data_set_styles(chart->handle, StringValueCStr(name), NUM2INT(line_style), style_ptr->handle);
  return self;
}

static VALUE wavelinechart_set_style(VALUE self, VALUE style) {
  GET_WAVELINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_wavelinechart_set_style(chart->handle, style_ptr->handle);
  return self;
}

static VALUE wavelinechart_set_axis_style(VALUE self, VALUE style) {
  GET_WAVELINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_wavelinechart_set_axis_style(chart->handle, style_ptr->handle);
  return self;
}

static VALUE wavelinechart_set_label_style(VALUE self, VALUE style) {
  GET_WAVELINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_wavelinechart_set_label_style(chart->handle, style_ptr->handle);
  return self;
}

static VALUE wavelinechart_draw(VALUE self) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_draw(chart->handle);
  return self;
}

static VALUE wavelinechart_draw_all(VALUE self) {
  GET_WAVELINECHART(self, chart);
  ntcharts_wavelinechart_draw_all(chart->handle);
  return self;
}

static VALUE wavelinechart_view(VALUE self) {
  GET_WAVELINECHART(self, chart);
  char *result = ntcharts_wavelinechart_view(chart->handle);
  VALUE rb_result = rb_utf8_str_new_cstr(result);
  ntcharts_free(result);
  return rb_result;
}

static VALUE wavelinechart_render(VALUE self) {
  wavelinechart_draw(self);
  return wavelinechart_view(self);
}

static VALUE wavelinechart_render_all(VALUE self) {
  wavelinechart_draw_all(self);
  return wavelinechart_view(self);
}

static VALUE wavelinechart_to_s(VALUE self) {
  return wavelinechart_view(self);
}

void Init_ntcharts_wavelinechart(void) {
  cWavelinechart = rb_define_class_under(mNtcharts, "Wavelinechart", rb_cObject);

  rb_define_alloc_func(cWavelinechart, wavelinechart_alloc);
  rb_define_method(cWavelinechart, "initialize", wavelinechart_initialize, 2);

  rb_define_method(cWavelinechart, "width", wavelinechart_width, 0);
  rb_define_method(cWavelinechart, "height", wavelinechart_height, 0);
  rb_define_method(cWavelinechart, "graph_width", wavelinechart_graph_width, 0);
  rb_define_method(cWavelinechart, "graph_height", wavelinechart_graph_height, 0);

  rb_define_method(cWavelinechart, "min_x", wavelinechart_min_x, 0);
  rb_define_method(cWavelinechart, "max_x", wavelinechart_max_x, 0);
  rb_define_method(cWavelinechart, "min_y", wavelinechart_min_y, 0);
  rb_define_method(cWavelinechart, "max_y", wavelinechart_max_y, 0);

  rb_define_method(cWavelinechart, "set_y_range", wavelinechart_set_y_range, 2);
  rb_define_method(cWavelinechart, "set_view_x_range", wavelinechart_set_view_x_range, 2);
  rb_define_method(cWavelinechart, "set_view_y_range", wavelinechart_set_view_y_range, 2);

  rb_define_method(cWavelinechart, "resize", wavelinechart_resize, 2);
  rb_define_method(cWavelinechart, "clear", wavelinechart_clear, 0);
  rb_define_method(cWavelinechart, "clear_all_data", wavelinechart_clear_all_data, 0);
  rb_define_method(cWavelinechart, "clear_data_set", wavelinechart_clear_data_set, 1);

  rb_define_method(cWavelinechart, "plot", wavelinechart_plot, 2);
  rb_define_method(cWavelinechart, "plot_data_set", wavelinechart_plot_data_set, 3);

  rb_define_method(cWavelinechart, "set_styles", wavelinechart_set_styles, 2);
  rb_define_method(cWavelinechart, "set_data_set_styles", wavelinechart_set_data_set_styles, 3);
  rb_define_method(cWavelinechart, "_set_style", wavelinechart_set_style, 1);
  rb_define_method(cWavelinechart, "_set_axis_style", wavelinechart_set_axis_style, 1);
  rb_define_method(cWavelinechart, "_set_label_style", wavelinechart_set_label_style, 1);

  rb_define_method(cWavelinechart, "draw", wavelinechart_draw, 0);
  rb_define_method(cWavelinechart, "draw_all", wavelinechart_draw_all, 0);
  rb_define_method(cWavelinechart, "view", wavelinechart_view, 0);
  rb_define_method(cWavelinechart, "render", wavelinechart_render, 0);
  rb_define_method(cWavelinechart, "render_all", wavelinechart_render_all, 0);
  rb_define_method(cWavelinechart, "to_s", wavelinechart_to_s, 0);

  rb_define_const(cWavelinechart, "LINE_STYLE_THIN", INT2NUM(0));
  rb_define_const(cWavelinechart, "LINE_STYLE_ARC", INT2NUM(1));
}
