function(jage_set_warnings target)
    set(_warnings
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wnull-dereference
    )

    if(JAGE_WARNINGS_AS_ERRORS)
        list(APPEND _warnings -Werror)
    endif()

    target_compile_options(${target} PRIVATE ${_warnings})
endfunction()
