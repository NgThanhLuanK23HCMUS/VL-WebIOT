import { autoHideFlash, initForm } from "./handle_index_page.js";
import { setupLedControl, setUpBeepControl, handleSyncButton } from "./handle_control_panel_home.js";
import { sendUserIdIfNeeded } from "./handle_home_page.js";

const path = window.location.pathname;
if (path === "/home") {
  sendUserIdIfNeeded();
} else if (path === "/control") {
  setupLedControl();
  setUpBeepControl();
} else if (path === "/index") {
  document.addEventListener("DOMContentLoaded", () => {
    autoHideFlash();
  });
  initForm();
}

handleSyncButton();