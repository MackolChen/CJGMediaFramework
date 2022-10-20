#
# Be sure to run `pod lib lint CJGMediaFramework.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#
Pod::Spec.new do |s|
  s.name                  = 'CJGMediaFramework'
  s.version               = '1.2.4'
  s.summary               = '音视频处理'
  s.platform              = :ios, '10.0'
  s.homepage              = 'https://github.com/MackolChen/CJGMediaFramework'
  s.license               = { :type => 'MIT', :file => 'LICENSE' }
  s.author                = { 'MackolChen' => 'engineer_macchen@163.com' }
  s.static_framework  =  true # 是否是静态库
  s.requires_arc = true  # 是否是 arc 环境
  s.source                = { :git => 'https://github.com/MackolChen/CJGMediaFramework.git', :tag => s.version.to_s }
  s.ios.deployment_target = '10.0'
  s.resource = 'CJGMediaFramework/Classes/CJGMediaFramework.framework/Headers'
  s.public_header_files = 'CJGMediaFramework/Classes/**/*.h'  # framework 暴露的头文件
  s.vendored_frameworks = ['CJGMediaFramework/Classes/CJGMediaFramework.framework'] #  .framework 资源路径
  s.source_files          = 'CJGMediaFramework/Classes/**/*'
  s.requires_arc          = true
  s.libraries = 'c++'
  s.xcconfig = {
      'CLANG_CXX_LIBRARY' => 'libc++'
      }

  s.public_header_files = 'CJGMediaFramework/Classes/**/*.h'  # framework 暴露的头文件
end
