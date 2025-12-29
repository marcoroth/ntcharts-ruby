# frozen_string_literal: true

module Ntcharts
  class BarValue
    attr_reader :name, :value, :style

    def initialize(name: "", value: 0.0, style: nil)
      @name = name
      @value = value.to_f
      @style = style
    end

    def to_h
      h = { name: @name, value: @value }
      h[:style_handle] = @style.handle if @style
      h
    end

    def to_json(*args)
      to_h.to_json(*args)
    end
  end

  class BarData
    attr_reader :label, :values

    def initialize(label: "", values: [])
      @label = label
      @values = values.map do |v|
        case v
        when BarValue then v
        when Hash then BarValue.new(**v)
        else raise ArgumentError, "Expected BarValue or Hash, got #{v.class}"
        end
      end
    end

    def add_value(name: "", value: 0.0, style: nil)
      @values << BarValue.new(name: name, value: value, style: style)
      self
    end

    def to_h
      { label: @label, values: @values.map(&:to_h) }
    end

    def to_json(*args)
      to_h.to_json(*args)
    end
  end
end
