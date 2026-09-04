# Backend

## Notices

## Code structure

### `backend/CMakeLists.txt`
Defines the project type(static library) and requirements

### `backend/src/Backend.cpp`  

Main logic is in the constructor of Backend. API ports is registered here.

### `backend/src/Backend.h`  

Contains global datas, convers, users, and websocket connections. Database will manage the convers and users in the future.

### `backend/src/functions/auth/JWT.h` & `backend/src/functions/JWT.cpp`

JWT verify wrapper, provide `verify_from_req(const crow::request& req)`, `verify_token(const std::string& token)`, `generate_token(const std::string& username)`.  
The verify functions all return a `std::optional<std::string>`. If the token is vaild, the functions will return the username. Unless, return a `std::nullopt`.

### `backend/tests`

Empty now, create for tests.
