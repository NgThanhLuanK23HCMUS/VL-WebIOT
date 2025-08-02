export function setupLedControl() {
  const pumpCheckbox = document.getElementById("led");
  if (pumpCheckbox) {
    pumpCheckbox.addEventListener("change", function () {
      const isLedOn = this.checked;
      fetch("http://192.168.0.114/api/control_led", {
        method: "POST",
        headers: {
          "Content-Type": "application/x-www-form-urlencoded",
        },
        body: `state=${isLedOn ? "on" : "off"}`,
      })
        .then((response) => {
          if (response.ok) {
            console.log("Thành Công");
          } else {
            console.error("Gửi thất bại");
          }
        })
        .catch((err) => {
          console.error("Lỗi khi gửi:", err);
        });
    });
  }
}

export function setUpBeepControl() {
  const beepCheckbox = document.getElementById("beep");
  if (beepCheckbox) {
    beepCheckbox.addEventListener("change", function () {
      const isBeepOn = this.checked;
      fetch("http://192.168.0.114/api/control_beep", {
        method: "POST",
        headers: {
          "Content-Type": "application/x-www-form-urlencoded",
        },
        body: `state=${isBeepOn ? "on" : "off"}`,
      })
        .then((response) => {
          if (response.ok) {
            console.log("Thành Công");
          } else {
            console.error("Gửi thất bại");
          }
        })
        .catch((err) => {
          console.error("Lỗi khi gửi:", err);
        });
    });
  }
}

export function handleSyncButton() {
  document.addEventListener('DOMContentLoaded', function () {
  const autoModeCheckbox = document.getElementById('autoMode');
  const manualIds = ['pump', 'led', 'beep'];
  const manualControls = manualIds.map(id => document.getElementById(id));

  manualControls.forEach(control => {
    control.addEventListener('change', () => {
      if (autoModeCheckbox.checked) {
        autoModeCheckbox.checked = false;
        fetch("http://192.168.0.114/api/control_mode", {
          method: "POST",
          headers: {
            "Content-Type": "application/x-www-form-urlencoded",
          },
          body: `mode=manual`,
        })
          .then((response) => {
            if (response.ok) {
              console.log("Chuyển sang chế độ thủ công");
            } else {
              console.error("Gửi thất bại");
            }
          })
          .catch((err) => {
            console.error("Lỗi khi gửi:", err);
          });
      }
    });
  });

  autoModeCheckbox.addEventListener('change', () => {
    if (autoModeCheckbox.checked) {
      manualControls.forEach(control => {
        control.checked = false;
      });
      fetch("http://192.168.0.114/api/control_mode", {
        method: "POST",
        headers: {
          "Content-Type": "application/x-www-form-urlencoded",
        },
        body: `mode=auto`,
      })
        .then((response) => {
          if (response.ok) {
            console.log("Chuyển sang chế độ tự động");
          } else {
            console.error("Gửi thất bại");
          }
        })
        .catch((err) => {
          console.error("Lỗi khi gửi:", err);
        });
    }
  });
});

}
