project(
	'Flood Fill',
	'c',
	version: '0.2.1',
	license: 'MIT',
	default_options:
	[
		'c_std=c11',
		'warning_level=3'
	]
)

add_project_arguments(
	[
		'-Wundef',
		'-Wvla',
		'-DNAME="@0@"'.format(meson.project_name()),
		'-DVERSION="@0@"'.format(meson.project_version()),
		'-DLICENSE="@0@"'.format(meson.project_license()[0]),
	],
	language: 'c'
)

datadir = get_option('datadir')
sysconfdir = get_option('sysconfdir')
prefix = get_option('prefix')
incdir = include_directories('include')

subdir('res')
subdir('src')