set(MAIN_FILE
    main.cpp
)

add_executable(main ${MAIN_FILE})

target_link_libraries(main PRIVATE IncompLib)