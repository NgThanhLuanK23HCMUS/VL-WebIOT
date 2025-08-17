let controlMode = "null";
let userId = null;
const beepInterval = 30000;
const pumpInterval = 10000;

const [led, pump, beep] = ["control_led", "control_pump", "control_beep"];
// Gọi khi load trang
window.addEventListener("DOMContentLoaded", async () => {
  userId = await getUserId();

  await syncControlStateFromServer();
  const led_device = document.getElementById("led");
  const pump_device = document.getElementById("pump");
  const beep_device = document.getElementById("beep");
  const auto_device = document.getElementById("autoMode");

  if (led_device.checked || pump.checked || beep.checked)
    controlMode = "manual";
  else {
    if (auto_device.checked) controlMode = "auto";
    else controlMode = "null";
  }
  sendControlMode(controlMode, userId);
  sendDeviceControl(led, led_device.checked);
  sendDeviceControl(pump, pump_device.checked);
  sendDeviceControl(beep, beep_device.checked);

});

// Gửi trạng thái điều khiển lên server và ESP32
function sendControlMode(mode, user_id) {
  const urlServer = `/api/update/control/mode?mode=${mode}&user_id=${encodeURIComponent(
    user_id
  )}`;
  const urlESP32 = "http://192.168.1.6/api/control_mode";

  fetch(urlServer, { method: "GET" })
    .then((res) => {
      if (!res.ok) console.error("Server update failed");
      else console.log("Server updated control mode");
    })
    .catch((err) => console.error("Server error:", err));

  fetch(urlESP32, {
    method: "POST",
    headers: {
      "Content-Type": "application/x-www-form-urlencoded",
    },
    body: `mode=${mode}`,
  })
    .then((res) => {
      if (!res.ok) console.error("ESP32 update failed");
      else console.log("✅ ESP32 updated control mode");
    })
    .catch((err) => console.error("ESP32 error:", err));
}

// Gửi điều khiển thiết bị + cập nhật server
function sendDeviceControl(endpoint, state) {
  // Gửi ESP32
  fetch(`http://192.168.1.6/api/${endpoint}`, {
    method: "POST",
    headers: {
      "Content-Type": "application/x-www-form-urlencoded",
    },
    body: `state=${state ? "on" : "off"}`,
  })
    .then((res) => {
      if (!res.ok) throw new Error(`ESP32 gửi ${endpoint} thất bại`);
      console.log(`Gửi ${endpoint} ${state ? "on" : "off"} thành công`);
    })
    .catch((err) => {
      console.error(`Lỗi khi gửi ${endpoint}:`, err);
    });

  // Gửi server cập nhật DB
  fetch("/api/update/control/device", {
    method: "POST",
    headers: {
      "Content-Type": "application/x-www-form-urlencoded",
    },
    body: `device=${endpoint.replace(
      "control_",
      ""
    )}&state=${state}&userId=${userId}`,
  })
    .then((res) => {
      if (!res.ok) console.error("Cập nhật DB thất bại");
    })
    .catch((err) => console.error("Lỗi khi cập nhật DB:", err));
}

// Lấy user_id
async function getUserId() {
  try {
    const res = await fetch("/get_user_id");
    const data = await res.json();
    if (data.user_id) {
      return data.user_id;
    } else {
      return null;
    }
  } catch (err) {
    return null;
  }
}

// Đồng bộ trạng thái khi quay lại trang
export async function syncControlStateFromServer() {
  try {
    const res = await fetch("/get/control/status?userId=" + userId);
    const data = await res.json();

    const autoBox = document.getElementById("autoMode");
    const led = document.getElementById("led");
    const pump = document.getElementById("pump");
    const beep = document.getElementById("beep");

    if (!autoBox || !led || !pump || !beep) return;

    controlMode = data.mode || "null";

    if (controlMode === "auto") {
      autoBox.checked = true;
      led.checked = false;
      pump.checked = false;
      beep.checked = false;
    } else {
      autoBox.checked = false;
      led.checked = data.led;
      pump.checked = data.pump;
      beep.checked = data.beep;
    }
  } catch (err) {
    console.error("Không thể đồng bộ trạng thái điều khiển từ server:", err);
  }
}

export function setupLedControl() {
  const ledCheckBox = document.getElementById("led");
  const autoModeCheckbox = document.getElementById("autoMode");
  if (!ledCheckBox || !autoModeCheckbox) return;

  ledCheckBox.addEventListener("change", function () {
    if (autoModeCheckbox.checked) {
      autoModeCheckbox.checked = false;
    }

    if (controlMode !== "manual") {
      controlMode = "manual";
      sendControlMode(controlMode, userId);
      setTimeout(() => {
        sendDeviceControl(led, ledCheckBox.checked);
      }, 300);
    } else {
      sendDeviceControl(led, this.checked);
    }

    setUpNoControlMode();
  });
}

export function setUpPumpControl() {
  const pumpCheck = document.getElementById("pump");
  const autoModeCheck = document.getElementById("autoMode");

  if (!pumpCheck || !autoModeCheck) return;
  pumpCheck.addEventListener("change", function () {
    if (autoModeCheck.checked) {
      autoModeCheck.checked = false;
    }

    if (controlMode !== "manual") {
      controlMode = "manual";
      sendControlMode(controlMode, userId);
      setTimeout(() => {
        sendDeviceControl(pump, this.checked);
      }, 300);
    } else {
      sendDeviceControl(pump, this.checked);
    }
    if (this.checked) {
      setTimeout(() => {
        if (pumpCheck.checked) {
          pumpCheck.checked = false;
          sendDeviceControl(pump, pumpCheck.checked);
        }
      }, pumpInterval);
    }

    setUpNoControlMode();
  });
}

export function setUpBeepControl() {
  const beepCheck = document.getElementById("beep");
  const autoModeCheck = document.getElementById("autoMode");

  if (!beepCheck || !autoModeCheck) return;
  beepCheck.addEventListener("change", function () {
    if (autoModeCheck.checked) {
      autoModeCheck.checked = false;
    }

    if (controlMode !== "manual") {
      controlMode = "manual";
      sendControlMode(controlMode, userId);
      setTimeout(() => {
        sendDeviceControl(beep, this.checked);
      }, 300);
    } else {
      sendDeviceControl(beep, this.checked);
    }

    if (this.checked) {
      setTimeout(() => {
        if (beepCheck.checked) {
          beepCheck.checked = false;
          sendDeviceControl(beep, beepCheck.checked);
        }
      }, beepInterval);
    }

    setUpNoControlMode();
  });
}

// Khi bật chế độ auto
export function setUpAutoModeControl() {
  const autoModeCheckbox = document.getElementById("autoMode");
  if (!autoModeCheckbox) return;

  autoModeCheckbox.addEventListener("change", async function () {
    if (this.checked) {
      const manualControls = ["pump", "led", "beep"];
      manualControls.forEach((id) => {
        const control = document.getElementById(id);
        if (control) {
          control.checked = false;
          sendDeviceControl(`control_${id}`, false);
        }
      });

      if (controlMode !== "auto") {
        controlMode = "auto";
        sendControlMode(controlMode, userId);
      }
    }

    setUpNoControlMode();
  });
}

// Nếu không còn thiết bị nào đang bật => set về "null"
function setUpNoControlMode() {
  const autoBox = document.getElementById("autoMode");
  const led = document.getElementById("led");
  const pump = document.getElementById("pump");
  const beep = document.getElementById("beep");

  if (!autoBox || !led || !pump || !beep) return;

  if (
    !autoBox.checked &&
    !led.checked &&
    !pump.checked &&
    !beep.checked &&
    controlMode !== "null"
  ) {
    controlMode = "null";
    sendControlMode(controlMode, userId);
  }
}
