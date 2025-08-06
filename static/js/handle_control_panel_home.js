// let controlMode = "null";
// let userId = null;
// console.log("Control mode:", controlMode);
// if (userId === null) {
//   userId = getUserId();
// }
// function sendControlMode(mode, user_id) {
//   console.log(userId);
//   const urlServer = `/api/update/control/mode?mode=${mode}&user_id=${encodeURIComponent(
//     user_id
//   )}`;
//   const urlESP32 = "http://192.168.100.132/api/control_mode";

//   fetch(urlServer, { method: "GET" })
//     .then((res) => {
//       if (!res.ok) console.error("Server update failed");
//       else console.log("Server updated control mode");
//     })
//     .catch((err) => console.error("Server error:", err));

//   fetch(urlESP32, {
//     method: "POST",
//     headers: {
//       "Content-Type": "application/x-www-form-urlencoded",
//     },
//     body: `mode=${mode}`,
//   })
//     .then((res) => {
//       if (!res.ok) console.error("ESP32 update failed");
//       else console.log("✅ ESP32 updated control mode");
//     })
//     .catch((err) => console.error(" ESP32 error:", err));
// }

// // Gửi lệnh điều khiển thiết bị như LED/PUMP/BEEP
// function sendDeviceControl(endpoint, state) {
//   fetch(`http://192.168.100.132/api/${endpoint}`, {
//     method: "POST",
//     headers: {
//       "Content-Type": "application/x-www-form-urlencoded",
//     },
//     body: `state=${state ? "on" : "off"}`,
//   })
//     .then((res) => {
//       if (!res.ok) throw new Error(`ESP32 gửi ${endpoint} thất bại`);
//       console.log(`Gửi ${endpoint} ${state ? "on" : "off"} thành công`);
//     })
//     .catch((err) => {
//       console.error(`Lỗi khi gửi ${endpoint}:`, err);
//     });
// }

// // Hàm lấy user_id từ server
// async function getUserId() {
//   try {
//     const res = await fetch("/get_user_id");
//     const data = await res.json();
//     if (data.user_id) {
//       userId = data.user_id;
//       return userId;
//     } else {
//       console.error("Không có user_id");
//       return null;
//     }
//   } catch (err) {
//     console.error("Không thể lấy user_id:", err);
//     return null;
//   }
// }

// // Hàm khởi tạo điều khiển LED và thiết lập chế độ ban đầu
// export function setupLedControl() {
//   const ledCheckBox = document.getElementById("led");
//   const autoModeCheckbox = document.getElementById("autoMode");
//   if (!ledCheckBox || !autoModeCheckbox) return;

//   ledCheckBox.addEventListener("change", function () {
//     // Nếu đang bật chế độ auto => tắt auto
//     console.log(controlMode);

//     if (autoModeCheckbox.checked) {
//       autoModeCheckbox.checked = false;
//     }

//     if (controlMode !== "manual") {
//       controlMode = "manual";
//       sendControlMode(controlMode, userId);
//       setTimeout(() => {
//         sendDeviceControl("control_led", ledCheckBox.checked);
//       }, 300);
//     } else {
//       sendDeviceControl("control_led", this.checked);
//     }
//     setUpNoControlMode();
//   });
// }

// export function setUpPumpControl() {
//   const pumpCheck = document.getElementById("pump");
//   const autoModeCheck = document.getElementById("autoMode");

//   if (!pumpCheck || !autoModeCheck) return;
//   pumpCheck.addEventListener("change", function () {
//     if (autoModeCheck.checked) {
//       autoModeCheck.checked = false;
//     }

//     if (controlMode !== "manual") {
//       controlMode = "manual";
//       sendControlMode(controlMode, userId);
//       setTimeout(() => {
//         sendDeviceControl("control_pump", this.checked);
//       }, 300);
//     } else {
//       sendDeviceControl("control_pump", this.checked);
//     }

//     setUpNoControlMode();
//   });
// }

// // Gắn sự kiện khi chuyển qua chế độ AUTO
// export function setUpAutoModeControl() {
//   const autoModeCheckbox = document.getElementById("autoMode");
//   if (!autoModeCheckbox) return;

//   autoModeCheckbox.addEventListener("change", async function () {
//     if (this.checked) {
//       // Tắt các chế độ thủ công
//       const manualControls = ["pump", "led", "beep"];
//       manualControls.forEach((id) => {
//         const control = document.getElementById(id);
//         if (control) control.checked = false;
//       });

//       if (controlMode !== "auto") {
//         controlMode = "auto";
//         sendControlMode(controlMode, userId); // Gửi 1 lần duy nhất
//       }
//     }
//     setUpNoControlMode();
//   });
// }

// function setUpNoControlMode() {
//   const autoBox = document.getElementById("autoMode");
//   const led = document.getElementById("led");
//   const pump = document.getElementById("pump");
//   const beep = document.getElementById("beep");

//   if (!autoBox || !led || !pump || !beep) return;

//   if (!autoBox.checked && !led.checked && !pump.checked && !beep.checked && controlMode !== "null") {
//     controlMode = "null";
//     sendControlMode(controlMode, userId);
//   }
// }

// export function setUpBeepControl() {
//   const pumpCheck = document.getElementById("beep");
//   const autoModeCheck = document.getElementById("autoMode");

//   if (!pumpCheck || !autoModeCheck) return;
//   pumpCheck.addEventListener("change", function () {
//     if (autoModeCheck.checked) {
//       autoModeCheck.checked = false;
//     }

//     if (controlMode !== "manual") {
//       controlMode = "manual";
//       sendControlMode(controlMode, userId);
//       setTimeout(() => {
//         sendDeviceControl("control_beep", this.checked);
//       }, 300);
//     } else {
//       sendDeviceControl("control_beep", this.checked);
//     }

//     setUpNoControlMode();
//   });
// }


let controlMode = "null";
let userId = null;

// Gọi khi load trang
window.addEventListener("DOMContentLoaded", async () => {
  userId = await getUserId();
  console.log(userId)
  await syncControlStateFromServer();

  setupLedControl();
  setUpPumpControl();
  setUpBeepControl();
  setUpAutoModeControl();
});

// Gửi trạng thái điều khiển lên server và ESP32
function sendControlMode(mode, user_id) {

  const urlServer = `/api/update/control/mode?mode=${mode}&user_id=${encodeURIComponent(user_id)}`;
  const urlESP32 = "http://192.168.100.132/api/control_mode";

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
  fetch(`http://192.168.100.132/api/${endpoint}`, {
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
    body: `device=${endpoint.replace("control_", "")}&state=${state}&userId=${userId}`,  
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

// Các hàm điều khiển thiết bị
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
        sendDeviceControl("control_led", ledCheckBox.checked);
      }, 300);
    } else {
      sendDeviceControl("control_led", this.checked);
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
        sendDeviceControl("control_pump", this.checked);
      }, 300);
    } else {
      sendDeviceControl("control_pump", this.checked);
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
        sendDeviceControl("control_beep", this.checked);
      }, 300);
    } else {
      sendDeviceControl("control_beep", this.checked);
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

  if (!autoBox.checked && !led.checked && !pump.checked && !beep.checked && controlMode !== "null") {
    controlMode = "null";
    sendControlMode(controlMode, userId);
  }
}
