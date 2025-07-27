// Dùng sessionStorage thay vì localStorage
let isSend = sessionStorage.getItem("isSend") !== "false";

fetch("/get_user_id")
  .then(res => res.json())
  .then(data => {
    console.log("isSend =", isSend);
    const user_id = data.user_id;
    console.log(user_id);
    if (isSend && user_id) {
      console.log("Sending user_id:", user_id);
      fetch("http://192.168.0.114/api/user/send_id_to_device", {
        method: "POST",
        headers: { "Content-Type": "application/x-www-form-urlencoded" },
        body: `user_id=${user_id}`
      }).then(response => {
        if (response.ok) {
          sessionStorage.setItem("isSend", "false"); // lưu tạm trong session
        }
      });
    }
  });
