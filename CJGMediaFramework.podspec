#
# Be sure to run `pod lib lint CJGMediaFramework.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#
Pod::Spec.new do |s|
  s.name             = 'CJGMediaFramework'
  s.version          = '1.0.9'
  s.summary          = '音视频处理'
  s.platform = :ios, '10.0'
  s.pod_target_xcconfig = { :OTHER_LDFLAGS => '-lObjC',
     :CLANG_CXX_LANGUAGE_STANDARD => 'c++11',
     :CLANG_CXX_LIBRARY => 'libc++' }
  s.user_target_xcconfig = { 'OTHER_LDFLAGS' => '-lObjC',
     'CLANG_CXX_LANGUAGE_STANDARD' => 'c++11',
     'CLANG_CXX_LIBRARY' => 'libc++' }
  s.libraries = 'c++','z'
  s.homepage         = 'https://github.com/MackolChen/CJGMediaFramework.git'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'MackolChen' => 'engineer_macchen@163.com' }
  s.source           = { :git => 'https://github.com/MackolChen/CJGMediaFramework.git', :tag => s.version.to_s }
  s.ios.deployment_target = '10.0'
  s.source_files = 'CJGMediaFramework/Classes/**/*'
  valid_archs = ['armv7s','arm64','x86_64','armv7','arm64e']
  s.frameworks = ['Foundation','UIKit']
end
