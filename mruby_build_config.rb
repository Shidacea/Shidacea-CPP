MRuby::Build.new do |conf|

  if ENV['VisualStudioVersion'] || ENV['VSINSTALLDIR']
    toolchain :visualcpp

     # The definition for ssize_t is due to a compilation error from mruby on Windows, where ssize_t is apparently not defined
     # If this gets fixed, the following line can be removed safely
    conf.cc.flags << '-Dssize_t=int'
  else
    toolchain :gcc
  end

  conf.gembox 'default'

  conf.gem :mgem => 'json'
  conf.gem :mgem => 'dir'

  conf.cc.flags << '-DMRB_USE_FLOAT -DMRB_UTF8_STRING'

  conf.build_dir = ENV["MRUBY_BUILD_DIR"] || raise("MRUBY_BUILD_DIR undefined!")

end
