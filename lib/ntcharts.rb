# frozen_string_literal: true

require_relative "ntcharts/version"

begin
  major, minor, _patch = RUBY_VERSION.split(".")
  require_relative "ntcharts/#{major}.#{minor}/ntcharts"
rescue LoadError
  require_relative "ntcharts/ntcharts"
end

require_relative "ntcharts/bar_data"

module Ntcharts
  class Error < StandardError; end

  # Helper method to convert Lipgloss::Style to Ntcharts::Style
  # This allows using Lipgloss::Style objects directly with ntcharts
  def self.convert_style(style)
    return style if style.is_a?(Ntcharts::Style)

    raise ArgumentError, "Expected Ntcharts::Style or Lipgloss::Style, got #{style.class}" unless style.respond_to?(:get_foreground) && style.respond_to?(:get_background) && style.respond_to?(:bold?)

    ntcharts_style = Ntcharts::Style.new

    fg = style.get_foreground
    bg = style.get_background

    ntcharts_style = ntcharts_style.foreground(fg) if fg
    ntcharts_style = ntcharts_style.background(bg) if bg
    ntcharts_style = ntcharts_style.bold(style.bold?) if style.bold?

    ntcharts_style
  end

  module StyleSetters
    def style=(value)
      _set_style(Ntcharts.convert_style(value))
    end

    def axis_style=(value)
      _set_axis_style(Ntcharts.convert_style(value))
    end

    def label_style=(value)
      _set_label_style(Ntcharts.convert_style(value))
    end
  end

  class Barchart
    include StyleSetters

    def push(bar_data)
      data = case bar_data
             when BarData then bar_data
             when Hash then BarData.new(**bar_data)
             else raise ArgumentError, "Expected BarData or Hash"
             end

      _push(data)

      self
    end

    def push_all(bar_data_array)
      data = bar_data_array.map do |d|
        case d
        when BarData then d
        when Hash then BarData.new(**d)
        else raise ArgumentError, "Expected BarData or Hash"
        end
      end
      _push_all(data)
      self
    end

    def render
      draw
      view
    end
  end

  class Sparkline
    include StyleSetters
  end

  class Linechart
    include StyleSetters
  end

  class Wavelinechart
    include StyleSetters
  end

  class Streamlinechart
    include StyleSetters
  end

  class Timeserieslinechart
    include StyleSetters
  end
end
