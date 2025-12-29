#include "extension.h"

static void streamlinechart_free(void *pointer) {
  ntcharts_streamlinechart_t *chart = (ntcharts_streamlinechart_t *)pointer;
  if (chart->handle != 0) {
    ntcharts_streamlinechart_free(chart->handle);
  }
  xfree(chart);
}

static size_t streamlinechart_memsize(const void *pointer) {
  return sizeof(ntcharts_streamlinechart_t);
}

const rb_data_type_t streamlinechart_type = {
  .wrap_struct_name = "Ntcharts::Streamlinechart",
  .function = {
    .dmark = NULL,
    .dfree = streamlinechart_free,
    .dsize = streamlinechart_memsize,
  },
  .flags = RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE streamlinechart_alloc(VALUE klass) {
  ntcharts_streamlinechart_t *chart = ALLOC(ntcharts_streamlinechart_t);
  chart->handle = 0;
  return TypedData_Wrap_Struct(klass, &streamlinechart_type, chart);
}

static VALUE streamlinechart_initialize(VALUE self, VALUE width, VALUE height) {
  GET_STREAMLINECHART(self, chart);
  chart->handle = ntcharts_streamlinechart_new(NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE streamlinechart_width(VALUE self) {
  GET_STREAMLINECHART(self, chart);
  return INT2NUM(ntcharts_streamlinechart_width(chart->handle));
}

static VALUE streamlinechart_height(VALUE self) {
  GET_STREAMLINECHART(self, chart);
  return INT2NUM(ntcharts_streamlinechart_height(chart->handle));
}

static VALUE streamlinechart_graph_width(VALUE self) {
  GET_STREAMLINECHART(self, chart);
  return INT2NUM(ntcharts_streamlinechart_graph_width(chart->handle));
}

static VALUE streamlinechart_graph_height(VALUE self) {
  GET_STREAMLINECHART(self, chart);
  return INT2NUM(ntcharts_streamlinechart_graph_height(chart->handle));
}

static VALUE streamlinechart_min_y(VALUE self) {
  GET_STREAMLINECHART(self, chart);
  return DBL2NUM(ntcharts_streamlinechart_min_y(chart->handle));
}

static VALUE streamlinechart_max_y(VALUE self) {
  GET_STREAMLINECHART(self, chart);
  return DBL2NUM(ntcharts_streamlinechart_max_y(chart->handle));
}

static VALUE streamlinechart_set_y_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_STREAMLINECHART(self, chart);
  ntcharts_streamlinechart_set_y_range(chart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE streamlinechart_set_view_y_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_STREAMLINECHART(self, chart);
  ntcharts_streamlinechart_set_view_y_range(chart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE streamlinechart_resize(VALUE self, VALUE width, VALUE height) {
  GET_STREAMLINECHART(self, chart);
  ntcharts_streamlinechart_resize(chart->handle, NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE streamlinechart_clear(VALUE self) {
  GET_STREAMLINECHART(self, chart);
  ntcharts_streamlinechart_clear(chart->handle);
  return self;
}

static VALUE streamlinechart_clear_data(VALUE self) {
  GET_STREAMLINECHART(self, chart);
  ntcharts_streamlinechart_clear_data(chart->handle);
  return self;
}

static VALUE streamlinechart_push(VALUE self, VALUE value) {
  GET_STREAMLINECHART(self, chart);
  ntcharts_streamlinechart_push(chart->handle, NUM2DBL(value));
  return self;
}

static VALUE streamlinechart_set_style(VALUE self, VALUE style) {
  GET_STREAMLINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_streamlinechart_set_style(chart->handle, style_ptr->handle);
  return self;
}

static VALUE streamlinechart_set_axis_style(VALUE self, VALUE style) {
  GET_STREAMLINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_streamlinechart_set_axis_style(chart->handle, style_ptr->handle);
  return self;
}

static VALUE streamlinechart_set_label_style(VALUE self, VALUE style) {
  GET_STREAMLINECHART(self, chart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_streamlinechart_set_label_style(chart->handle, style_ptr->handle);
  return self;
}

static VALUE streamlinechart_draw(VALUE self) {
  GET_STREAMLINECHART(self, chart);
  ntcharts_streamlinechart_draw(chart->handle);
  return self;
}

static VALUE streamlinechart_view(VALUE self) {
  GET_STREAMLINECHART(self, chart);
  char *result = ntcharts_streamlinechart_view(chart->handle);
  VALUE rb_result = rb_utf8_str_new_cstr(result);
  ntcharts_free(result);
  return rb_result;
}

static VALUE streamlinechart_render(VALUE self) {
  streamlinechart_draw(self);
  return streamlinechart_view(self);
}

static VALUE streamlinechart_to_s(VALUE self) {
  return streamlinechart_view(self);
}

void Init_ntcharts_streamlinechart(void) {
  cStreamlinechart = rb_define_class_under(mNtcharts, "Streamlinechart", rb_cObject);

  rb_define_alloc_func(cStreamlinechart, streamlinechart_alloc);
  rb_define_method(cStreamlinechart, "initialize", streamlinechart_initialize, 2);

  rb_define_method(cStreamlinechart, "width", streamlinechart_width, 0);
  rb_define_method(cStreamlinechart, "height", streamlinechart_height, 0);
  rb_define_method(cStreamlinechart, "graph_width", streamlinechart_graph_width, 0);
  rb_define_method(cStreamlinechart, "graph_height", streamlinechart_graph_height, 0);

  rb_define_method(cStreamlinechart, "min_y", streamlinechart_min_y, 0);
  rb_define_method(cStreamlinechart, "max_y", streamlinechart_max_y, 0);

  rb_define_method(cStreamlinechart, "set_y_range", streamlinechart_set_y_range, 2);
  rb_define_method(cStreamlinechart, "set_view_y_range", streamlinechart_set_view_y_range, 2);

  rb_define_method(cStreamlinechart, "resize", streamlinechart_resize, 2);
  rb_define_method(cStreamlinechart, "clear", streamlinechart_clear, 0);
  rb_define_method(cStreamlinechart, "clear_data", streamlinechart_clear_data, 0);
  rb_define_method(cStreamlinechart, "push", streamlinechart_push, 1);

  rb_define_method(cStreamlinechart, "_set_style", streamlinechart_set_style, 1);
  rb_define_method(cStreamlinechart, "_set_axis_style", streamlinechart_set_axis_style, 1);
  rb_define_method(cStreamlinechart, "_set_label_style", streamlinechart_set_label_style, 1);

  rb_define_method(cStreamlinechart, "draw", streamlinechart_draw, 0);
  rb_define_method(cStreamlinechart, "view", streamlinechart_view, 0);
  rb_define_method(cStreamlinechart, "render", streamlinechart_render, 0);
  rb_define_method(cStreamlinechart, "to_s", streamlinechart_to_s, 0);

  rb_define_const(cStreamlinechart, "LINE_STYLE_THIN", INT2NUM(0));
  rb_define_const(cStreamlinechart, "LINE_STYLE_ARC", INT2NUM(1));
}
