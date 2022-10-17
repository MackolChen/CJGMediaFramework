#
# Be sure to run `pod lib lint CJGMediaFramework.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#
Pod::Spec.new do |s|
  s.name                  = 'CJGMediaFramework'
  s.version               = '1.2.1'
  s.summary               = '音视频处理'
  s.platform              = :ios, '10.0'
  s.homepage              = 'https://github.com/MackolChen/CJGMediaFramework'
  s.license               = { :type => 'MIT', :file => 'LICENSE' }
  s.author                = { 'MackolChen' => 'engineer_macchen@163.com' }
  s.source                = { :git => 'https://github.com/MackolChen/CJGMediaFramework.git', :tag => s.version.to_s }
  s.ios.deployment_target = '10.0'
  s.source_files          = 'CJGMediaFramework/Classes/**/*'
  s.requires_arc          = true
  s.libraries = 'c++'
end
