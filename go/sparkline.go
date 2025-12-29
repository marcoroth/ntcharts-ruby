package main

import "C"

import (
	"encoding/json"
	"github.com/NimbleMarkets/ntcharts/sparkline"
)

//export ntcharts_sparkline_new
func ntcharts_sparkline_new(width C.int, height C.int) C.ulonglong {
	s := sparkline.New(int(width), int(height))
	return C.ulonglong(allocSparkline(&s))
}

//export ntcharts_sparkline_free
func ntcharts_sparkline_free(id C.ulonglong) {
	freeSparkline(uint64(id))
}

//export ntcharts_sparkline_width
func ntcharts_sparkline_width(id C.ulonglong) C.int {
	s := getSparkline(uint64(id))

	if s == nil {
		return 0
	}

	return C.int(s.Width())
}

//export ntcharts_sparkline_height
func ntcharts_sparkline_height(id C.ulonglong) C.int {
	s := getSparkline(uint64(id))

	if s == nil {
		return 0
	}

	return C.int(s.Height())
}

//export ntcharts_sparkline_max_value
func ntcharts_sparkline_max_value(id C.ulonglong) C.double {
	s := getSparkline(uint64(id))

	if s == nil {
		return 0
	}

	return C.double(s.MaxValue())
}

//export ntcharts_sparkline_scale
func ntcharts_sparkline_scale(id C.ulonglong) C.double {
	s := getSparkline(uint64(id))

	if s == nil {
		return 0
	}

	return C.double(s.Scale())
}

//export ntcharts_sparkline_set_max
func ntcharts_sparkline_set_max(id C.ulonglong, maxVal C.double) {
	s := getSparkline(uint64(id))

	if s == nil {
		return
	}

	s.SetMax(float64(maxVal))
}

//export ntcharts_sparkline_set_style
func ntcharts_sparkline_set_style(id C.ulonglong, styleID C.ulonglong) {
	s := getSparkline(uint64(id))

	if s == nil {
		return
	}

	style, ok := getStyle(uint64(styleID))

	if ok {
		s.Style = style
	}
}

//export ntcharts_sparkline_set_auto_max_value
func ntcharts_sparkline_set_auto_max_value(id C.ulonglong, autoVal C.int) {
	s := getSparkline(uint64(id))

	if s == nil {
		return
	}

	s.AutoMaxValue = autoVal != 0
}

//export ntcharts_sparkline_resize
func ntcharts_sparkline_resize(id C.ulonglong, width C.int, height C.int) {
	s := getSparkline(uint64(id))

	if s == nil {
		return
	}

	s.Resize(int(width), int(height))
}

//export ntcharts_sparkline_clear
func ntcharts_sparkline_clear(id C.ulonglong) {
	s := getSparkline(uint64(id))

	if s == nil {
		return
	}

	s.Clear()
}

//export ntcharts_sparkline_push
func ntcharts_sparkline_push(id C.ulonglong, value C.double) {
	s := getSparkline(uint64(id))

	if s == nil {
		return
	}

	s.Push(float64(value))
}

//export ntcharts_sparkline_push_all
func ntcharts_sparkline_push_all(id C.ulonglong, valuesJSON *C.char) {
	s := getSparkline(uint64(id))

	if s == nil {
		return
	}

	var values []float64

	if err := json.Unmarshal([]byte(C.GoString(valuesJSON)), &values); err != nil {
		return
	}

	s.PushAll(values)
}

//export ntcharts_sparkline_draw
func ntcharts_sparkline_draw(id C.ulonglong) {
	s := getSparkline(uint64(id))

	if s == nil {
		return
	}

	s.Draw()
}

//export ntcharts_sparkline_draw_columns_only
func ntcharts_sparkline_draw_columns_only(id C.ulonglong) {
	s := getSparkline(uint64(id))

	if s == nil {
		return
	}

	s.DrawColumnsOnly()
}

//export ntcharts_sparkline_draw_braille
func ntcharts_sparkline_draw_braille(id C.ulonglong) {
	s := getSparkline(uint64(id))

	if s == nil {
		return
	}

	s.DrawBraille()
}

//export ntcharts_sparkline_view
func ntcharts_sparkline_view(id C.ulonglong) *C.char {
	s := getSparkline(uint64(id))

	if s == nil {
		return C.CString("")
	}

	return C.CString(s.View())
}
