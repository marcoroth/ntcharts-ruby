#include "extension.h"

static void style_free(void *pointer) {
  ntcharts_style_t *style = (ntcharts_style_t *)pointer;
  if (style->handle != 0) {
    ntcharts_style_free(style->handle);
  }
  xfree(style);
}

static size_t style_memsize(const void *pointer) {
  return sizeof(ntcharts_style_t);
}

const rb_data_type_t style_type = {
  .wrap_struct_name = "Ntcharts::Style",
  .function = {
    .dmark = NULL,
    .dfree = style_free,
    .dsize = style_memsize,
  },
  .flags = RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE style_alloc(VALUE klass) {
  ntcharts_style_t *style = ALLOC(ntcharts_style_t);
  style->handle = 0;
  return TypedData_Wrap_Struct(klass, &style_type, style);
}

VALUE style_wrap(VALUE klass, unsigned long long handle) {
  ntcharts_style_t *style = ALLOC(ntcharts_style_t);
  style->handle = handle;
  return TypedData_Wrap_Struct(klass, &style_type, style);
}

static VALUE style_initialize(VALUE self) {
  GET_STYLE(self, style);
  style->handle = ntcharts_style_new();
  return self;
}

static VALUE style_foreground(VALUE self, VALUE color) {
  GET_STYLE(self, style);
  Check_Type(color, T_STRING);
  unsigned long long new_handle = ntcharts_style_foreground(style->handle, StringValueCStr(color));
  return style_wrap(rb_class_of(self), new_handle);
}

static VALUE style_background(VALUE self, VALUE color) {
  GET_STYLE(self, style);
  Check_Type(color, T_STRING);
  unsigned long long new_handle = ntcharts_style_background(style->handle, StringValueCStr(color));
  return style_wrap(rb_class_of(self), new_handle);
}

static VALUE style_bold(VALUE self, VALUE bold_val) {
  GET_STYLE(self, style);
  unsigned long long new_handle = ntcharts_style_bold(style->handle, RTEST(bold_val) ? 1 : 0);
  return style_wrap(rb_class_of(self), new_handle);
}

static VALUE style_handle(VALUE self) {
  GET_STYLE(self, style);
  return ULL2NUM(style->handle);
}

void Init_ntcharts_style(void) {
  cStyle = rb_define_class_under(mNtcharts, "Style", rb_cObject);

  rb_define_alloc_func(cStyle, style_alloc);
  rb_define_method(cStyle, "initialize", style_initialize, 0);
  rb_define_method(cStyle, "foreground", style_foreground, 1);
  rb_define_method(cStyle, "background", style_background, 1);
  rb_define_method(cStyle, "bold", style_bold, 1);
  rb_define_method(cStyle, "handle", style_handle, 0);
}
