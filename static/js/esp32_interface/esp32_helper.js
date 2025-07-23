fetch("/get_user_id")
  .then(res => res.json())
  .then(data => {
    const user_id = data.user_id;
    if (user_id) {
      console.log(user_id)
      fetch("http://192.168.1.6/api/user/send_id_to_device", {
        method: "POST",
        headers: { "Content-Type": "application/x-www-form-urlencoded" },
        body: `user_id=${user_id}`
      });
    }
  });
