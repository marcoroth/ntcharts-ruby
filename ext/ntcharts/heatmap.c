#include "extension.h"

static void heatmap_free(void *pointer) {
  ntcharts_heatmap_t *heatmap = (ntcharts_heatmap_t *)pointer;
  if (heatmap->handle != 0) {
    ntcharts_heatmap_free(heatmap->handle);
  }
  xfree(heatmap);
}

static size_t heatmap_memsize(const void *pointer) {
  return sizeof(ntcharts_heatmap_t);
}

const rb_data_type_t heatmap_type = {
  .wrap_struct_name = "Ntcharts::Heatmap",
  .function = {
    .dmark = NULL,
    .dfree = heatmap_free,
    .dsize = heatmap_memsize,
  },
  .flags = RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE heatmap_alloc(VALUE klass) {
  ntcharts_heatmap_t *heatmap = ALLOC(ntcharts_heatmap_t);
  heatmap->handle = 0;
  return TypedData_Wrap_Struct(klass, &heatmap_type, heatmap);
}

static VALUE heatmap_initialize(VALUE self, VALUE width, VALUE height) {
  GET_HEATMAP(self, heatmap);
  heatmap->handle = ntcharts_heatmap_new(NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE heatmap_width(VALUE self) {
  GET_HEATMAP(self, heatmap);
  return INT2NUM(ntcharts_heatmap_width(heatmap->handle));
}

static VALUE heatmap_height(VALUE self) {
  GET_HEATMAP(self, heatmap);
  return INT2NUM(ntcharts_heatmap_height(heatmap->handle));
}

static VALUE heatmap_graph_width(VALUE self) {
  GET_HEATMAP(self, heatmap);
  return INT2NUM(ntcharts_heatmap_graph_width(heatmap->handle));
}

static VALUE heatmap_graph_height(VALUE self) {
  GET_HEATMAP(self, heatmap);
  return INT2NUM(ntcharts_heatmap_graph_height(heatmap->handle));
}

static VALUE heatmap_min_x(VALUE self) {
  GET_HEATMAP(self, heatmap);
  return DBL2NUM(ntcharts_heatmap_min_x(heatmap->handle));
}

static VALUE heatmap_max_x(VALUE self) {
  GET_HEATMAP(self, heatmap);
  return DBL2NUM(ntcharts_heatmap_max_x(heatmap->handle));
}

static VALUE heatmap_min_y(VALUE self) {
  GET_HEATMAP(self, heatmap);
  return DBL2NUM(ntcharts_heatmap_min_y(heatmap->handle));
}

static VALUE heatmap_max_y(VALUE self) {
  GET_HEATMAP(self, heatmap);
  return DBL2NUM(ntcharts_heatmap_max_y(heatmap->handle));
}

static VALUE heatmap_set_view_x_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_set_view_x_range(heatmap->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE heatmap_set_view_y_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_set_view_y_range(heatmap->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE heatmap_set_view_xy_range(VALUE self, VALUE min_x, VALUE max_x, VALUE min_y, VALUE max_y) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_set_view_xy_range(heatmap->handle, NUM2DBL(min_x), NUM2DBL(max_x), NUM2DBL(min_y), NUM2DBL(max_y));
  return self;
}

static VALUE heatmap_set_value_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_set_value_range(heatmap->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE heatmap_resize(VALUE self, VALUE width, VALUE height) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_resize(heatmap->handle, NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE heatmap_clear(VALUE self) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_clear(heatmap->handle);
  return self;
}

static VALUE heatmap_clear_data(VALUE self) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_clear_data(heatmap->handle);
  return self;
}

static VALUE heatmap_push(VALUE self, VALUE x, VALUE y, VALUE value) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_push(heatmap->handle, NUM2DBL(x), NUM2DBL(y), NUM2DBL(value));
  return self;
}

static VALUE heatmap_push_all(VALUE self, VALUE points) {
  GET_HEATMAP(self, heatmap);
  VALUE json_class = rb_const_get(rb_cObject, rb_intern("JSON"));
  VALUE json_str = rb_funcall(json_class, rb_intern("generate"), 1, points);
  ntcharts_heatmap_push_all_json(heatmap->handle, StringValueCStr(json_str));
  return self;
}

static VALUE heatmap_push_matrix(VALUE self, VALUE matrix) {
  GET_HEATMAP(self, heatmap);
  VALUE json_class = rb_const_get(rb_cObject, rb_intern("JSON"));
  VALUE json_str = rb_funcall(json_class, rb_intern("generate"), 1, matrix);
  ntcharts_heatmap_push_matrix_json(heatmap->handle, StringValueCStr(json_str));
  return self;
}

static VALUE heatmap_set_color_scale(VALUE self, VALUE colors) {
  GET_HEATMAP(self, heatmap);
  VALUE json_class = rb_const_get(rb_cObject, rb_intern("JSON"));
  VALUE json_str = rb_funcall(json_class, rb_intern("generate"), 1, colors);
  ntcharts_heatmap_set_color_scale_json(heatmap->handle, StringValueCStr(json_str));
  return self;
}

static VALUE heatmap_set_style(VALUE self, VALUE style) {
  GET_HEATMAP(self, heatmap);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_heatmap_set_style(heatmap->handle, style_ptr->handle);
  return self;
}

static VALUE heatmap_set_axis_style(VALUE self, VALUE style) {
  GET_HEATMAP(self, heatmap);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_heatmap_set_axis_style(heatmap->handle, style_ptr->handle);
  return self;
}

static VALUE heatmap_set_label_style(VALUE self, VALUE style) {
  GET_HEATMAP(self, heatmap);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_heatmap_set_label_style(heatmap->handle, style_ptr->handle);
  return self;
}

static VALUE heatmap_set_auto_min_value(VALUE self, VALUE auto_val) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_set_auto_min_value(heatmap->handle, RTEST(auto_val) ? 1 : 0);
  return self;
}

static VALUE heatmap_set_auto_max_value(VALUE self, VALUE auto_val) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_set_auto_max_value(heatmap->handle, RTEST(auto_val) ? 1 : 0);
  return self;
}

static VALUE heatmap_draw(VALUE self) {
  GET_HEATMAP(self, heatmap);
  ntcharts_heatmap_draw(heatmap->handle);
  return self;
}

static VALUE heatmap_view(VALUE self) {
  GET_HEATMAP(self, heatmap);
  char *result = ntcharts_heatmap_view(heatmap->handle);
  VALUE rb_result = rb_utf8_str_new_cstr(result);
  ntcharts_free(result);
  return rb_result;
}

static VALUE heatmap_render(VALUE self) {
  heatmap_draw(self);
  return heatmap_view(self);
}

static VALUE heatmap_to_s(VALUE self) {
  return heatmap_view(self);
}

void Init_ntcharts_heatmap(void) {
  cHeatmap = rb_define_class_under(mNtcharts, "Heatmap", rb_cObject);

  rb_define_alloc_func(cHeatmap, heatmap_alloc);
  rb_define_method(cHeatmap, "initialize", heatmap_initialize, 2);

  rb_define_method(cHeatmap, "width", heatmap_width, 0);
  rb_define_method(cHeatmap, "height", heatmap_height, 0);
  rb_define_method(cHeatmap, "graph_width", heatmap_graph_width, 0);
  rb_define_method(cHeatmap, "graph_height", heatmap_graph_height, 0);

  rb_define_method(cHeatmap, "min_x", heatmap_min_x, 0);
  rb_define_method(cHeatmap, "max_x", heatmap_max_x, 0);
  rb_define_method(cHeatmap, "min_y", heatmap_min_y, 0);
  rb_define_method(cHeatmap, "max_y", heatmap_max_y, 0);

  rb_define_method(cHeatmap, "set_view_x_range", heatmap_set_view_x_range, 2);
  rb_define_method(cHeatmap, "set_view_y_range", heatmap_set_view_y_range, 2);
  rb_define_method(cHeatmap, "set_view_xy_range", heatmap_set_view_xy_range, 4);
  rb_define_method(cHeatmap, "set_value_range", heatmap_set_value_range, 2);

  rb_define_method(cHeatmap, "resize", heatmap_resize, 2);
  rb_define_method(cHeatmap, "clear", heatmap_clear, 0);
  rb_define_method(cHeatmap, "clear_data", heatmap_clear_data, 0);

  rb_define_method(cHeatmap, "push", heatmap_push, 3);
  rb_define_method(cHeatmap, "push_all", heatmap_push_all, 1);
  rb_define_method(cHeatmap, "push_matrix", heatmap_push_matrix, 1);

  rb_define_method(cHeatmap, "color_scale=", heatmap_set_color_scale, 1);

  rb_define_method(cHeatmap, "_set_style", heatmap_set_style, 1);
  rb_define_method(cHeatmap, "_set_axis_style", heatmap_set_axis_style, 1);
  rb_define_method(cHeatmap, "_set_label_style", heatmap_set_label_style, 1);
  rb_define_method(cHeatmap, "auto_min_value=", heatmap_set_auto_min_value, 1);
  rb_define_method(cHeatmap, "auto_max_value=", heatmap_set_auto_max_value, 1);

  rb_define_method(cHeatmap, "draw", heatmap_draw, 0);
  rb_define_method(cHeatmap, "view", heatmap_view, 0);
  rb_define_method(cHeatmap, "render", heatmap_render, 0);
  rb_define_method(cHeatmap, "to_s", heatmap_to_s, 0);
}
