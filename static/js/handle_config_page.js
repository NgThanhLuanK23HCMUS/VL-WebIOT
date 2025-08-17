const gearIcon = document.getElementById("openSettings");
const gearMenu = document.getElementById("gearMenu");

const openConfigBtn = document.getElementById("openConfig");
const openConfigBtn2 = document.getElementById("openConfig2");

const logoutBtn = document.getElementById("logoutBtn");

const modal = document.getElementById("settingsModal");
const modal2 = document.getElementById("settingsModal2");

const closeSettingsBtn = document.getElementById("closeSettings");
const closeSettingsBtn2 = document.getElementById("closeSettings2");

// Toggle popup menu khi nhấn bánh răng
gearIcon.addEventListener("click", () => {
  if (gearMenu.style.display === "block") {
    gearMenu.style.display = "none";
  } else {
    gearMenu.style.display = "block";
  }
});

// Ẩn popup menu khi click ra ngoài
window.addEventListener("click", (e) => {
  if (e.target !== gearIcon && !gearMenu.contains(e.target)) {
    gearMenu.style.display = "none";
  }
});

// Mở modal nhập thông số khi nhấn nút trong menu
openConfigBtn.addEventListener("click", () => {
  gearMenu.style.display = "none";
  modal.style.display = "block";
  // Xóa dữ liệu cũ
  document.getElementById("temp").value = "";
  document.getElementById("soilHumidity").value = "";
  document.getElementById("airHumidity").value = "";
});

openConfigBtn2.addEventListener("click", () => {
  gearMenu.style.display = "none";
  modal2.style.display = "block";
  // Xóa dữ liệu cũ
  document.getElementById("privateKey").value = "";
});

// Đóng modal khi nhấn nút đóng
closeSettingsBtn.addEventListener("click", () => {
  modal.style.display = "none";
});

closeSettingsBtn2.addEventListener("click", () => {
  modal2.style.display = "none";
});

// Xử lý nút lưu trong modal
document.addEventListener("DOMContentLoaded", () => {
  document.getElementById("saveSettings").addEventListener("click", () => {
    let temp = document.getElementById("temp").value;
    let soil = document.getElementById("soilHumidity").value;
    let air = document.getElementById("airHumidity").value;

    if (temp === "") temp = "null";
    if (soil === "") soil = "null";
    if (air === "") air = "null";

    if (soil == "null") console.log("haha");

    const modal = document.getElementById("settingsModal");
    modal.style.display = "none";

    // Gửi dữ liệu lên server (ví dụ dùng x-www-form-urlencoded)
    fetch("http://192.168.1.6/api/save/threshold", {
      method: "POST",
      headers: {
        "Content-Type": "application/x-www-form-urlencoded",
      },
      body: `temperature=${encodeURIComponent(
        temp
      )}&soilHumidity=${encodeURIComponent(
        soil
      )}&airHumidity=${encodeURIComponent(air)}`,
    })
      .then((res) => res.json())
      .then((data) => {
        console.log("Server trả về:", data);
      })
      .catch((err) => {
        console.error(err);
      });
  });
});

// Xử lý nút lưu trong modal 2
document.getElementById("saveSettings2").addEventListener("click", () => {
  const privateKey = document.getElementById("privateKey").value;

  const modal = document.getElementById("settingsModal2");
  modal.style.display = "none";
  fetch("/api/user/private_key", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({
      private_key: privateKey,
    }),
  })
    .then((res) => res.json())
    .then((data) => {
      modal.style.display = "none";
    })
    .catch((err) => {
      console.error(err);
    });
});

// Xử lý nút logout
logoutBtn.addEventListener("click", () => {
  gearMenu.style.display = "none";
  window.location.href = "/";
});
