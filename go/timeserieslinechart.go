package main

/*
#include <stdlib.h>
*/
import "C"

import (
	"time"

	"github.com/NimbleMarkets/ntcharts/canvas/runes"
	"github.com/NimbleMarkets/ntcharts/linechart/timeserieslinechart"
)

//export ntcharts_timeserieslinechart_new
func ntcharts_timeserieslinechart_new(width C.int, height C.int) C.ulonglong {
	m := timeserieslinechart.New(int(width), int(height))
	return C.ulonglong(allocTimeserieslinechart(&m))
}

//export ntcharts_timeserieslinechart_free
func ntcharts_timeserieslinechart_free(id C.ulonglong) {
	freeTimeserieslinechart(uint64(id))
}

//export ntcharts_timeserieslinechart_width
func ntcharts_timeserieslinechart_width(id C.ulonglong) C.int {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return 0
	}

	return C.int(t.Width())
}

//export ntcharts_timeserieslinechart_height
func ntcharts_timeserieslinechart_height(id C.ulonglong) C.int {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return 0
	}

	return C.int(t.Height())
}

//export ntcharts_timeserieslinechart_graph_width
func ntcharts_timeserieslinechart_graph_width(id C.ulonglong) C.int {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return 0
	}

	return C.int(t.GraphWidth())
}

//export ntcharts_timeserieslinechart_graph_height
func ntcharts_timeserieslinechart_graph_height(id C.ulonglong) C.int {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return 0
	}

	return C.int(t.GraphHeight())
}

//export ntcharts_timeserieslinechart_min_x
func ntcharts_timeserieslinechart_min_x(id C.ulonglong) C.longlong {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return 0
	}

	return C.longlong(int64(t.MinX()))
}

//export ntcharts_timeserieslinechart_max_x
func ntcharts_timeserieslinechart_max_x(id C.ulonglong) C.longlong {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return 0
	}

	return C.longlong(int64(t.MaxX()))
}

//export ntcharts_timeserieslinechart_min_y
func ntcharts_timeserieslinechart_min_y(id C.ulonglong) C.double {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return 0
	}

	return C.double(t.MinY())
}

//export ntcharts_timeserieslinechart_max_y
func ntcharts_timeserieslinechart_max_y(id C.ulonglong) C.double {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return 0
	}

	return C.double(t.MaxY())
}

//export ntcharts_timeserieslinechart_set_time_range
func ntcharts_timeserieslinechart_set_time_range(id C.ulonglong, minUnix C.longlong, maxUnix C.longlong) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		minTime := time.Unix(int64(minUnix), 0)
		maxTime := time.Unix(int64(maxUnix), 0)
		t.SetTimeRange(minTime, maxTime)
	}
}

//export ntcharts_timeserieslinechart_set_y_range
func ntcharts_timeserieslinechart_set_y_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		t.SetYRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_timeserieslinechart_set_view_time_range
func ntcharts_timeserieslinechart_set_view_time_range(id C.ulonglong, minUnix C.longlong, maxUnix C.longlong) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		minTime := time.Unix(int64(minUnix), 0)
		maxTime := time.Unix(int64(maxUnix), 0)
		t.SetViewTimeRange(minTime, maxTime)
	}
}

//export ntcharts_timeserieslinechart_set_view_y_range
func ntcharts_timeserieslinechart_set_view_y_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		t.SetViewYRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_timeserieslinechart_resize
func ntcharts_timeserieslinechart_resize(id C.ulonglong, width C.int, height C.int) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		t.Resize(int(width), int(height))
	}
}

//export ntcharts_timeserieslinechart_clear
func ntcharts_timeserieslinechart_clear(id C.ulonglong) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		t.Clear()
	}
}

//export ntcharts_timeserieslinechart_clear_all_data
func ntcharts_timeserieslinechart_clear_all_data(id C.ulonglong) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		t.ClearAllData()
	}
}

//export ntcharts_timeserieslinechart_clear_data_set
func ntcharts_timeserieslinechart_clear_data_set(id C.ulonglong, name *C.char) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		t.ClearDataSet(C.GoString(name))
	}
}

//export ntcharts_timeserieslinechart_push
func ntcharts_timeserieslinechart_push(id C.ulonglong, timeUnix C.longlong, value C.double) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		tp := timeserieslinechart.TimePoint{
			Time:  time.Unix(int64(timeUnix), 0),
			Value: float64(value),
		}

		t.Push(tp)
	}
}

//export ntcharts_timeserieslinechart_push_data_set
func ntcharts_timeserieslinechart_push_data_set(id C.ulonglong, name *C.char, timeUnix C.longlong, value C.double) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		tp := timeserieslinechart.TimePoint{
			Time:  time.Unix(int64(timeUnix), 0),
			Value: float64(value),
		}

		t.PushDataSet(C.GoString(name), tp)
	}
}

//export ntcharts_timeserieslinechart_set_line_style
func ntcharts_timeserieslinechart_set_line_style(id C.ulonglong, lineStyle C.int) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		ls := getTimeseriesLineStyle(int(lineStyle))
		t.SetLineStyle(ls)
	}
}

//export ntcharts_timeserieslinechart_set_style
func ntcharts_timeserieslinechart_set_style(id C.ulonglong, styleID C.ulonglong) {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		t.SetStyle(style)
	}
}

//export ntcharts_timeserieslinechart_set_data_set_line_style
func ntcharts_timeserieslinechart_set_data_set_line_style(id C.ulonglong, name *C.char, lineStyle C.int) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		ls := getTimeseriesLineStyle(int(lineStyle))
		t.SetDataSetLineStyle(C.GoString(name), ls)
	}
}

//export ntcharts_timeserieslinechart_set_data_set_style
func ntcharts_timeserieslinechart_set_data_set_style(id C.ulonglong, name *C.char, styleID C.ulonglong) {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		t.SetDataSetStyle(C.GoString(name), style)
	}
}

//export ntcharts_timeserieslinechart_set_axis_style
func ntcharts_timeserieslinechart_set_axis_style(id C.ulonglong, styleID C.ulonglong) {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		t.AxisStyle = style
	}
}

//export ntcharts_timeserieslinechart_set_label_style
func ntcharts_timeserieslinechart_set_label_style(id C.ulonglong, styleID C.ulonglong) {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		t.LabelStyle = style
	}
}

//export ntcharts_timeserieslinechart_draw
func ntcharts_timeserieslinechart_draw(id C.ulonglong) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		t.Draw()
	}
}

//export ntcharts_timeserieslinechart_draw_all
func ntcharts_timeserieslinechart_draw_all(id C.ulonglong) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		t.DrawAll()
	}
}

//export ntcharts_timeserieslinechart_draw_braille
func ntcharts_timeserieslinechart_draw_braille(id C.ulonglong) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		t.DrawBraille()
	}
}

//export ntcharts_timeserieslinechart_draw_braille_all
func ntcharts_timeserieslinechart_draw_braille_all(id C.ulonglong) {
	t := getTimeserieslinechart(uint64(id))

	if t != nil {
		t.DrawBrailleAll()
	}
}

//export ntcharts_timeserieslinechart_view
func ntcharts_timeserieslinechart_view(id C.ulonglong) *C.char {
	t := getTimeserieslinechart(uint64(id))

	if t == nil {
		return C.CString("")
	}

	return C.CString(t.View())
}

func getTimeseriesLineStyle(style int) runes.LineStyle {
	switch style {
	case 0:
		return runes.ThinLineStyle
	case 1:
		return runes.ArcLineStyle
	default:
		return runes.ArcLineStyle
	}
}
