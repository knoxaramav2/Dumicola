
#Version config
set(DUMICOMM_MAJOR 0)
set(DUMICOMM_MINOR 0)
set(DUMICOMM_BUILD 1)
configure_file(dumicommon_version.h.in dumicommon_version.h)

#Setup library
add_library(DUMICOMMON SHARED)
target_sources(
    DUMICOMMON
PUBLIC 
    dumicommon.cpp
PRIVATE

)

#Values

