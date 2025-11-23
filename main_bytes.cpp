#include "crow.h"
#include <fstream>
#include <bitset>
#include <vector>
#include <iostream>
#include <chrono>
#include <sstream>
#include "utils.hpp"
#include "constants.hpp"
#include "file_storage.hpp"

int main()
{

    crow::SimpleApp app;
    FileStorage fs;

    CROW_ROUTE(app, "/upload").methods("POST"_method)([fs](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400);
        
        auto byte_string = body["bytes"].s();
        auto file_name = body["filename"].s();
        std::string filename = generate_file_name();
        fs.create_file(UPLOAD_FOLDER + filename, byte_string);
        crow::json::wvalue response_body;
        
        response_body["message"] = "bytes uploaded";
        response_body["file_id"] = filename;
        return crow::response{response_body};
    });

    CROW_ROUTE(app, "/upload").methods("PUT"_method)([fs](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400);
        
        auto byte_string = body["bytes"].s();
        std::string filename;
        if (body.has("file_id")) {
            filename = std::string(body["file_id"].s());
        }
        else {
            filename = generate_file_name();
        }
        crow::json::wvalue response_body;
        
        fs.create_or_append(UPLOAD_FOLDER + filename, byte_string);
        response_body["message"] = "bytes uploaded";
        response_body["file_id"] = filename;
        return crow::response{response_body};
    });

    CROW_ROUTE(app, "/delete").methods("DELETE"_method)([fs](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400);
        
        auto file_id = body["file_id"].s();
        crow::json::wvalue response_body;
        fs.delete_file(UPLOAD_FOLDER + std::string(file_id));
        response_body["message"] = "file deleted";
        return crow::response{response_body};
    });
    app.port(18080).run();

}
// 1010101110111010 1011101010111110