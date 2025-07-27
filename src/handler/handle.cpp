#include "handle.h"
#include "../receive data/receive_device_info.h"
#include "../send data/send_device_info.h"
#include "../send data/send_sensor_data.h"
#include "../config.h"
#include "../Sensor/Sensor.h"




extern String user_id;
void Handle::handleReceiveUserID(WebServer* server, Sensor* sensor)
{
    if (receiveDeviceInfo(server, user_id)) {
        sendDeviceInfo(infoDeviceAndUserURL, sensor->getDeviceName(), user_id);
        server->sendHeader("Access-Control-Allow-Origin", "*"); // ⚠️ Bắt buộc
        server->send(200, "text/plain", "Đã nhận user_id: " + user_id);
    }
}

void Handle::handleSendDeviceInfo(Sensor* sensor)
{
    sendDeviceInfo(infoDeviceURL, sensor->getDeviceName(), "");
}

void Handle::handleSendSensorData(Sensor* sensor)
{
    sendSensorData(dataURL, sensor);
}
