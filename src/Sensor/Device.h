#ifndef Device_h
#define Device_h

#include <Arduino.h>

class Device {
private:
    String deviceId;
    String userId;
    String deviceName;
    
public:
    Device(String id, String user, String name) {
        deviceId = id;
        userId = user;
        deviceName = name;
    }

    String getDeviceId() const {
        return deviceId;
    }

    String getUserId() const {
        return userId;
    }

    String getDeviceName() const {
        return deviceName;
    }

    void setUserId(const String& user) {
        userId = user;
    }

    

    ~Device() {
    }
};

#endif
