package main

/*
#include <stdlib.h>
*/
import "C"

import (
	"runtime/debug"
	"sync"
	"unsafe"
	"github.com/NimbleMarkets/ntcharts/barchart"
	"github.com/NimbleMarkets/ntcharts/heatmap"
	"github.com/NimbleMarkets/ntcharts/linechart"
	"github.com/NimbleMarkets/ntcharts/linechart/streamlinechart"
	"github.com/NimbleMarkets/ntcharts/linechart/timeserieslinechart"
	"github.com/NimbleMarkets/ntcharts/linechart/wavelinechart"
	"github.com/NimbleMarkets/ntcharts/sparkline"
	"github.com/charmbracelet/lipgloss"
)

var (
	nextID   uint64 = 1
	nextIDMu sync.Mutex
)

func getNextID() uint64 {
	nextIDMu.Lock()
	defer nextIDMu.Unlock()
	id := nextID
	nextID++
	return id
}

var (
	sparklines   = make(map[uint64]*sparkline.Model)
	sparklinesMu sync.RWMutex
)

func allocSparkline(s *sparkline.Model) uint64 {
	id := getNextID()
	sparklinesMu.Lock()
	sparklines[id] = s
	sparklinesMu.Unlock()
	return id
}

func getSparkline(id uint64) *sparkline.Model {
	sparklinesMu.RLock()
	defer sparklinesMu.RUnlock()
	return sparklines[id]
}

func freeSparkline(id uint64) {
	sparklinesMu.Lock()
	delete(sparklines, id)
	sparklinesMu.Unlock()
}

var (
	barcharts   = make(map[uint64]*barchart.Model)
	barchartsMu sync.RWMutex
)

func allocBarchart(b *barchart.Model) uint64 {
	id := getNextID()
	barchartsMu.Lock()
	barcharts[id] = b
	barchartsMu.Unlock()
	return id
}

func getBarchart(id uint64) *barchart.Model {
	barchartsMu.RLock()
	defer barchartsMu.RUnlock()
	return barcharts[id]
}

func freeBarchart(id uint64) {
	barchartsMu.Lock()
	delete(barcharts, id)
	barchartsMu.Unlock()
}

var (
	linecharts   = make(map[uint64]*linechart.Model)
	linechartsMu sync.RWMutex
)

func allocLinechart(l *linechart.Model) uint64 {
	id := getNextID()
	linechartsMu.Lock()
	linecharts[id] = l
	linechartsMu.Unlock()
	return id
}

func getLinechart(id uint64) *linechart.Model {
	linechartsMu.RLock()
	defer linechartsMu.RUnlock()
	return linecharts[id]
}

func freeLinechart(id uint64) {
	linechartsMu.Lock()
	delete(linecharts, id)
	linechartsMu.Unlock()
}

var (
	wavelinecharts   = make(map[uint64]*wavelinechart.Model)
	wavelinechartsMu sync.RWMutex
)

func allocWavelinechart(w *wavelinechart.Model) uint64 {
	id := getNextID()
	wavelinechartsMu.Lock()
	wavelinecharts[id] = w
	wavelinechartsMu.Unlock()
	return id
}

func getWavelinechart(id uint64) *wavelinechart.Model {
	wavelinechartsMu.RLock()
	defer wavelinechartsMu.RUnlock()
	return wavelinecharts[id]
}

func freeWavelinechart(id uint64) {
	wavelinechartsMu.Lock()
	delete(wavelinecharts, id)
	wavelinechartsMu.Unlock()
}

var (
	streamlinecharts   = make(map[uint64]*streamlinechart.Model)
	streamlinechartsMu sync.RWMutex
)

func allocStreamlinechart(s *streamlinechart.Model) uint64 {
	id := getNextID()
	streamlinechartsMu.Lock()
	streamlinecharts[id] = s
	streamlinechartsMu.Unlock()
	return id
}

func getStreamlinechart(id uint64) *streamlinechart.Model {
	streamlinechartsMu.RLock()
	defer streamlinechartsMu.RUnlock()
	return streamlinecharts[id]
}

func freeStreamlinechart(id uint64) {
	streamlinechartsMu.Lock()
	delete(streamlinecharts, id)
	streamlinechartsMu.Unlock()
}

var (
	timeserieslinecharts   = make(map[uint64]*timeserieslinechart.Model)
	timeserieslinechartsMu sync.RWMutex
)

func allocTimeserieslinechart(t *timeserieslinechart.Model) uint64 {
	id := getNextID()
	timeserieslinechartsMu.Lock()
	timeserieslinecharts[id] = t
	timeserieslinechartsMu.Unlock()
	return id
}

func getTimeserieslinechart(id uint64) *timeserieslinechart.Model {
	timeserieslinechartsMu.RLock()
	defer timeserieslinechartsMu.RUnlock()
	return timeserieslinecharts[id]
}

func freeTimeserieslinechart(id uint64) {
	timeserieslinechartsMu.Lock()
	delete(timeserieslinecharts, id)
	timeserieslinechartsMu.Unlock()
}

var (
	heatmaps   = make(map[uint64]*heatmap.Model)
	heatmapsMu sync.RWMutex
)

func allocHeatmap(h *heatmap.Model) uint64 {
	id := getNextID()
	heatmapsMu.Lock()
	heatmaps[id] = h
	heatmapsMu.Unlock()
	return id
}

func getHeatmap(id uint64) *heatmap.Model {
	heatmapsMu.RLock()
	defer heatmapsMu.RUnlock()
	return heatmaps[id]
}

func freeHeatmap(id uint64) {
	heatmapsMu.Lock()
	delete(heatmaps, id)
	heatmapsMu.Unlock()
}

var (
	styles   = make(map[uint64]lipgloss.Style)
	stylesMu sync.RWMutex
)

func allocStyle(s lipgloss.Style) uint64 {
	id := getNextID()
	stylesMu.Lock()
	styles[id] = s
	stylesMu.Unlock()
	return id
}

func getStyle(id uint64) (lipgloss.Style, bool) {
	stylesMu.RLock()
	defer stylesMu.RUnlock()
	s, ok := styles[id]
	return s, ok
}

func freeStyle(id uint64) {
	stylesMu.Lock()
	delete(styles, id)
	stylesMu.Unlock()
}

//export ntcharts_free
func ntcharts_free(pointer *C.char) {
	C.free(unsafe.Pointer(pointer))
}

//export ntcharts_upstream_version
func ntcharts_upstream_version() *C.char {
	info, ok := debug.ReadBuildInfo()

	if !ok {
		return C.CString("unknown")
	}

	for _, dep := range info.Deps {
		if dep.Path == "github.com/NimbleMarkets/ntcharts" {
			return C.CString(dep.Version)
		}
	}

	return C.CString("unknown")
}

//export ntcharts_style_new
func ntcharts_style_new() C.ulonglong {
	s := lipgloss.NewStyle()
	return C.ulonglong(allocStyle(s))
}

//export ntcharts_style_free
func ntcharts_style_free(id C.ulonglong) {
	freeStyle(uint64(id))
}

//export ntcharts_style_foreground
func ntcharts_style_foreground(id C.ulonglong, color *C.char) C.ulonglong {
	s, ok := getStyle(uint64(id))

	if !ok {
		s = lipgloss.NewStyle()
	}

	newStyle := s.Foreground(lipgloss.Color(C.GoString(color)))
	return C.ulonglong(allocStyle(newStyle))
}

//export ntcharts_style_background
func ntcharts_style_background(id C.ulonglong, color *C.char) C.ulonglong {
	s, ok := getStyle(uint64(id))

	if !ok {
		s = lipgloss.NewStyle()
	}

	newStyle := s.Background(lipgloss.Color(C.GoString(color)))
	return C.ulonglong(allocStyle(newStyle))
}

//export ntcharts_style_bold
func ntcharts_style_bold(id C.ulonglong, bold C.int) C.ulonglong {
	s, ok := getStyle(uint64(id))

	if !ok {
		s = lipgloss.NewStyle()
	}

	newStyle := s.Bold(bold != 0)
	return C.ulonglong(allocStyle(newStyle))
}

func main() {}
