# frozen_string_literal: true

require_relative "test_helper"

class NtchartsTest < Minitest::Spec
  it "has a version_number" do
    refute_nil ::Ntcharts::VERSION
  end
end
