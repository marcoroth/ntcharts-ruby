package main

/*
#include <stdlib.h>
*/
import "C"

import (
	"encoding/json"
	"github.com/NimbleMarkets/ntcharts/heatmap"
	"github.com/charmbracelet/lipgloss"
)

//export ntcharts_heatmap_new
func ntcharts_heatmap_new(width C.int, height C.int) C.ulonglong {
	m := heatmap.New(int(width), int(height), heatmap.WithAutoValueRange())
	return C.ulonglong(allocHeatmap(&m))
}

//export ntcharts_heatmap_free
func ntcharts_heatmap_free(id C.ulonglong) {
	freeHeatmap(uint64(id))
}

//export ntcharts_heatmap_width
func ntcharts_heatmap_width(id C.ulonglong) C.int {
	h := getHeatmap(uint64(id))

	if h == nil {
		return 0
	}

	return C.int(h.Width())
}

//export ntcharts_heatmap_height
func ntcharts_heatmap_height(id C.ulonglong) C.int {
	h := getHeatmap(uint64(id))

	if h == nil {
		return 0
	}

	return C.int(h.Height())
}

//export ntcharts_heatmap_graph_width
func ntcharts_heatmap_graph_width(id C.ulonglong) C.int {
	h := getHeatmap(uint64(id))

	if h == nil {
		return 0
	}

	return C.int(h.GraphWidth())
}

//export ntcharts_heatmap_graph_height
func ntcharts_heatmap_graph_height(id C.ulonglong) C.int {
	h := getHeatmap(uint64(id))

	if h == nil {
		return 0
	}

	return C.int(h.GraphHeight())
}

//export ntcharts_heatmap_min_x
func ntcharts_heatmap_min_x(id C.ulonglong) C.double {
	h := getHeatmap(uint64(id))

	if h == nil {
		return 0
	}

	return C.double(h.MinX())
}

//export ntcharts_heatmap_max_x
func ntcharts_heatmap_max_x(id C.ulonglong) C.double {
	h := getHeatmap(uint64(id))

	if h == nil {
		return 0
	}

	return C.double(h.MaxX())
}

//export ntcharts_heatmap_min_y
func ntcharts_heatmap_min_y(id C.ulonglong) C.double {
	h := getHeatmap(uint64(id))

	if h == nil {
		return 0
	}

	return C.double(h.MinY())
}

//export ntcharts_heatmap_max_y
func ntcharts_heatmap_max_y(id C.ulonglong) C.double {
	h := getHeatmap(uint64(id))

	if h == nil {
		return 0
	}

	return C.double(h.MaxY())
}

//export ntcharts_heatmap_set_view_x_range
func ntcharts_heatmap_set_view_x_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	h := getHeatmap(uint64(id))

	if h != nil {
		h.SetViewXRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_heatmap_set_view_y_range
func ntcharts_heatmap_set_view_y_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	h := getHeatmap(uint64(id))

	if h != nil {
		h.SetViewYRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_heatmap_set_view_xy_range
func ntcharts_heatmap_set_view_xy_range(id C.ulonglong, minX C.double, maxX C.double, minY C.double, maxY C.double) {
	h := getHeatmap(uint64(id))

	if h != nil {
		h.SetViewXYRange(float64(minX), float64(maxX), float64(minY), float64(maxY))
	}
}

//export ntcharts_heatmap_set_value_range
func ntcharts_heatmap_set_value_range(id C.ulonglong, minVal C.double, maxVal C.double) {
	h := getHeatmap(uint64(id))

	if h != nil {
		h.SetValueRange(float64(minVal), float64(maxVal))
	}
}

//export ntcharts_heatmap_resize
func ntcharts_heatmap_resize(id C.ulonglong, width C.int, height C.int) {
	h := getHeatmap(uint64(id))

	if h != nil {
		h.Resize(int(width), int(height))
	}
}

//export ntcharts_heatmap_clear
func ntcharts_heatmap_clear(id C.ulonglong) {
	h := getHeatmap(uint64(id))

	if h != nil {
		h.Clear()
	}
}

//export ntcharts_heatmap_clear_data
func ntcharts_heatmap_clear_data(id C.ulonglong) {
	h := getHeatmap(uint64(id))

	if h != nil {
		h.ClearData()
	}
}

//export ntcharts_heatmap_push
func ntcharts_heatmap_push(id C.ulonglong, x C.double, y C.double, value C.double) {
	h := getHeatmap(uint64(id))

	if h != nil {
		pt := heatmap.NewHeatPoint(float64(x), float64(y), float64(value))
		h.Push(pt)
	}
}

//export ntcharts_heatmap_push_all_json
func ntcharts_heatmap_push_all_json(id C.ulonglong, jsonData *C.char) {
	h := getHeatmap(uint64(id))

	if h == nil {
		return
	}

	type HeatPointJSON struct {
		X float64 `json:"x"`
		Y float64 `json:"y"`
		V float64 `json:"v"`
	}

	var points []HeatPointJSON

	if err := json.Unmarshal([]byte(C.GoString(jsonData)), &points); err != nil {
		return
	}

	for _, p := range points {
		pt := heatmap.NewHeatPoint(p.X, p.Y, p.V)
		h.Push(pt)
	}
}

//export ntcharts_heatmap_push_matrix_json
func ntcharts_heatmap_push_matrix_json(id C.ulonglong, jsonData *C.char) {
	h := getHeatmap(uint64(id))

	if h == nil {
		return
	}

	var matrix [][]float64

	if err := json.Unmarshal([]byte(C.GoString(jsonData)), &matrix); err != nil {
		return
	}

	h.PushAllMatrixRow(matrix)
}

//export ntcharts_heatmap_set_color_scale_json
func ntcharts_heatmap_set_color_scale_json(id C.ulonglong, jsonColors *C.char) {
	h := getHeatmap(uint64(id))

	if h == nil {
		return
	}

	var colorStrings []string

	if err := json.Unmarshal([]byte(C.GoString(jsonColors)), &colorStrings); err != nil {
		return
	}

	colors := make([]lipgloss.Color, len(colorStrings))

	for i, cs := range colorStrings {
		colors[i] = lipgloss.Color(cs)
	}

	h.ColorScale = colors
}

//export ntcharts_heatmap_set_style
func ntcharts_heatmap_set_style(id C.ulonglong, styleID C.ulonglong) {
	h := getHeatmap(uint64(id))

	if h == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		h.Style = style
	}
}

//export ntcharts_heatmap_set_axis_style
func ntcharts_heatmap_set_axis_style(id C.ulonglong, styleID C.ulonglong) {
	h := getHeatmap(uint64(id))

	if h == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		h.AxisStyle = style
	}
}

//export ntcharts_heatmap_set_label_style
func ntcharts_heatmap_set_label_style(id C.ulonglong, styleID C.ulonglong) {
	h := getHeatmap(uint64(id))

	if h == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		h.LabelStyle = style
	}
}

//export ntcharts_heatmap_set_auto_min_value
func ntcharts_heatmap_set_auto_min_value(id C.ulonglong, autoVal C.int) {
	h := getHeatmap(uint64(id))

	if h != nil {
		h.AutoMinValue = autoVal != 0
	}
}

//export ntcharts_heatmap_set_auto_max_value
func ntcharts_heatmap_set_auto_max_value(id C.ulonglong, autoVal C.int) {
	h := getHeatmap(uint64(id))

	if h != nil {
		h.AutoMaxValue = autoVal != 0
	}
}

//export ntcharts_heatmap_draw
func ntcharts_heatmap_draw(id C.ulonglong) {
	h := getHeatmap(uint64(id))

	if h != nil {
		h.Draw()
	}
}

//export ntcharts_heatmap_view
func ntcharts_heatmap_view(id C.ulonglong) *C.char {
	h := getHeatmap(uint64(id))

	if h == nil {
		return C.CString("")
	}

	return C.CString(h.View())
}
