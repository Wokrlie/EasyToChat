cmake_minimum_required(VERSION 3.15)
project(EasyToChat VERSION 0.0.1 LANGUAGES C CXX)

add_subdirectory(backend)
add_subdirectory(desktop-client)

# ---------- Frontend (pnpm) ----------
find_program(PNPM_EXECUTABLE pnpm)

if(PNPM_EXECUTABLE)
    add_custom_target(build-frontend
        COMMAND ${PNPM_EXECUTABLE} install --frozen-lockfile
        COMMAND ${PNPM_EXECUTABLE} run build
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/frontend
        COMMENT "Building frontend with pnpm"
        BYPRODUCTS ${CMAKE_SOURCE_DIR}/frontend/dist
        VERBATIM
    )

    # 桌面客户端构建依赖前端产物
    if(TARGET desktop-client)
        add_dependencies(desktop-client build-frontend)
    endif()

    # 安装时把 dist 复制到 <prefix>/static
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/frontend/dist/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/static
        OPTIONAL
    )
else()
    message(STATUS "pnpm not found, skipping 'build-frontend' target. \
前端构建请直接执行: cd frontend && pnpm install && pnpm run build")
endif()
