MRuby::Build.new do |conf|

  if ENV['VisualStudioVersion'] || ENV['VSINSTALLDIR']
    toolchain :visualcpp
  else
    toolchain :gcc
  end

  conf.gembox 'default'

  conf.gem :mgem => 'json'
  conf.gem :mgem => 'dir'

  conf.cc.flags << '-DMRB_USE_FLOAT -DMRB_UTF8_STRING'

  conf.build_dir = ENV["MRUBY_BUILD_DIR"] || raise("MRUBY_BUILD_DIR undefined!")

end
