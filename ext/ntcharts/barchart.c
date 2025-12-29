#include "extension.h"

static void barchart_free(void *pointer) {
  ntcharts_barchart_t *barchart = (ntcharts_barchart_t *)pointer;
  if (barchart->handle != 0) {
    ntcharts_barchart_free(barchart->handle);
  }
  xfree(barchart);
}

static size_t barchart_memsize(const void *pointer) {
  return sizeof(ntcharts_barchart_t);
}

const rb_data_type_t barchart_type = {
  .wrap_struct_name = "Ntcharts::Barchart",
  .function = {
    .dmark = NULL,
    .dfree = barchart_free,
    .dsize = barchart_memsize,
  },
  .flags = RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE barchart_alloc(VALUE klass) {
  ntcharts_barchart_t *barchart = ALLOC(ntcharts_barchart_t);
  barchart->handle = 0;
  return TypedData_Wrap_Struct(klass, &barchart_type, barchart);
}

VALUE barchart_wrap(VALUE klass, unsigned long long handle) {
  ntcharts_barchart_t *barchart = ALLOC(ntcharts_barchart_t);
  barchart->handle = handle;
  return TypedData_Wrap_Struct(klass, &barchart_type, barchart);
}

static VALUE barchart_initialize(VALUE self, VALUE width, VALUE height) {
  GET_BARCHART(self, barchart);
  barchart->handle = ntcharts_barchart_new(NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE barchart_width(VALUE self) {
  GET_BARCHART(self, barchart);
  return INT2NUM(ntcharts_barchart_width(barchart->handle));
}

static VALUE barchart_height(VALUE self) {
  GET_BARCHART(self, barchart);
  return INT2NUM(ntcharts_barchart_height(barchart->handle));
}

static VALUE barchart_max_value(VALUE self) {
  GET_BARCHART(self, barchart);
  return DBL2NUM(ntcharts_barchart_max_value(barchart->handle));
}

static VALUE barchart_scale(VALUE self) {
  GET_BARCHART(self, barchart);
  return DBL2NUM(ntcharts_barchart_scale(barchart->handle));
}

static VALUE barchart_bar_width(VALUE self) {
  GET_BARCHART(self, barchart);
  return INT2NUM(ntcharts_barchart_bar_width(barchart->handle));
}

static VALUE barchart_bar_gap(VALUE self) {
  GET_BARCHART(self, barchart);
  return INT2NUM(ntcharts_barchart_bar_gap(barchart->handle));
}

static VALUE barchart_show_axis_p(VALUE self) {
  GET_BARCHART(self, barchart);
  return ntcharts_barchart_show_axis(barchart->handle) ? Qtrue : Qfalse;
}

static VALUE barchart_horizontal_p(VALUE self) {
  GET_BARCHART(self, barchart);
  return ntcharts_barchart_horizontal(barchart->handle) ? Qtrue : Qfalse;
}

static VALUE barchart_set_max(VALUE self, VALUE max_val) {
  GET_BARCHART(self, barchart);
  ntcharts_barchart_set_max(barchart->handle, NUM2DBL(max_val));
  return self;
}

static VALUE barchart_set_bar_width(VALUE self, VALUE width) {
  GET_BARCHART(self, barchart);
  ntcharts_barchart_set_bar_width(barchart->handle, NUM2INT(width));
  return self;
}

static VALUE barchart_set_bar_gap(VALUE self, VALUE gap) {
  GET_BARCHART(self, barchart);
  ntcharts_barchart_set_bar_gap(barchart->handle, NUM2INT(gap));
  return self;
}

static VALUE barchart_set_horizontal(VALUE self, VALUE horizontal) {
  GET_BARCHART(self, barchart);
  ntcharts_barchart_set_horizontal(barchart->handle, RTEST(horizontal) ? 1 : 0);
  return self;
}

static VALUE barchart_set_show_axis(VALUE self, VALUE show_axis) {
  GET_BARCHART(self, barchart);
  ntcharts_barchart_set_show_axis(barchart->handle, RTEST(show_axis) ? 1 : 0);
  return self;
}

static VALUE barchart_set_auto_max_value(VALUE self, VALUE auto_max) {
  GET_BARCHART(self, barchart);
  ntcharts_barchart_set_auto_max_value(barchart->handle, RTEST(auto_max) ? 1 : 0);
  return self;
}

static VALUE barchart_set_auto_bar_width(VALUE self, VALUE auto_width) {
  GET_BARCHART(self, barchart);
  ntcharts_barchart_set_auto_bar_width(barchart->handle, RTEST(auto_width) ? 1 : 0);
  return self;
}

static VALUE barchart_set_axis_style(VALUE self, VALUE style) {
  GET_BARCHART(self, barchart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_barchart_set_axis_style(barchart->handle, style_ptr->handle);
  return self;
}

static VALUE barchart_set_label_style(VALUE self, VALUE style) {
  GET_BARCHART(self, barchart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_barchart_set_label_style(barchart->handle, style_ptr->handle);
  return self;
}

static VALUE barchart_resize(VALUE self, VALUE width, VALUE height) {
  GET_BARCHART(self, barchart);
  ntcharts_barchart_resize(barchart->handle, NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE barchart_clear(VALUE self) {
  GET_BARCHART(self, barchart);
  ntcharts_barchart_clear(barchart->handle);
  return self;
}

static VALUE barchart_push(VALUE self, VALUE bar_data) {
  GET_BARCHART(self, barchart);
  VALUE json_str = rb_funcall(bar_data, rb_intern("to_json"), 0);
  ntcharts_barchart_push(barchart->handle, StringValueCStr(json_str));
  return self;
}

static VALUE barchart_push_all(VALUE self, VALUE bar_data_array) {
  GET_BARCHART(self, barchart);
  Check_Type(bar_data_array, T_ARRAY);
  VALUE json_str = rb_funcall(bar_data_array, rb_intern("to_json"), 0);
  ntcharts_barchart_push_all(barchart->handle, StringValueCStr(json_str));
  return self;
}

static VALUE barchart_draw(VALUE self) {
  GET_BARCHART(self, barchart);
  ntcharts_barchart_draw(barchart->handle);
  return self;
}

static VALUE barchart_view(VALUE self) {
  GET_BARCHART(self, barchart);
  char *result = ntcharts_barchart_view(barchart->handle);
  VALUE rb_result = rb_utf8_str_new_cstr(result);
  ntcharts_free(result);
  return rb_result;
}

static VALUE barchart_to_s(VALUE self) {
  return barchart_view(self);
}

void Init_ntcharts_barchart(void) {
  cBarchart = rb_define_class_under(mNtcharts, "Barchart", rb_cObject);

  rb_define_alloc_func(cBarchart, barchart_alloc);
  rb_define_method(cBarchart, "initialize", barchart_initialize, 2);
  rb_define_method(cBarchart, "width", barchart_width, 0);
  rb_define_method(cBarchart, "height", barchart_height, 0);
  rb_define_method(cBarchart, "max_value", barchart_max_value, 0);
  rb_define_method(cBarchart, "scale", barchart_scale, 0);
  rb_define_method(cBarchart, "bar_width", barchart_bar_width, 0);
  rb_define_method(cBarchart, "bar_gap", barchart_bar_gap, 0);
  rb_define_method(cBarchart, "show_axis?", barchart_show_axis_p, 0);
  rb_define_method(cBarchart, "horizontal?", barchart_horizontal_p, 0);
  rb_define_method(cBarchart, "max=", barchart_set_max, 1);
  rb_define_method(cBarchart, "bar_width=", barchart_set_bar_width, 1);
  rb_define_method(cBarchart, "bar_gap=", barchart_set_bar_gap, 1);
  rb_define_method(cBarchart, "horizontal=", barchart_set_horizontal, 1);
  rb_define_method(cBarchart, "show_axis=", barchart_set_show_axis, 1);
  rb_define_method(cBarchart, "auto_max_value=", barchart_set_auto_max_value, 1);
  rb_define_method(cBarchart, "auto_bar_width=", barchart_set_auto_bar_width, 1);
  rb_define_method(cBarchart, "_set_axis_style", barchart_set_axis_style, 1);
  rb_define_method(cBarchart, "_set_label_style", barchart_set_label_style, 1);
  rb_define_method(cBarchart, "resize", barchart_resize, 2);
  rb_define_method(cBarchart, "clear", barchart_clear, 0);
  rb_define_method(cBarchart, "_push", barchart_push, 1);
  rb_define_method(cBarchart, "_push_all", barchart_push_all, 1);
  rb_define_method(cBarchart, "draw", barchart_draw, 0);
  rb_define_method(cBarchart, "view", barchart_view, 0);
  rb_define_method(cBarchart, "to_s", barchart_to_s, 0);
}
