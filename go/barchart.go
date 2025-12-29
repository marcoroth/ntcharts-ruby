package main

import "C"

import (
	"encoding/json"
	"github.com/NimbleMarkets/ntcharts/barchart"
	"github.com/charmbracelet/lipgloss"
)

type BarValueJSON struct {
	Name        string `json:"name"`
	Value       float64 `json:"value"`
	StyleHandle uint64 `json:"style_handle,omitempty"`
}

type BarDataJSON struct {
	Label  string         `json:"label"`
	Values []BarValueJSON `json:"values"`
}

func parseBarData(jsonStr string) barchart.BarData {
	var data BarDataJSON

	if err := json.Unmarshal([]byte(jsonStr), &data); err != nil {
		return barchart.BarData{}
	}

	barData := barchart.BarData{Label: data.Label}

	for _, v := range data.Values {
		style := lipgloss.NewStyle()

		if v.StyleHandle != 0 {
			if s, ok := getStyle(v.StyleHandle); ok {
				style = s
			}
		}

		barValue := barchart.BarValue{
			Name:  v.Name,
			Value: v.Value,
			Style: style,
		}

		barData.Values = append(barData.Values, barValue)
	}

	return barData
}

//export ntcharts_barchart_new
func ntcharts_barchart_new(width C.int, height C.int) C.ulonglong {
	b := barchart.New(int(width), int(height))
	return C.ulonglong(allocBarchart(&b))
}

//export ntcharts_barchart_free
func ntcharts_barchart_free(id C.ulonglong) {
	freeBarchart(uint64(id))
}

//export ntcharts_barchart_width
func ntcharts_barchart_width(id C.ulonglong) C.int {
	b := getBarchart(uint64(id))

	if b == nil {
		return 0
	}

	return C.int(b.Width())
}

//export ntcharts_barchart_height
func ntcharts_barchart_height(id C.ulonglong) C.int {
	b := getBarchart(uint64(id))

	if b == nil {
		return 0
	}

	return C.int(b.Height())
}

//export ntcharts_barchart_max_value
func ntcharts_barchart_max_value(id C.ulonglong) C.double {
	b := getBarchart(uint64(id))

	if b == nil {
		return 0
	}

	return C.double(b.MaxValue())
}

//export ntcharts_barchart_scale
func ntcharts_barchart_scale(id C.ulonglong) C.double {
	b := getBarchart(uint64(id))

	if b == nil {
		return 0
	}

	return C.double(b.Scale())
}

//export ntcharts_barchart_bar_width
func ntcharts_barchart_bar_width(id C.ulonglong) C.int {
	b := getBarchart(uint64(id))

	if b == nil {
		return 0
	}

	return C.int(b.BarWidth())
}

//export ntcharts_barchart_bar_gap
func ntcharts_barchart_bar_gap(id C.ulonglong) C.int {
	b := getBarchart(uint64(id))

	if b == nil {
		return 0
	}

	return C.int(b.BarGap())
}

//export ntcharts_barchart_show_axis
func ntcharts_barchart_show_axis(id C.ulonglong) C.int {
	b := getBarchart(uint64(id))

	if b == nil {
		return 0
	}

	if b.ShowAxis() {
		return 1
	}

	return 0
}

//export ntcharts_barchart_horizontal
func ntcharts_barchart_horizontal(id C.ulonglong) C.int {
	b := getBarchart(uint64(id))

	if b == nil {
		return 0
	}

	if b.Horizontal() {
		return 1
	}

	return 0
}

//export ntcharts_barchart_set_max
func ntcharts_barchart_set_max(id C.ulonglong, maxVal C.double) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	b.SetMax(float64(maxVal))
}

//export ntcharts_barchart_set_bar_width
func ntcharts_barchart_set_bar_width(id C.ulonglong, width C.int) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	b.AutoBarWidth = false
	b.SetBarWidth(int(width))
}

//export ntcharts_barchart_set_bar_gap
func ntcharts_barchart_set_bar_gap(id C.ulonglong, gap C.int) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	b.SetBarGap(int(gap))
}

//export ntcharts_barchart_set_horizontal
func ntcharts_barchart_set_horizontal(id C.ulonglong, horizontal C.int) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	b.SetHorizontal(horizontal != 0)
}

//export ntcharts_barchart_set_show_axis
func ntcharts_barchart_set_show_axis(id C.ulonglong, showAxis C.int) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	b.SetShowAxis(showAxis != 0)
}

//export ntcharts_barchart_set_auto_max_value
func ntcharts_barchart_set_auto_max_value(id C.ulonglong, autoMax C.int) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	b.AutoMaxValue = autoMax != 0
}

//export ntcharts_barchart_set_auto_bar_width
func ntcharts_barchart_set_auto_bar_width(id C.ulonglong, autoWidth C.int) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	b.AutoBarWidth = autoWidth != 0
}

//export ntcharts_barchart_set_axis_style
func ntcharts_barchart_set_axis_style(id C.ulonglong, styleID C.ulonglong) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	if style, ok := getStyle(uint64(styleID)); ok {
		b.AxisStyle = style
	}
}

//export ntcharts_barchart_set_label_style
func ntcharts_barchart_set_label_style(id C.ulonglong, styleID C.ulonglong) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	if style, ok := getStyle(uint64(styleID)); ok {
		b.LabelStyle = style
	}
}

//export ntcharts_barchart_resize
func ntcharts_barchart_resize(id C.ulonglong, width C.int, height C.int) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	b.Resize(int(width), int(height))
}

//export ntcharts_barchart_clear
func ntcharts_barchart_clear(id C.ulonglong) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	b.Clear()
}

//export ntcharts_barchart_push
func ntcharts_barchart_push(id C.ulonglong, barDataJSON *C.char) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	barData := parseBarData(C.GoString(barDataJSON))
	b.Push(barData)
}

//export ntcharts_barchart_push_all
func ntcharts_barchart_push_all(id C.ulonglong, barDataArrayJSON *C.char) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	var dataArray []BarDataJSON

	if err := json.Unmarshal([]byte(C.GoString(barDataArrayJSON)), &dataArray); err != nil {
		return
	}

	for _, data := range dataArray {
		barData := barchart.BarData{Label: data.Label}

		for _, v := range data.Values {
			style := lipgloss.NewStyle()

			if v.StyleHandle != 0 {
				if s, ok := getStyle(v.StyleHandle); ok {
					style = s
				}
			}

			barValue := barchart.BarValue{
				Name:  v.Name,
				Value: v.Value,
				Style: style,
			}

			barData.Values = append(barData.Values, barValue)
		}

		b.Push(barData)
	}
}

//export ntcharts_barchart_draw
func ntcharts_barchart_draw(id C.ulonglong) {
	b := getBarchart(uint64(id))

	if b == nil {
		return
	}

	b.Draw()
}

//export ntcharts_barchart_view
func ntcharts_barchart_view(id C.ulonglong) *C.char {
	b := getBarchart(uint64(id))

	if b == nil {
		return C.CString("")
	}

	return C.CString(b.View())
}
