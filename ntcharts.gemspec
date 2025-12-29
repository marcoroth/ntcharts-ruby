# frozen_string_literal: true

require_relative "lib/ntcharts/version"

Gem::Specification.new do |spec|
  spec.name = "ntcharts"
  spec.version = Ntcharts::VERSION
  spec.authors = ["Marco Roth"]
  spec.email = ["marco.roth@intergga.ch"]

  spec.summary = "Ruby wrapper for NimbleMarkets' ntcharts terminal charting library."
  spec.description = spec.summary
  spec.homepage = "https://github.com/marcoroth/ntcharts-ruby"
  spec.license = "MIT"
  spec.required_ruby_version = ">= 3.2.0"

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/marcoroth/ntcharts-ruby"
  spec.metadata["changelog_uri"] = "https://github.com/marcoroth/ntcharts-ruby/releases"
  spec.metadata["rubygems_mfa_required"] = "true"

  spec.files = Dir[
    "ntcharts.gemspec",
    "LICENSE.txt",
    "README.md",
    "lib/**/*.rb",
    "ext/**/*.{c,h,rb}",
    "go/**/*.{go,mod,sum}",
    "go/build/**/*"
  ]

  spec.require_paths = ["lib"]
  spec.extensions = ["ext/ntcharts/extconf.rb"]

  spec.add_dependency "rake-compiler", "~> 1.2"
end
