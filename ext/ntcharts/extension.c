#include "extension.h"

VALUE mNtcharts;
VALUE cSparkline;
VALUE cBarchart;
VALUE cLinechart;
VALUE cWavelinechart;
VALUE cStreamlinechart;
VALUE cTimeserieslinechart;
VALUE cHeatmap;
VALUE cStyle;

static VALUE ntcharts_upstream_version_rb(VALUE self) {
  char *version = ntcharts_upstream_version();
  VALUE rb_version = rb_utf8_str_new_cstr(version);

  ntcharts_free(version);

  return rb_version;
}

static VALUE ntcharts_version_rb(VALUE self) {
  VALUE gem_version = rb_const_get(self, rb_intern("VERSION"));
  VALUE upstream_version = ntcharts_upstream_version_rb(self);
  VALUE format_string = rb_utf8_str_new_cstr("ntcharts v%s (upstream %s) [Go native extension]");

  return rb_funcall(rb_mKernel, rb_intern("sprintf"), 3, format_string, gem_version, upstream_version);
}

__attribute__((__visibility__("default"))) void Init_ntcharts(void) {
  rb_require("json");

  mNtcharts = rb_define_module("Ntcharts");

  Init_ntcharts_sparkline();
  Init_ntcharts_barchart();
  Init_ntcharts_linechart();
  Init_ntcharts_wavelinechart();
  Init_ntcharts_streamlinechart();
  Init_ntcharts_timeserieslinechart();
  Init_ntcharts_heatmap();
  Init_ntcharts_style();

  rb_define_singleton_method(mNtcharts, "upstream_version", ntcharts_upstream_version_rb, 0);
  rb_define_singleton_method(mNtcharts, "version", ntcharts_version_rb, 0);
}
