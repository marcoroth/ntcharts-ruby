package main

/*
#include <stdlib.h>
*/
import "C"

import (
	"github.com/NimbleMarkets/ntcharts/canvas"
	"github.com/NimbleMarkets/ntcharts/canvas/runes"
	"github.com/NimbleMarkets/ntcharts/linechart/wavelinechart"
)

//export ntcharts_wavelinechart_new
func ntcharts_wavelinechart_new(width C.int, height C.int) C.ulonglong {
	m := wavelinechart.New(int(width), int(height))
	return C.ulonglong(allocWavelinechart(&m))
}

//export ntcharts_wavelinechart_free
func ntcharts_wavelinechart_free(id C.ulonglong) {
	freeWavelinechart(uint64(id))
}

//export ntcharts_wavelinechart_width
func ntcharts_wavelinechart_width(id C.ulonglong) C.int {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return 0
	}

	return C.int(w.Width())
}

//export ntcharts_wavelinechart_height
func ntcharts_wavelinechart_height(id C.ulonglong) C.int {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return 0
	}

	return C.int(w.Height())
}

//export ntcharts_wavelinechart_graph_width
func ntcharts_wavelinechart_graph_width(id C.ulonglong) C.int {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return 0
	}

	return C.int(w.GraphWidth())
}

//export ntcharts_wavelinechart_graph_height
func ntcharts_wavelinechart_graph_height(id C.ulonglong) C.int {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return 0
	}

	return C.int(w.GraphHeight())
}

//export ntcharts_wavelinechart_min_x
func ntcharts_wavelinechart_min_x(id C.ulonglong) C.double {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return 0
	}

	return C.double(w.MinX())
}

//export ntcharts_wavelinechart_max_x
func ntcharts_wavelinechart_max_x(id C.ulonglong) C.double {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return 0
	}

	return C.double(w.MaxX())
}

//export ntcharts_wavelinechart_min_y
func ntcharts_wavelinechart_min_y(id C.ulonglong) C.double {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return 0
	}

	return C.double(w.MinY())
}

//export ntcharts_wavelinechart_max_y
func ntcharts_wavelinechart_max_y(id C.ulonglong) C.double {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return 0
	}

	return C.double(w.MaxY())
}

//export ntcharts_wavelinechart_set_y_range
func ntcharts_wavelinechart_set_y_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.SetYRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_wavelinechart_set_view_x_range
func ntcharts_wavelinechart_set_view_x_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.SetViewXRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_wavelinechart_set_view_y_range
func ntcharts_wavelinechart_set_view_y_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.SetViewYRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_wavelinechart_resize
func ntcharts_wavelinechart_resize(id C.ulonglong, width C.int, height C.int) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.Resize(int(width), int(height))
	}
}

//export ntcharts_wavelinechart_clear
func ntcharts_wavelinechart_clear(id C.ulonglong) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.Clear()
	}
}

//export ntcharts_wavelinechart_clear_all_data
func ntcharts_wavelinechart_clear_all_data(id C.ulonglong) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.ClearAllData()
	}
}

//export ntcharts_wavelinechart_clear_data_set
func ntcharts_wavelinechart_clear_data_set(id C.ulonglong, name *C.char) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.ClearDataSet(C.GoString(name))
	}
}

//export ntcharts_wavelinechart_plot
func ntcharts_wavelinechart_plot(id C.ulonglong, x C.double, y C.double) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.Plot(canvas.Float64Point{X: float64(x), Y: float64(y)})
	}
}

//export ntcharts_wavelinechart_plot_data_set
func ntcharts_wavelinechart_plot_data_set(id C.ulonglong, name *C.char, x C.double, y C.double) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.PlotDataSet(C.GoString(name), canvas.Float64Point{X: float64(x), Y: float64(y)})
	}
}

//export ntcharts_wavelinechart_set_styles
func ntcharts_wavelinechart_set_styles(id C.ulonglong, lineStyle C.int, styleID C.ulonglong) {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return
	}

	ls := getWaveLineStyle(int(lineStyle))

	style, ok := getStyle(uint64(styleID))
	if ok {
		w.SetStyles(ls, style)
	}
}

//export ntcharts_wavelinechart_set_data_set_styles
func ntcharts_wavelinechart_set_data_set_styles(id C.ulonglong, name *C.char, lineStyle C.int, styleID C.ulonglong) {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return
	}

	ls := getWaveLineStyle(int(lineStyle))
	style, ok := getStyle(uint64(styleID))

	if ok {
		w.SetDataSetStyles(C.GoString(name), ls, style)
	}
}

//export ntcharts_wavelinechart_set_style
func ntcharts_wavelinechart_set_style(id C.ulonglong, styleID C.ulonglong) {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		w.Style = style
	}
}

//export ntcharts_wavelinechart_set_axis_style
func ntcharts_wavelinechart_set_axis_style(id C.ulonglong, styleID C.ulonglong) {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		w.AxisStyle = style
	}
}

//export ntcharts_wavelinechart_set_label_style
func ntcharts_wavelinechart_set_label_style(id C.ulonglong, styleID C.ulonglong) {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		w.LabelStyle = style
	}
}

//export ntcharts_wavelinechart_draw
func ntcharts_wavelinechart_draw(id C.ulonglong) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.Draw()
	}
}

//export ntcharts_wavelinechart_draw_all
func ntcharts_wavelinechart_draw_all(id C.ulonglong) {
	w := getWavelinechart(uint64(id))

	if w != nil {
		w.DrawAll()
	}
}

//export ntcharts_wavelinechart_view
func ntcharts_wavelinechart_view(id C.ulonglong) *C.char {
	w := getWavelinechart(uint64(id))

	if w == nil {
		return C.CString("")
	}

	return C.CString(w.View())
}

func getWaveLineStyle(style int) runes.LineStyle {
	switch style {
	case 0:
		return runes.ThinLineStyle
	case 1:
		return runes.ArcLineStyle
	default:
		return runes.ArcLineStyle
	}
}
