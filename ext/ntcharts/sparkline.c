#include "extension.h"

static void sparkline_free(void *pointer) {
  ntcharts_sparkline_t *sparkline = (ntcharts_sparkline_t *)pointer;
  if (sparkline->handle != 0) {
    ntcharts_sparkline_free(sparkline->handle);
  }
  xfree(sparkline);
}

static size_t sparkline_memsize(const void *pointer) {
  return sizeof(ntcharts_sparkline_t);
}

const rb_data_type_t sparkline_type = {
  .wrap_struct_name = "Ntcharts::Sparkline",
  .function = {
    .dmark = NULL,
    .dfree = sparkline_free,
    .dsize = sparkline_memsize,
  },
  .flags = RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE sparkline_alloc(VALUE klass) {
  ntcharts_sparkline_t *sparkline = ALLOC(ntcharts_sparkline_t);
  sparkline->handle = 0;
  return TypedData_Wrap_Struct(klass, &sparkline_type, sparkline);
}

VALUE sparkline_wrap(VALUE klass, unsigned long long handle) {
  ntcharts_sparkline_t *sparkline = ALLOC(ntcharts_sparkline_t);
  sparkline->handle = handle;
  return TypedData_Wrap_Struct(klass, &sparkline_type, sparkline);
}

static VALUE sparkline_initialize(VALUE self, VALUE width, VALUE height) {
  GET_SPARKLINE(self, sparkline);
  sparkline->handle = ntcharts_sparkline_new(NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE sparkline_width(VALUE self) {
  GET_SPARKLINE(self, sparkline);
  return INT2NUM(ntcharts_sparkline_width(sparkline->handle));
}

static VALUE sparkline_height(VALUE self) {
  GET_SPARKLINE(self, sparkline);
  return INT2NUM(ntcharts_sparkline_height(sparkline->handle));
}

static VALUE sparkline_max_value(VALUE self) {
  GET_SPARKLINE(self, sparkline);
  return DBL2NUM(ntcharts_sparkline_max_value(sparkline->handle));
}

static VALUE sparkline_scale(VALUE self) {
  GET_SPARKLINE(self, sparkline);
  return DBL2NUM(ntcharts_sparkline_scale(sparkline->handle));
}

static VALUE sparkline_set_max(VALUE self, VALUE max_val) {
  GET_SPARKLINE(self, sparkline);
  ntcharts_sparkline_set_max(sparkline->handle, NUM2DBL(max_val));
  return self;
}

static VALUE sparkline_set_style(VALUE self, VALUE style) {
  GET_SPARKLINE(self, sparkline);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_sparkline_set_style(sparkline->handle, style_ptr->handle);
  return self;
}

static VALUE sparkline_set_auto_max_value(VALUE self, VALUE auto_val) {
  GET_SPARKLINE(self, sparkline);
  ntcharts_sparkline_set_auto_max_value(sparkline->handle, RTEST(auto_val) ? 1 : 0);
  return self;
}

static VALUE sparkline_resize(VALUE self, VALUE width, VALUE height) {
  GET_SPARKLINE(self, sparkline);
  ntcharts_sparkline_resize(sparkline->handle, NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE sparkline_clear(VALUE self) {
  GET_SPARKLINE(self, sparkline);
  ntcharts_sparkline_clear(sparkline->handle);
  return self;
}

static VALUE sparkline_push(VALUE self, VALUE value) {
  GET_SPARKLINE(self, sparkline);
  ntcharts_sparkline_push(sparkline->handle, NUM2DBL(value));
  return self;
}

static VALUE sparkline_push_all(VALUE self, VALUE values) {
  GET_SPARKLINE(self, sparkline);
  Check_Type(values, T_ARRAY);
  VALUE json_str = rb_funcall(values, rb_intern("to_json"), 0);
  ntcharts_sparkline_push_all(sparkline->handle, StringValueCStr(json_str));
  return self;
}

static VALUE sparkline_draw(VALUE self) {
  GET_SPARKLINE(self, sparkline);
  ntcharts_sparkline_draw(sparkline->handle);
  return self;
}

static VALUE sparkline_draw_columns_only(VALUE self) {
  GET_SPARKLINE(self, sparkline);
  ntcharts_sparkline_draw_columns_only(sparkline->handle);
  return self;
}

static VALUE sparkline_draw_braille(VALUE self) {
  GET_SPARKLINE(self, sparkline);
  ntcharts_sparkline_draw_braille(sparkline->handle);
  return self;
}

static VALUE sparkline_view(VALUE self) {
  GET_SPARKLINE(self, sparkline);
  char *result = ntcharts_sparkline_view(sparkline->handle);
  VALUE rb_result = rb_utf8_str_new_cstr(result);
  ntcharts_free(result);
  return rb_result;
}

static VALUE sparkline_to_s(VALUE self) {
  return sparkline_view(self);
}

void Init_ntcharts_sparkline(void) {
  cSparkline = rb_define_class_under(mNtcharts, "Sparkline", rb_cObject);

  rb_define_alloc_func(cSparkline, sparkline_alloc);

  rb_define_method(cSparkline, "initialize", sparkline_initialize, 2);
  rb_define_method(cSparkline, "width", sparkline_width, 0);
  rb_define_method(cSparkline, "height", sparkline_height, 0);
  rb_define_method(cSparkline, "max_value", sparkline_max_value, 0);
  rb_define_method(cSparkline, "scale", sparkline_scale, 0);
  rb_define_method(cSparkline, "max=", sparkline_set_max, 1);
  rb_define_method(cSparkline, "_set_style", sparkline_set_style, 1);
  rb_define_method(cSparkline, "auto_max_value=", sparkline_set_auto_max_value, 1);
  rb_define_method(cSparkline, "resize", sparkline_resize, 2);
  rb_define_method(cSparkline, "clear", sparkline_clear, 0);
  rb_define_method(cSparkline, "push", sparkline_push, 1);
  rb_define_method(cSparkline, "push_all", sparkline_push_all, 1);
  rb_define_method(cSparkline, "draw", sparkline_draw, 0);
  rb_define_method(cSparkline, "draw_columns_only", sparkline_draw_columns_only, 0);
  rb_define_method(cSparkline, "draw_braille", sparkline_draw_braille, 0);
  rb_define_method(cSparkline, "view", sparkline_view, 0);
  rb_define_method(cSparkline, "to_s", sparkline_to_s, 0);
}
