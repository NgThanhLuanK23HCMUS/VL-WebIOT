export function sendUserIdIfNeeded() {
  let isSendStr = sessionStorage.getItem("isSend");

  let isSend = isSendStr === null ? true : isSendStr === "true";

  if (isSend) {
    fetch("/get_user_id")
      .then((res) => res.json())
      .then((data) => {
        const user_id = data.user_id;

        console.log(user_id);
        console.log(isSend);
        if (user_id) {
          fetch("http://192.168.1.7/api/user/send_id_to_device", {
            method: "POST",
            headers: { "Content-Type": "application/x-www-form-urlencoded" },
            body: `user_id=${user_id}`,
          }).then((response) => {
            if (response.ok) {
              sessionStorage.setItem("isSend", "false");
            }
          });
        }
      });
  }
}
