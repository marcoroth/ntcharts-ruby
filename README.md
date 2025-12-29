<div align="center">
  <h1>Nimble Terminal Charts for Ruby</h1>
  <h4>Terminal Charts for Beautiful Data Visualization</h4>

  <p>
    <a href="https://rubygems.org/gems/ntcharts"><img alt="Gem Version" src="https://img.shields.io/gem/v/ntcharts"></a>
    <a href="https://github.com/marcoroth/ntcharts-ruby/blob/main/LICENSE.txt"><img alt="License" src="https://img.shields.io/github/license/marcoroth/ntcharts-ruby"></a>
  </p>

  <p>Ruby bindings for <a href="https://github.com/NimbleMarkets/ntcharts">NimbleMarkets/ntcharts</a>.<br/>Render beautiful charts directly in your terminal. Built with TUIs in mind.</p>
</div>

## Installation

**Add to your Gemfile:**

```ruby
gem "ntcharts"
```

**Or install directly:**

```bash
gem install ntcharts
```

## Usage

### Sparkline

**Compact time-series visualization:**

```ruby
require "ntcharts"

chart = Ntcharts::Sparkline.new(40, 6)
[1, 4, 2, 7, 3, 9, 5, 8, 2, 6].each { |v| chart.push(v) }
chart.draw
puts chart.view
```

**Styled sparkline with lipgloss:**

```ruby
require "lipgloss"

style = Lipgloss::Style.new.foreground("#FF6B6B")
chart = Ntcharts::Sparkline.new(40, 6)
chart.style = style  # Accepts Lipgloss::Style or Ntcharts::Style

[5, 3, 7, 2, 9, 4, 6, 1, 8, 3].each { |v| chart.push(v) }
chart.draw_braille
puts chart.view
```

### Barchart

**Horizontal and vertical bar charts:**

```ruby
chart = Ntcharts::Barchart.new(50, 12)

chart.push(label: "Go", values: [{ value: 85, style: style }])
chart.push(label: "Ruby", values: [{ value: 92, style: style }])
chart.push(label: "Python", values: [{ value: 78, style: style }])

puts chart.render
```

**Stacked bar segments:**

```ruby
chart.push(
  label: "Sales",
  values: [
    { value: 30, style: red_style },
    { value: 45, style: green_style },
    { value: 25, style: blue_style }
  ]
)
```

### LineChart

**X/Y coordinate plotting:**

```ruby
chart = Ntcharts::Linechart.new(50, 12, 0.0, 10.0, 0.0, 10.0)

(0..10).each do |i|
  x = i.to_f
  y = Math.sin(i * 0.5) * 4 + 5
  chart.draw_rune(x, y, "*")
end

chart.draw_axes
puts chart.view
```

**Braille lines for smooth curves:**

```ruby
chart = Ntcharts::Linechart.new(60, 15, 0.0, 30.0, -5.0, 10.0)

points = (0..30).map { |i| [i.to_f, Math.sin(i * 0.2) * 4 + 3] }

points.each_cons(2) do |(x1, y1), (x2, y2)|
  chart.draw_braille_line(x1, y1, x2, y2)
end

chart.draw_axes
puts chart.view
```

#### Line styles

**Thin lines (box-drawing characters)**

```ruby
chart.draw_line(0, 0, 10, 10, Ntcharts::Linechart::LINE_STYLE_THIN)
```

**Arc lines (curved connections)**
```ruby
chart.draw_line(0, 0, 10, 10, Ntcharts::Linechart::LINE_STYLE_ARC)
```

### WaveLineChart

**Multiple named datasets:**

```ruby
chart = Ntcharts::Wavelinechart.new(60, 15)

(0..40).each { |i| chart.plot(i.to_f, Math.sin(i * 0.15) * 5 + 5) }

(0..40).each do |i|
  chart.plot_data_set("series_a", i.to_f, Math.cos(i * 0.15) * 4 + 5)
  chart.plot_data_set("series_b", i.to_f, Math.sin(i * 0.1) * 3 + 5)
end

chart.draw_all
puts chart.view
```

### StreamLineChart

**Real-time scrolling data:**

```ruby
chart = Ntcharts::Streamlinechart.new(60, 12)
chart.style = Lipgloss::Style.new.foreground("#00D4FF")

loop do
  value = Math.sin(Time.now.to_f) * 4 + 5
  chart.push(value)

  system("clear")
  puts chart.render
  sleep 0.1
end
```

### TimeSeriesLineChart

**Time-based X-axis with date labels:**

```ruby
chart = Ntcharts::Timeserieslinechart.new(70, 15)

now = Time.now
(0..60).each do |i|
  time = now - (60 - i) * 60
  value = Math.sin(i * 0.1) * 10 + 50
  chart.push(time, value)
end

chart.draw_braille
puts chart.view
```

### Styling

**All charts support lipgloss styling:**

```ruby
require "lipgloss"

chart_style = Lipgloss::Style.new.foreground("#FF6B6B")
axis_style = Lipgloss::Style.new.foreground("#666666")
label_style = Lipgloss::Style.new.foreground("#888888")

chart.style = chart_style
chart.axis_style = axis_style
chart.label_style = label_style
```

**Or use Ntcharts::Style directly:**

```ruby
style = Ntcharts::Style.new
  .foreground("#00FF00")
  .background("#000033")
  .bold(true)

chart.style = style
```

## Chart Types

| Chart | Description | Key Features |
|-------|-------------|--------------|
| `Sparkline` | Compact time-series | Column and braille rendering modes |
| `Barchart` | Bar charts | Horizontal/vertical, stacked segments |
| `Linechart` | Base X/Y plotting | Points, lines, braille, custom runes |
| `Wavelinechart` | Multi-dataset lines | Named datasets, arc/thin line styles |
| `Streamlinechart` | Scrolling streams | Push data, auto-scroll right-to-left |
| `Timeserieslinechart` | Time-based charts | Ruby Time objects, date labels |

## Sparkline Methods

| Method | Description |
|--------|-------------|
| `push(value)` | Add a data point |
| `draw` | Render with column characters |
| `draw_braille` | Render with braille dots |
| `view` | Get rendered string |
| `style=` | Set chart style |
| `max=` | Set maximum value |
| `auto_max_value=` | Enable/disable auto-scaling |
| `resize(width, height)` | Resize the chart |
| `clear` | Clear all data |

## Barchart Methods

| Method | Description |
|--------|-------------|
| `push(bar_data)` | Add a bar (Hash or BarData) |
| `push_all(array)` | Add multiple bars |
| `render` | Draw and return view |
| `horizontal=` | Set horizontal orientation |
| `bar_width=` | Set bar width |
| `bar_gap=` | Set gap between bars |
| `show_axis=` | Show/hide axis |
| `axis_style=` | Set axis style |
| `label_style=` | Set label style |

## LineChart Methods

| Method | Description |
|--------|-------------|
| `draw_rune(x, y, char, [style])` | Draw character at point |
| `draw_line(x1, y1, x2, y2, line_style, [style])` | Draw line segment |
| `draw_braille_line(x1, y1, x2, y2, [style])` | Draw braille line |
| `draw_axes` | Draw X and Y axes |
| `view` | Get rendered string |
| `set_x_range(min, max)` | Set X data range |
| `set_y_range(min, max)` | Set Y data range |
| `x_step=` / `y_step=` | Set axis step (0 to hide) |

## StreamLineChart Methods

| Method | Description |
|--------|-------------|
| `push(value)` | Add value (scrolls left) |
| `render` | Draw and return view |
| `set_y_range(min, max)` | Set Y range |
| `style=` | Set line style |
| `clear_data` | Clear data points |

## TimeSeriesLineChart Methods

| Method | Description |
|--------|-------------|
| `push(time, value)` | Add time point |
| `push_data_set(name, time, value)` | Add to named dataset |
| `draw` / `draw_all` | Render default/all datasets |
| `draw_braille` / `draw_braille_all` | Braille rendering |
| `set_time_range(min, max)` | Set time range |
| `line_style=` | Set line style (THIN/ARC) |

## Line Style Constants

Available on `Linechart`, `Wavelinechart`, `Streamlinechart`, `Timeserieslinechart`:

| Constant | Description |
|----------|-------------|
| `LINE_STYLE_THIN` | Box-drawing characters |
| `LINE_STYLE_ARC` | Curved arc connections |

## Development

**Requirements:**
- Go 1.23+
- Ruby 3.2+

**Install dependencies:**

```bash
bundle install
```

**Build the Go library and compile the extension:**

```bash
bundle exec rake go:build
bundle exec rake compile
```

**Run demos:**

```bash
./demo/sparkline
./demo/barchart
./demo/linechart
./demo/wavelinechart
./demo/streamlinechart
./demo/timeserieslinechart
./demo/streaming
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/marcoroth/ntcharts-ruby.

## License

The gem is available as open source under the terms of the MIT License.

## Acknowledgments

This gem wraps [NimbleMarkets/ntcharts](https://github.com/NimbleMarkets/ntcharts), which builds on the excellent [Charm](https://charm.sh) ecosystem including [lipgloss](https://github.com/charmbracelet/lipgloss).
