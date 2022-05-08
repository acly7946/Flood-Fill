project(
	'Flood Fill',
	'c',
	version: '0.2.0',
	license: 'MIT',
	default_options:
	[
		'c_std=c11'
	]
)

add_project_arguments(
	[
		'-Wno-unused-parameter',
		'-Wno-unused-result',
		'-Wno-missing-braces',
		'-Wundef',
		'-Wvla',
	],
	language: 'c'
)

raylib = dependency('raylib')

install_data(
	'res/floodfill.desktop',
	install_dir: '/usr/share/applications'
)

install_data(
	'res/floodfill.png',
	install_dir: '/usr/share/pixmaps'
)

executable(
	'floodfill',
	'src/main.c',
	'src/game.c',
	dependencies: raylib,
	install: true
)