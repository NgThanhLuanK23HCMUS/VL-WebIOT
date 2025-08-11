#include "ReceiveThresholdConfigHandler.h"
#include <ArduinoJson.h>  // thư viện ArduinoJson giúp parse JSON dễ dàng


void ReceiveThresholdConfigHandler::handle(WebServer* server) {
    // CORS và OPTIONS xử lý
    if (server->method() == HTTP_OPTIONS) {
        server->sendHeader("Access-Control-Allow-Origin", "*");
        server->sendHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
        server->sendHeader("Access-Control-Allow-Headers", "Content-Type");
        server->send(204);  // No Content
        return;
    }

    // Chỉ xử lý POST
    if (server->method() != HTTP_POST) {
        server->sendHeader("Access-Control-Allow-Origin", "*");
        server->send(405, "text/plain", "Method Not Allowed");
        return;
    }

    // Kiểm tra các tham số bắt buộc
    if (!server->hasArg("temperature") || !server->hasArg("soilHumidity") || !server->hasArg("airHumidity")) {
        server->sendHeader("Access-Control-Allow-Origin", "*");
        server->send(400, "text/plain", "Missing parameters");
        return;
    }

    // Lấy giá trị từng tham số
    String tempStr = server->arg("temperature");
    String soilStr = server->arg("soilHumidity");
    String airStr = server->arg("airHumidity");

    // Chuyển sang float hoặc số thực
    float temperature = tempStr.toFloat();
    float soilHumidity = soilStr.toFloat();
    float airHumidity = airStr.toFloat();

    // Cập nhật vào sensor hoặc xử lý tiếp
    sensor->setTemperatureThreshold(temperature);
    sensor->setSoilThreshold(soilHumidity);
    sensor->setHumidityThreshold(airHumidity);


    // Trả về thành công
    server->sendHeader("Access-Control-Allow-Origin", "*");
    server->send(200, "application/json", "{\"message\":\"Thresholds updated successfully\"}");
}