#include "extension.h"

static void linechart_free(void *pointer) {
  ntcharts_linechart_t *linechart = (ntcharts_linechart_t *)pointer;
  if (linechart->handle != 0) {
    ntcharts_linechart_free(linechart->handle);
  }
  xfree(linechart);
}

static size_t linechart_memsize(const void *pointer) {
  return sizeof(ntcharts_linechart_t);
}

const rb_data_type_t linechart_type = {
  .wrap_struct_name = "Ntcharts::Linechart",
  .function = {
    .dmark = NULL,
    .dfree = linechart_free,
    .dsize = linechart_memsize,
  },
  .flags = RUBY_TYPED_FREE_IMMEDIATELY
};

static VALUE linechart_alloc(VALUE klass) {
  ntcharts_linechart_t *linechart = ALLOC(ntcharts_linechart_t);
  linechart->handle = 0;
  return TypedData_Wrap_Struct(klass, &linechart_type, linechart);
}

VALUE linechart_wrap(VALUE klass, unsigned long long handle) {
  ntcharts_linechart_t *linechart = ALLOC(ntcharts_linechart_t);
  linechart->handle = handle;
  return TypedData_Wrap_Struct(klass, &linechart_type, linechart);
}

static VALUE linechart_initialize(int argc, VALUE *argv, VALUE self) {
  GET_LINECHART(self, linechart);

  if (argc == 2) {
    // Auto-range mode: width, height only
    linechart->handle = ntcharts_linechart_new_with_auto_range(NUM2INT(argv[0]), NUM2INT(argv[1]));
  } else if (argc == 6) {
    // Full mode: width, height, min_x, max_x, min_y, max_y
    linechart->handle = ntcharts_linechart_new(
      NUM2INT(argv[0]), NUM2INT(argv[1]),
      NUM2DBL(argv[2]), NUM2DBL(argv[3]),
      NUM2DBL(argv[4]), NUM2DBL(argv[5])
    );
  } else {
    rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 2 or 6)", argc);
  }

  return self;
}

static VALUE linechart_width(VALUE self) {
  GET_LINECHART(self, linechart);
  return INT2NUM(ntcharts_linechart_width(linechart->handle));
}

static VALUE linechart_height(VALUE self) {
  GET_LINECHART(self, linechart);
  return INT2NUM(ntcharts_linechart_height(linechart->handle));
}

static VALUE linechart_graph_width(VALUE self) {
  GET_LINECHART(self, linechart);
  return INT2NUM(ntcharts_linechart_graph_width(linechart->handle));
}

static VALUE linechart_graph_height(VALUE self) {
  GET_LINECHART(self, linechart);
  return INT2NUM(ntcharts_linechart_graph_height(linechart->handle));
}

static VALUE linechart_min_x(VALUE self) {
  GET_LINECHART(self, linechart);
  return DBL2NUM(ntcharts_linechart_min_x(linechart->handle));
}

static VALUE linechart_max_x(VALUE self) {
  GET_LINECHART(self, linechart);
  return DBL2NUM(ntcharts_linechart_max_x(linechart->handle));
}

static VALUE linechart_min_y(VALUE self) {
  GET_LINECHART(self, linechart);
  return DBL2NUM(ntcharts_linechart_min_y(linechart->handle));
}

static VALUE linechart_max_y(VALUE self) {
  GET_LINECHART(self, linechart);
  return DBL2NUM(ntcharts_linechart_max_y(linechart->handle));
}

static VALUE linechart_view_min_x(VALUE self) {
  GET_LINECHART(self, linechart);
  return DBL2NUM(ntcharts_linechart_view_min_x(linechart->handle));
}

static VALUE linechart_view_max_x(VALUE self) {
  GET_LINECHART(self, linechart);
  return DBL2NUM(ntcharts_linechart_view_max_x(linechart->handle));
}

static VALUE linechart_view_min_y(VALUE self) {
  GET_LINECHART(self, linechart);
  return DBL2NUM(ntcharts_linechart_view_min_y(linechart->handle));
}

static VALUE linechart_view_max_y(VALUE self) {
  GET_LINECHART(self, linechart);
  return DBL2NUM(ntcharts_linechart_view_max_y(linechart->handle));
}

static VALUE linechart_x_step(VALUE self) {
  GET_LINECHART(self, linechart);
  return INT2NUM(ntcharts_linechart_x_step(linechart->handle));
}

static VALUE linechart_y_step(VALUE self) {
  GET_LINECHART(self, linechart);
  return INT2NUM(ntcharts_linechart_y_step(linechart->handle));
}

static VALUE linechart_set_x_step(VALUE self, VALUE step) {
  GET_LINECHART(self, linechart);
  ntcharts_linechart_set_x_step(linechart->handle, NUM2INT(step));
  return self;
}

static VALUE linechart_set_y_step(VALUE self, VALUE step) {
  GET_LINECHART(self, linechart);
  ntcharts_linechart_set_y_step(linechart->handle, NUM2INT(step));
  return self;
}

static VALUE linechart_set_x_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_LINECHART(self, linechart);
  ntcharts_linechart_set_x_range(linechart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE linechart_set_y_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_LINECHART(self, linechart);
  ntcharts_linechart_set_y_range(linechart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return self;
}

static VALUE linechart_set_view_x_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_LINECHART(self, linechart);
  int result = ntcharts_linechart_set_view_x_range(linechart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return result ? Qtrue : Qfalse;
}

static VALUE linechart_set_view_y_range(VALUE self, VALUE min_val, VALUE max_val) {
  GET_LINECHART(self, linechart);
  int result = ntcharts_linechart_set_view_y_range(linechart->handle, NUM2DBL(min_val), NUM2DBL(max_val));
  return result ? Qtrue : Qfalse;
}

static VALUE linechart_set_auto_x_range(VALUE self, VALUE auto_min, VALUE auto_max) {
  GET_LINECHART(self, linechart);
  ntcharts_linechart_set_auto_x_range(linechart->handle, RTEST(auto_min) ? 1 : 0, RTEST(auto_max) ? 1 : 0);
  return self;
}

static VALUE linechart_set_auto_y_range(VALUE self, VALUE auto_min, VALUE auto_max) {
  GET_LINECHART(self, linechart);
  ntcharts_linechart_set_auto_y_range(linechart->handle, RTEST(auto_min) ? 1 : 0, RTEST(auto_max) ? 1 : 0);
  return self;
}

static VALUE linechart_resize(VALUE self, VALUE width, VALUE height) {
  GET_LINECHART(self, linechart);
  ntcharts_linechart_resize(linechart->handle, NUM2INT(width), NUM2INT(height));
  return self;
}

static VALUE linechart_clear(VALUE self) {
  GET_LINECHART(self, linechart);
  ntcharts_linechart_clear(linechart->handle);
  return self;
}

static VALUE linechart_draw_axes(VALUE self) {
  GET_LINECHART(self, linechart);
  ntcharts_linechart_draw_axes(linechart->handle);
  return self;
}

static VALUE linechart_draw_rune(int argc, VALUE *argv, VALUE self) {
  GET_LINECHART(self, linechart);
  VALUE x, y, r, style;
  rb_scan_args(argc, argv, "31", &x, &y, &r, &style);

  int rune_val;

  if (RB_TYPE_P(r, T_STRING)) {
    const char *str = StringValueCStr(r);
    rune_val = (unsigned char)str[0];
  } else {
    rune_val = NUM2INT(r);
  }

  if (NIL_P(style)) {
    ntcharts_linechart_draw_rune(linechart->handle, NUM2DBL(x), NUM2DBL(y), rune_val);
  } else {
    ntcharts_style_t *style_ptr;
    TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
    ntcharts_linechart_draw_rune_with_style(linechart->handle, NUM2DBL(x), NUM2DBL(y), rune_val, style_ptr->handle);
  }

  return self;
}

static VALUE linechart_draw_line(int argc, VALUE *argv, VALUE self) {
  GET_LINECHART(self, linechart);
  VALUE x1, y1, x2, y2, line_style, style;
  rb_scan_args(argc, argv, "42", &x1, &y1, &x2, &y2, &line_style, &style);

  int ls = NIL_P(line_style) ? 0 : NUM2INT(line_style);

  if (NIL_P(style)) {
    ntcharts_linechart_draw_line(linechart->handle,
      NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), ls);
  } else {
    ntcharts_style_t *style_ptr;
    TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
    ntcharts_linechart_draw_line_with_style(linechart->handle,
      NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), ls, style_ptr->handle);
  }

  return self;
}

static VALUE linechart_draw_braille_line(int argc, VALUE *argv, VALUE self) {
  GET_LINECHART(self, linechart);
  VALUE x1, y1, x2, y2, style;
  rb_scan_args(argc, argv, "41", &x1, &y1, &x2, &y2, &style);

  if (NIL_P(style)) {
    ntcharts_linechart_draw_braille_line(linechart->handle,
      NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2));
  } else {
    ntcharts_style_t *style_ptr;
    TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
    ntcharts_linechart_draw_braille_line_with_style(linechart->handle,
      NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2), style_ptr->handle);
  }

  return self;
}

static VALUE linechart_set_style(VALUE self, VALUE style) {
  GET_LINECHART(self, linechart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_linechart_set_style(linechart->handle, style_ptr->handle);
  return self;
}

static VALUE linechart_set_axis_style(VALUE self, VALUE style) {
  GET_LINECHART(self, linechart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_linechart_set_axis_style(linechart->handle, style_ptr->handle);
  return self;
}

static VALUE linechart_set_label_style(VALUE self, VALUE style) {
  GET_LINECHART(self, linechart);
  ntcharts_style_t *style_ptr;
  TypedData_Get_Struct(style, ntcharts_style_t, &style_type, style_ptr);
  ntcharts_linechart_set_label_style(linechart->handle, style_ptr->handle);
  return self;
}

static VALUE linechart_view(VALUE self) {
  GET_LINECHART(self, linechart);
  char *result = ntcharts_linechart_view(linechart->handle);
  VALUE rb_result = rb_utf8_str_new_cstr(result);
  ntcharts_free(result);
  return rb_result;
}

static VALUE linechart_to_s(VALUE self) {
  return linechart_view(self);
}

void Init_ntcharts_linechart(void) {
  cLinechart = rb_define_class_under(mNtcharts, "Linechart", rb_cObject);

  rb_define_alloc_func(cLinechart, linechart_alloc);
  rb_define_method(cLinechart, "initialize", linechart_initialize, -1);

  rb_define_method(cLinechart, "width", linechart_width, 0);
  rb_define_method(cLinechart, "height", linechart_height, 0);
  rb_define_method(cLinechart, "graph_width", linechart_graph_width, 0);
  rb_define_method(cLinechart, "graph_height", linechart_graph_height, 0);

  rb_define_method(cLinechart, "min_x", linechart_min_x, 0);
  rb_define_method(cLinechart, "max_x", linechart_max_x, 0);
  rb_define_method(cLinechart, "min_y", linechart_min_y, 0);
  rb_define_method(cLinechart, "max_y", linechart_max_y, 0);
  rb_define_method(cLinechart, "view_min_x", linechart_view_min_x, 0);
  rb_define_method(cLinechart, "view_max_x", linechart_view_max_x, 0);
  rb_define_method(cLinechart, "view_min_y", linechart_view_min_y, 0);
  rb_define_method(cLinechart, "view_max_y", linechart_view_max_y, 0);

  rb_define_method(cLinechart, "x_step", linechart_x_step, 0);
  rb_define_method(cLinechart, "y_step", linechart_y_step, 0);
  rb_define_method(cLinechart, "x_step=", linechart_set_x_step, 1);
  rb_define_method(cLinechart, "y_step=", linechart_set_y_step, 1);

  rb_define_method(cLinechart, "set_x_range", linechart_set_x_range, 2);
  rb_define_method(cLinechart, "set_y_range", linechart_set_y_range, 2);
  rb_define_method(cLinechart, "set_view_x_range", linechart_set_view_x_range, 2);
  rb_define_method(cLinechart, "set_view_y_range", linechart_set_view_y_range, 2);
  rb_define_method(cLinechart, "set_auto_x_range", linechart_set_auto_x_range, 2);
  rb_define_method(cLinechart, "set_auto_y_range", linechart_set_auto_y_range, 2);

  rb_define_method(cLinechart, "resize", linechart_resize, 2);
  rb_define_method(cLinechart, "clear", linechart_clear, 0);
  rb_define_method(cLinechart, "draw_axes", linechart_draw_axes, 0);

  rb_define_method(cLinechart, "draw_rune", linechart_draw_rune, -1);
  rb_define_method(cLinechart, "draw_line", linechart_draw_line, -1);
  rb_define_method(cLinechart, "draw_braille_line", linechart_draw_braille_line, -1);

  rb_define_method(cLinechart, "_set_style", linechart_set_style, 1);
  rb_define_method(cLinechart, "_set_axis_style", linechart_set_axis_style, 1);
  rb_define_method(cLinechart, "_set_label_style", linechart_set_label_style, 1);

  rb_define_method(cLinechart, "view", linechart_view, 0);
  rb_define_method(cLinechart, "to_s", linechart_to_s, 0);

  rb_define_const(cLinechart, "LINE_STYLE_THIN", INT2NUM(0));
  rb_define_const(cLinechart, "LINE_STYLE_ARC", INT2NUM(1));
}
