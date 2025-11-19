add_executable(indev indev.cpp)
target_compile_features(indev PRIVATE cxx_std_23)
target_link_libraries(indev PRIVATE theia::theia)
