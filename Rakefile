# -*- coding: utf-8; mode: ruby -*-

require 'English'

require 'find'
require 'fileutils'
require 'rubygems'
require 'hoe'

base_dir = File.join(File.dirname(__FILE__))
truncate_base_dir = Proc.new do |x|
  x.gsub(/^#{Regexp.escape(base_dir + File::SEPARATOR)}/, '')
end

groonga_ext_dir = File.join(base_dir, 'src')
groonga_lib_dir = File.join(groonga_ext_dir, 'lib')
$LOAD_PATH.unshift(groonga_ext_dir)
$LOAD_PATH.unshift(groonga_lib_dir)
ENV["RUBYLIB"] = "#{groonga_lib_dir}:#{groonga_ext_dir}:#{ENV['RUBYLIB']}"

def guess_version
  require 'groonga'
  Groonga.bindings_version
end

groonga_win32_dir = "groonga"
FileUtils.rm_rf(groonga_win32_dir)

manifest = File.join(base_dir, "Manifest.txt")
manifest_contents = []
base_dir_included_components = %w(AUTHORS COPYING ChangeLog GPL
                                  NEWS README Rakefile
                                  extconf.rb pkg-config.rb)
excluded_components = %w(.cvsignore .gdb_history CVS depend Makefile pkg
                         .test-result)
excluded_suffixes = %w(.png .ps .pdf .o .so .a .txt .~)
Find.find(base_dir) do |target|
  target = truncate_base_dir[target]
  components = target.split(File::SEPARATOR)
  if components.size == 1 and !File.directory?(target)
    next unless base_dir_included_components.include?(components[0])
  end
  Find.prune if (excluded_components - components) != excluded_components
  next if excluded_suffixes.include?(File.extname(target))
  manifest_contents << target if File.file?(target)
end

File.open(manifest, "w") do |f|
  f.puts manifest_contents.sort.join("\n")
end

# For Hoe's no user friendly default behavior. :<
File.open("README.txt", "w") {|file| file << "= Dummy README\n== XXX\n"}
FileUtils.cp("NEWS", "History.txt")
at_exit do
  FileUtils.rm_f("README.txt")
  FileUtils.rm_f("History.txt")
  FileUtils.rm_f(manifest)
end

ENV["VERSION"] ||= guess_version
version = ENV["VERSION"]
project = Hoe.new('groonga', version) do |project|
  project.rubyforge_name = 'groonga'
  authors = File.join(base_dir, "AUTHORS")
  project.author = File.readlines(authors).collect do |line|
    if /\s*<[^<>]*>$/ =~ line
      $PREMATCH
    else
      nil
    end
  end.compact
  project.email = ['groonga-users-en@rubyforge.org',
                   'groonga-dev@lists.sourceforge.jp']
  project.summary = 'Ruby bindings for groonga'
  project.url = 'http://groonga.rubyforge.org/'
  project.test_globs = []
  project.spec_extras = {
    :extensions => ['extconf.rb'],
    :require_paths => ['src/lib', 'src'],
    :has_rdoc => false,
  }
  news = File.join(base_dir, "NEWS")
  project.changes = File.read(news).gsub(/\n+^Release(?m:.*)/, '')
  project.description = "Ruby bindings for groonga"
  project.need_tar = false
  project.remote_rdoc_dir = "doc"
end

project.spec.dependencies.delete_if {|dependency| dependency.name == "hoe"}

if /mswin32/ =~ project.spec.platform.to_s
  project.spec.extensions = []
  project.spec.files += ["src/groonga.so", "src/libruby-groonga.a"]

  FileUtils.cp_r(File.expand_path("~/.wine/drive_c/groonga-dev"),
                 groonga_win32_dir)
  groonga_files = []
  Find.find(groonga_win32_dir) do |f|
    groonga_files << f
  end
  project.spec.files += groonga_files
end

# fix Hoe's incorrect guess.
project.spec.executables.clear
project.lib_files = project.spec.files.grep(%r|^src/lib/|)

# fix Hoe's install and uninstall task.
task(:install).instance_variable_get("@actions").clear
task(:uninstall).instance_variable_get("@actions").clear

task(:release).prerequisites.reject! {|name| name == "clean"}
