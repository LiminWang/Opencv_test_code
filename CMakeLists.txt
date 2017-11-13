project( opencv_test )

find_package( OpenCV REQUIRED )

MACRO(add_target name)
    ADD_EXECUTABLE(${name} ${name}.cpp)
    TARGET_LINK_LIBRARIES(${name} ${OpenCV_LIBS} )
ENDMACRO()

add_target(video_capture)
add_target(laplace)
add_target(canny)
add_target(sobel)
add_target(histogram_qualization)
add_target(match_template)
add_target(match_template_demo)
add_target(grabcut)
add_target(extract_roi)
add_target(max_vehicle)

