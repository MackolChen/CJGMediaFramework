#
# Be sure to run `pod lib lint CJGMediaFramework.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'CJGMediaFramework'
  s.version          = '1.0.4'
  s.summary          = '音视频处理'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/MackolChen/CJGMediaFramework'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'MackolChen' => 'engineer_macchen@163.com' }
  s.source           = { :git => 'https://github.com/MackolChen/CJGMediaFramework.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'
#  spec.pod_target_xcconfig = { 'VALID_ARCHS' => 'x86_64 armv7 arm64' }
  s.ios.deployment_target = '10.0'

  s.source_files = 'CJGMediaFramework/Classes/**/*'
  
  # s.resource_bundles = {
  #   'CJGMediaFramework' => ['CJGMediaFramework/Assets/*.png']
  # }
  VALID_ARCHS = ['armv7s','arm64','x86_64','armv7','arm64e']
  # s.public_header_files = 'Pod/Classes/**/*.h'
   s.frameworks = 'Foundation','UIKit', 'libc++'
  # s.dependency 'AFNetworking', '~> 2.3'
end
