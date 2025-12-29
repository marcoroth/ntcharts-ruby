package main

/*
#include <stdlib.h>
*/
import "C"

import (
	"github.com/NimbleMarkets/ntcharts/canvas/runes"
	"github.com/NimbleMarkets/ntcharts/linechart/streamlinechart"
)

//export ntcharts_streamlinechart_new
func ntcharts_streamlinechart_new(width C.int, height C.int) C.ulonglong {
	m := streamlinechart.New(int(width), int(height))
	return C.ulonglong(allocStreamlinechart(&m))
}

//export ntcharts_streamlinechart_free
func ntcharts_streamlinechart_free(id C.ulonglong) {
	freeStreamlinechart(uint64(id))
}

//export ntcharts_streamlinechart_width
func ntcharts_streamlinechart_width(id C.ulonglong) C.int {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return 0
	}

	return C.int(s.Width())
}

//export ntcharts_streamlinechart_height
func ntcharts_streamlinechart_height(id C.ulonglong) C.int {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return 0
	}

	return C.int(s.Height())
}

//export ntcharts_streamlinechart_graph_width
func ntcharts_streamlinechart_graph_width(id C.ulonglong) C.int {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return 0
	}

	return C.int(s.GraphWidth())
}

//export ntcharts_streamlinechart_graph_height
func ntcharts_streamlinechart_graph_height(id C.ulonglong) C.int {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return 0
	}

	return C.int(s.GraphHeight())
}

//export ntcharts_streamlinechart_min_y
func ntcharts_streamlinechart_min_y(id C.ulonglong) C.double {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return 0
	}

	return C.double(s.MinY())
}

//export ntcharts_streamlinechart_max_y
func ntcharts_streamlinechart_max_y(id C.ulonglong) C.double {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return 0
	}

	return C.double(s.MaxY())
}

//export ntcharts_streamlinechart_set_y_range
func ntcharts_streamlinechart_set_y_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	s := getStreamlinechart(uint64(id))

	if s != nil {
		s.SetYRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_streamlinechart_set_view_y_range
func ntcharts_streamlinechart_set_view_y_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	s := getStreamlinechart(uint64(id))

	if s != nil {
		s.SetViewYRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_streamlinechart_resize
func ntcharts_streamlinechart_resize(id C.ulonglong, width C.int, height C.int) {
	s := getStreamlinechart(uint64(id))

	if s != nil {
		s.Resize(int(width), int(height))
	}
}

//export ntcharts_streamlinechart_clear
func ntcharts_streamlinechart_clear(id C.ulonglong) {
	s := getStreamlinechart(uint64(id))

	if s != nil {
		s.Clear()
	}
}

//export ntcharts_streamlinechart_clear_data
func ntcharts_streamlinechart_clear_data(id C.ulonglong) {
	s := getStreamlinechart(uint64(id))

	if s != nil {
		s.ClearAllData()
	}
}

//export ntcharts_streamlinechart_push
func ntcharts_streamlinechart_push(id C.ulonglong, value C.double) {
	s := getStreamlinechart(uint64(id))

	if s != nil {
		s.Push(float64(value))
	}
}

//export ntcharts_streamlinechart_set_styles
func ntcharts_streamlinechart_set_styles(id C.ulonglong, lineStyle C.int, styleID C.ulonglong) {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return
	}

	ls := getStreamLineStyle(int(lineStyle))
	style, ok := getStyle(uint64(styleID))

	if ok {
		s.SetStyles(ls, style)
	} else {
		s.SetStyles(ls, s.Style)
	}
}

//export ntcharts_streamlinechart_set_style
func ntcharts_streamlinechart_set_style(id C.ulonglong, styleID C.ulonglong) {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return
	}
	style, ok := getStyle(uint64(styleID))

	if ok {
		s.Style = style
	}
}

//export ntcharts_streamlinechart_set_axis_style
func ntcharts_streamlinechart_set_axis_style(id C.ulonglong, styleID C.ulonglong) {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		s.AxisStyle = style
	}
}

//export ntcharts_streamlinechart_set_label_style
func ntcharts_streamlinechart_set_label_style(id C.ulonglong, styleID C.ulonglong) {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return
	}
	style, ok := getStyle(uint64(styleID))

	if ok {
		s.LabelStyle = style
	}
}

//export ntcharts_streamlinechart_draw
func ntcharts_streamlinechart_draw(id C.ulonglong) {
	s := getStreamlinechart(uint64(id))

	if s != nil {
		s.Draw()
	}
}

//export ntcharts_streamlinechart_view
func ntcharts_streamlinechart_view(id C.ulonglong) *C.char {
	s := getStreamlinechart(uint64(id))

	if s == nil {
		return C.CString("")
	}

	return C.CString(s.View())
}

func getStreamLineStyle(style int) runes.LineStyle {
	switch style {
	case 0:
		return runes.ThinLineStyle
	case 1:
		return runes.ArcLineStyle
	default:
		return runes.ArcLineStyle
	}
}
