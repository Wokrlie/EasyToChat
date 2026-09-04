#include "Path.h"
#include <vector>
#include <iostream>

std::filesystem::path getStaticDir() {
    const char* envPath = std::getenv("FRONTEND_DIST");
    if (envPath && std::filesystem::exists(envPath)) {
        return std::filesystem::canonical(envPath);
    }

    // 基于可执行文件路径推算（最可靠）
    // 注意：main 函数参数需要传入 argv
    std::filesystem::path execPath = std::filesystem::canonical("/proc/self/exe");
    std::filesystem::path base = std::filesystem::current_path();
    // 尝试多个候选路径
    std::vector<std::filesystem::path> candidates = {
        base / "../../frontend/dist",          // 从 build 往上两级
        base / "../../static"             // 通用备选
    };

    for (auto& p : candidates) {
        std::error_code ec;
        std::filesystem::path canonicalPath = std::filesystem::canonical(p, ec);
        if (!ec && std::filesystem::exists(canonicalPath / "index.html")) {
            std::cout << "Resolved static dir: " << canonicalPath << std::endl;
            return canonicalPath;
        }
    }

    // 最后的兜底：当前目录下的 static 文件夹（适合打包后的生产环境）
    std::filesystem::path fallback = std::filesystem::current_path() / "static";
    if (std::filesystem::exists(fallback / "index.html")) {
        return fallback;
    }

    throw std::runtime_error("Could not find frontend dist directory. Set FRONTEND_DIST env var.");
}
