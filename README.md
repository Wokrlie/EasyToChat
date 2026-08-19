# EasyToChat

## Notice

This project upgrades its dependencies regularly (when upgrades are needed). Please pull on time.  
The development and testing environment is POSIX systems, I haven't prepared to support the Windows platform.

## Layout

- `backend/` — C++ backend (vcpkg for dependency management)
- `desktop-client/` — C++ desktop client (standard cmake subprojects)
- `frontend/` — Web frontend (pnpm)

## Quick Start

### Frontend only

```bash
cd frontend
pnpm install
pnpm dev
```

### Configuration (local)

```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh
export VCPKG_ROOT=$HOME/vcpkg
```

### Backend + Desktop (CMake)

```bash
cmake --preset vcpkg
cmake --build --preset vcpkg
```

### Without Vcpkg?

If you don't want to manage the dependencies with vcpkg, 
- Download the sources, crow, jwt-cpp, libdatachannel, stduuid
- Build them correctly, the LibDataChannel need to init git submodule.
- Install them to system directory.
