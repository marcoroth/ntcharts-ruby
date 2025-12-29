package main

/*
#include <stdlib.h>
*/
import "C"

import (
	"github.com/NimbleMarkets/ntcharts/canvas"
	"github.com/NimbleMarkets/ntcharts/canvas/runes"
	"github.com/NimbleMarkets/ntcharts/linechart"
)

//export ntcharts_linechart_new
func ntcharts_linechart_new(width C.int, height C.int, minX C.double, maxX C.double, minY C.double, maxY C.double) C.ulonglong {
	m := linechart.New(int(width), int(height), float64(minX), float64(maxX), float64(minY), float64(maxY))
	return C.ulonglong(allocLinechart(&m))
}

//export ntcharts_linechart_new_with_auto_range
func ntcharts_linechart_new_with_auto_range(width C.int, height C.int) C.ulonglong {
	m := linechart.New(int(width), int(height), 0, 1, 0, 1, linechart.WithAutoXYRange())
	return C.ulonglong(allocLinechart(&m))
}

//export ntcharts_linechart_free
func ntcharts_linechart_free(id C.ulonglong) {
	freeLinechart(uint64(id))
}

//export ntcharts_linechart_width
func ntcharts_linechart_width(id C.ulonglong) C.int {
	l := getLinechart(uint64(id))
	if l == nil {
		return 0
	}
	return C.int(l.Width())
}

//export ntcharts_linechart_height
func ntcharts_linechart_height(id C.ulonglong) C.int {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.int(l.Height())
}

//export ntcharts_linechart_graph_width
func ntcharts_linechart_graph_width(id C.ulonglong) C.int {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.int(l.GraphWidth())
}

//export ntcharts_linechart_graph_height
func ntcharts_linechart_graph_height(id C.ulonglong) C.int {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.int(l.GraphHeight())
}

//export ntcharts_linechart_min_x
func ntcharts_linechart_min_x(id C.ulonglong) C.double {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.double(l.MinX())
}

//export ntcharts_linechart_max_x
func ntcharts_linechart_max_x(id C.ulonglong) C.double {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.double(l.MaxX())
}

//export ntcharts_linechart_min_y
func ntcharts_linechart_min_y(id C.ulonglong) C.double {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.double(l.MinY())
}

//export ntcharts_linechart_max_y
func ntcharts_linechart_max_y(id C.ulonglong) C.double {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.double(l.MaxY())
}

//export ntcharts_linechart_view_min_x
func ntcharts_linechart_view_min_x(id C.ulonglong) C.double {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.double(l.ViewMinX())
}

//export ntcharts_linechart_view_max_x
func ntcharts_linechart_view_max_x(id C.ulonglong) C.double {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.double(l.ViewMaxX())
}

//export ntcharts_linechart_view_min_y
func ntcharts_linechart_view_min_y(id C.ulonglong) C.double {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.double(l.ViewMinY())
}

//export ntcharts_linechart_view_max_y
func ntcharts_linechart_view_max_y(id C.ulonglong) C.double {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.double(l.ViewMaxY())
}

//export ntcharts_linechart_x_step
func ntcharts_linechart_x_step(id C.ulonglong) C.int {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.int(l.XStep())
}

//export ntcharts_linechart_y_step
func ntcharts_linechart_y_step(id C.ulonglong) C.int {
	l := getLinechart(uint64(id))

	if l == nil {
		return 0
	}

	return C.int(l.YStep())
}

//export ntcharts_linechart_set_x_step
func ntcharts_linechart_set_x_step(id C.ulonglong, step C.int) {
	l := getLinechart(uint64(id))

	if l != nil {
		l.SetXStep(int(step))
	}
}

//export ntcharts_linechart_set_y_step
func ntcharts_linechart_set_y_step(id C.ulonglong, step C.int) {
	l := getLinechart(uint64(id))

	if l != nil {
		l.SetYStep(int(step))
	}
}

//export ntcharts_linechart_set_x_range
func ntcharts_linechart_set_x_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	l := getLinechart(uint64(id))

	if l != nil {
		l.SetXRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_linechart_set_y_range
func ntcharts_linechart_set_y_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	l := getLinechart(uint64(id))

	if l != nil {
		l.SetYRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_linechart_set_view_x_range
func ntcharts_linechart_set_view_x_range(id C.ulonglong, minVal C.double, maxVal C.double) C.int {
	l := getLinechart(uint64(id))

	if l != nil && l.SetViewXRange(float64(minVal), float64(maxVal)) {
		return 1
	}

	return 0
}

//export ntcharts_linechart_set_view_y_range
func ntcharts_linechart_set_view_y_range(id C.ulonglong, minVal C.double, maxVal C.double) C.int {
	l := getLinechart(uint64(id))

	if l != nil && l.SetViewYRange(float64(minVal), float64(maxVal)) {
		return 1
	}

	return 0
}

//export ntcharts_linechart_set_auto_x_range
func ntcharts_linechart_set_auto_x_range(id C.ulonglong, autoMin C.int, autoMax C.int) {
	l := getLinechart(uint64(id))

	if l != nil {
		l.AutoMinX = autoMin != 0
		l.AutoMaxX = autoMax != 0
	}
}

//export ntcharts_linechart_set_auto_y_range
func ntcharts_linechart_set_auto_y_range(id C.ulonglong, autoMin C.int, autoMax C.int) {
	l := getLinechart(uint64(id))
	if l != nil {
		l.AutoMinY = autoMin != 0
		l.AutoMaxY = autoMax != 0
	}
}

//export ntcharts_linechart_resize
func ntcharts_linechart_resize(id C.ulonglong, width C.int, height C.int) {
	l := getLinechart(uint64(id))

	if l != nil {
		l.Resize(int(width), int(height))
	}
}

//export ntcharts_linechart_clear
func ntcharts_linechart_clear(id C.ulonglong) {
	l := getLinechart(uint64(id))

	if l != nil {
		l.Clear()
	}
}

//export ntcharts_linechart_draw_axes
func ntcharts_linechart_draw_axes(id C.ulonglong) {
	l := getLinechart(uint64(id))

	if l != nil {
		l.DrawXYAxisAndLabel()
	}
}

//export ntcharts_linechart_draw_rune
func ntcharts_linechart_draw_rune(id C.ulonglong, x C.double, y C.double, r C.int) {
	l := getLinechart(uint64(id))

	if l != nil {
		l.DrawRune(canvas.Float64Point{X: float64(x), Y: float64(y)}, rune(r))
	}
}

//export ntcharts_linechart_draw_rune_with_style
func ntcharts_linechart_draw_rune_with_style(id C.ulonglong, x C.double, y C.double, r C.int, styleID C.ulonglong) {
	l := getLinechart(uint64(id))

	if l == nil {
		return
	}

	s, ok := getStyle(uint64(styleID))

	if !ok {
		l.DrawRune(canvas.Float64Point{X: float64(x), Y: float64(y)}, rune(r))
		return
	}

	l.DrawRuneWithStyle(canvas.Float64Point{X: float64(x), Y: float64(y)}, rune(r), s)
}

//export ntcharts_linechart_draw_line
func ntcharts_linechart_draw_line(id C.ulonglong, x1 C.double, y1 C.double, x2 C.double, y2 C.double, lineStyle C.int) {
	l := getLinechart(uint64(id))

	if l != nil {
		ls := getLineStyle(int(lineStyle))
		l.DrawLine(canvas.Float64Point{X: float64(x1), Y: float64(y1)}, canvas.Float64Point{X: float64(x2), Y: float64(y2)}, ls)
	}
}

//export ntcharts_linechart_draw_line_with_style
func ntcharts_linechart_draw_line_with_style(id C.ulonglong, x1 C.double, y1 C.double, x2 C.double, y2 C.double, lineStyle C.int, styleID C.ulonglong) {
	l := getLinechart(uint64(id))

	if l == nil {
		return
	}

	ls := getLineStyle(int(lineStyle))

	s, ok := getStyle(uint64(styleID))

	if !ok {
		l.DrawLine(canvas.Float64Point{X: float64(x1), Y: float64(y1)}, canvas.Float64Point{X: float64(x2), Y: float64(y2)}, ls)
		return
	}

	l.DrawLineWithStyle(canvas.Float64Point{X: float64(x1), Y: float64(y1)}, canvas.Float64Point{X: float64(x2), Y: float64(y2)}, ls, s)
}

//export ntcharts_linechart_draw_braille_line
func ntcharts_linechart_draw_braille_line(id C.ulonglong, x1 C.double, y1 C.double, x2 C.double, y2 C.double) {
	l := getLinechart(uint64(id))

	if l != nil {
		l.DrawBrailleLine(canvas.Float64Point{X: float64(x1), Y: float64(y1)}, canvas.Float64Point{X: float64(x2), Y: float64(y2)})
	}
}

//export ntcharts_linechart_draw_braille_line_with_style
func ntcharts_linechart_draw_braille_line_with_style(id C.ulonglong, x1 C.double, y1 C.double, x2 C.double, y2 C.double, styleID C.ulonglong) {
	l := getLinechart(uint64(id))

	if l == nil {
		return
	}

	s, ok := getStyle(uint64(styleID))

	if !ok {
		l.DrawBrailleLine(canvas.Float64Point{X: float64(x1), Y: float64(y1)}, canvas.Float64Point{X: float64(x2), Y: float64(y2)})
		return
	}

	l.DrawBrailleLineWithStyle(canvas.Float64Point{X: float64(x1), Y: float64(y1)}, canvas.Float64Point{X: float64(x2), Y: float64(y2)}, s)
}

//export ntcharts_linechart_set_style
func ntcharts_linechart_set_style(id C.ulonglong, styleID C.ulonglong) {
	l := getLinechart(uint64(id))

	if l == nil {
		return
	}

	s, ok := getStyle(uint64(styleID))

	if ok {
		l.Style = s
	}
}

//export ntcharts_linechart_set_axis_style
func ntcharts_linechart_set_axis_style(id C.ulonglong, styleID C.ulonglong) {
	l := getLinechart(uint64(id))

	if l == nil {
		return
	}

	s, ok := getStyle(uint64(styleID))

	if ok {
		l.AxisStyle = s
	}
}

//export ntcharts_linechart_set_label_style
func ntcharts_linechart_set_label_style(id C.ulonglong, styleID C.ulonglong) {
	l := getLinechart(uint64(id))

	if l == nil {
		return
	}

	s, ok := getStyle(uint64(styleID))

	if ok {
		l.LabelStyle = s
	}
}

//export ntcharts_linechart_view
func ntcharts_linechart_view(id C.ulonglong) *C.char {
	l := getLinechart(uint64(id))

	if l == nil {
		return C.CString("")
	}

	return C.CString(l.View())
}

const (
	LineStyleThin = 0
	LineStyleArc  = 1
)

func getLineStyle(style int) runes.LineStyle {
	switch style {
	case LineStyleThin:
		return runes.ThinLineStyle
	case LineStyleArc:
		return runes.ArcLineStyle
	default:
		return runes.ThinLineStyle
	}
}
