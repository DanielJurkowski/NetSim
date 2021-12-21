include_directories(
        include
)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        )


add_executable(polprodukty ${SOURCE_FILES})