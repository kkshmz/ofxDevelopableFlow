meta:
	ADDON_NAME = ofxDevelopableFlow
	ADDON_DESCRIPTION = An openFrameworks wrapper for using Developable flow library by Keenan Crane
	ADDON_AUTHOR = Kye Shimizu
	ADDON_TAGS = "linear algebra" "Discrete Geometry" "Matrix"
	ADDON_URL = http://github.com/kkshmz/ofxDevelopableFlow

common:
	ADDON_DEFINES =
	ADDON_CFLAGS = -O3 -Wno-strict-aliasing

	# Exclude includes and source.
	ADDON_SOURCES_EXCLUDE = libs/developableflow/include/%
	ADDON_INCLUDES_EXCLUDE = libs/developableflow/include/%

	# Manually add the includes and source.
	ADDON_INCLUDES = libs/developableflow/include
	ADDON_INCLUDES += libs/ofxDevelopableFlow/include
	ADDON_INCLUDES += src
