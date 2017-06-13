Pod::Spec.new do |s|
  s.name         = "Porygon"
  s.version      = "0.0.2"
  s.summary      = "Generate low-poly style images."
  s.description  = <<-DESC
                   Porygon is a library for generate low-poly style images.
                   DESC

  s.homepage     = "https://github.com/DevinShine/Porygon"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author             = { "DevinShine" => "devin.xdw@gmail.com" }
  s.platform     = :ios, "8.0"
  s.source       = { :git => "https://github.com/DevinShine/Porygon.git", :tag => s.version }
  s.source_files  = "Sources/*.{h,m,c}"
  s.public_header_files = "Sources/*.h"
  s.framework  = "UIKit"
  s.requires_arc = true
end
