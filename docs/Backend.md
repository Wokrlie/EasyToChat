# Backend

## Code structure

### `backend/CMakeLists.txt`
Defines the project type(static library) and requirements

### `backend/src/Backend.cpp`  

Main logic is in the constructor of Backend. API ports is registered here.

### `backend/src/Backend.h`  

Contains global datas, convers, users, and websocket connections. Database will manage the convers and users in the future.

### `backend/tests`

Empty now, create for tests.
