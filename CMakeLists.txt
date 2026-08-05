cmake_minimum_required(VERSION 3.15)
project(EasyToChat VERSION 0.0.1)

add_subdirectory(backend)
add_subdirectory(desktop-client)

find_program(PNPM_EXECUTABLE pnpm)
if(NOT PNPM_EXECUTABLE)
    message(WARNING "pnpm not found, frontend build will be skipped")
endif()

add_custom_target(build-frontend
    COMMAND ${PNPM_EXECUTABLE} install
    COMMAND ${PNPM_EXECUTABLE} build
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/frontend
    COMMENT "Building frontend with pnpm"
    BYPRODUCTS ${CMAKE_SOURCE_DIR}/frontend/dist
)

if(TARGET desktop-client)
    add_dependencies(desktop-client build-frontend)
endif()

# 可选：添加一个安装目标，将前端 dist 复制到最终输出目录
install(DIRECTORY ${CMAKE_SOURCE_DIR}/frontend/dist/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/static
)
