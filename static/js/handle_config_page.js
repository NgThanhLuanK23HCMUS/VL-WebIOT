const gearIcon = document.getElementById("openSettings");
const gearMenu = document.getElementById("gearMenu");
const openConfigBtn = document.getElementById("openConfig");
const logoutBtn = document.getElementById("logoutBtn");
const modal = document.getElementById("settingsModal");
const closeSettingsBtn = document.getElementById("closeSettings");

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
  document.getElementById("privateKey").value = "";
});

// Đóng modal khi nhấn nút đóng
closeSettingsBtn.addEventListener("click", () => {
  modal.style.display = "none";
});


// Xử lý nút lưu trong modal
document.getElementById("saveSettings").addEventListener("click", () => {
  const temp = document.getElementById("temp").value;
  const soil = document.getElementById("soilHumidity").value;
  const air = document.getElementById("airHumidity").value;
  const privateKey = document.getElementById("privateKey").value;

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


  console.log("haha")
  // Gửi dữ liệu lên server (ví dụ dùng x-www-form-urlencoded)
  fetch("http://192.168.1.2/api/save/threshold", {
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
