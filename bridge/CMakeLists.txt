set(SRCS ddsjson.C)
set(HDRS ddsjson.h)

add_library(bridge SHARED)
add_library(bridge::bridge ALIAS bridge)

target_sources(bridge PRIVATE ${SRCS} ${HDRS})

set_target_properties(bridge PROPERTIES LINKER_LANGUAGE CXX)

set_property(TARGET bridge PROPERTY CXX_STANDARD 17)
set_property(TARGET bridge PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(bridge PRIVATE ${RapidJSON_INCLUDE_DIR})

target_link_libraries(bridge PRIVATE dds)

install(TARGETS bridge)
