#ifndef NTCHARTS_EXTENSION_H
#define NTCHARTS_EXTENSION_H

#include <ruby.h>
#include "libntcharts.h"

extern VALUE mNtcharts;
extern VALUE cSparkline;
extern VALUE cBarchart;
extern VALUE cLinechart;
extern VALUE cWavelinechart;
extern VALUE cStreamlinechart;
extern VALUE cTimeserieslinechart;
extern VALUE cStyle;

extern const rb_data_type_t sparkline_type;
extern const rb_data_type_t barchart_type;
extern const rb_data_type_t linechart_type;
extern const rb_data_type_t wavelinechart_type;
extern const rb_data_type_t streamlinechart_type;
extern const rb_data_type_t timeserieslinechart_type;
extern const rb_data_type_t style_type;

typedef struct {
  unsigned long long handle;
} ntcharts_sparkline_t;

typedef struct {
  unsigned long long handle;
} ntcharts_barchart_t;

typedef struct {
  unsigned long long handle;
} ntcharts_linechart_t;

typedef struct {
  unsigned long long handle;
} ntcharts_wavelinechart_t;

typedef struct {
  unsigned long long handle;
} ntcharts_streamlinechart_t;

typedef struct {
  unsigned long long handle;
} ntcharts_timeserieslinechart_t;

typedef struct {
  unsigned long long handle;
} ntcharts_style_t;

#define GET_SPARKLINE(self, sparkline) \
  ntcharts_sparkline_t *sparkline; \
  TypedData_Get_Struct(self, ntcharts_sparkline_t, &sparkline_type, sparkline)

#define GET_BARCHART(self, barchart) \
  ntcharts_barchart_t *barchart; \
  TypedData_Get_Struct(self, ntcharts_barchart_t, &barchart_type, barchart)

#define GET_LINECHART(self, linechart) \
  ntcharts_linechart_t *linechart; \
  TypedData_Get_Struct(self, ntcharts_linechart_t, &linechart_type, linechart)

#define GET_WAVELINECHART(self, wavelinechart) \
  ntcharts_wavelinechart_t *wavelinechart; \
  TypedData_Get_Struct(self, ntcharts_wavelinechart_t, &wavelinechart_type, wavelinechart)

#define GET_STREAMLINECHART(self, streamlinechart) \
  ntcharts_streamlinechart_t *streamlinechart; \
  TypedData_Get_Struct(self, ntcharts_streamlinechart_t, &streamlinechart_type, streamlinechart)

#define GET_TIMESERIESLINECHART(self, timeserieslinechart) \
  ntcharts_timeserieslinechart_t *timeserieslinechart; \
  TypedData_Get_Struct(self, ntcharts_timeserieslinechart_t, &timeserieslinechart_type, timeserieslinechart)

#define GET_STYLE(self, style) \
  ntcharts_style_t *style; \
  TypedData_Get_Struct(self, ntcharts_style_t, &style_type, style)

VALUE sparkline_wrap(VALUE klass, unsigned long long handle);
VALUE barchart_wrap(VALUE klass, unsigned long long handle);
VALUE style_wrap(VALUE klass, unsigned long long handle);

void Init_ntcharts_sparkline(void);
void Init_ntcharts_barchart(void);
void Init_ntcharts_linechart(void);
void Init_ntcharts_wavelinechart(void);
void Init_ntcharts_streamlinechart(void);
void Init_ntcharts_timeserieslinechart(void);
void Init_ntcharts_style(void);

#endif
