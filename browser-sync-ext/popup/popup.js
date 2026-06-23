// popup.js — BrowserSync popup logic

const IS_FIREFOX = typeof browser !== "undefined";
const ext = IS_FIREFOX ? browser : chrome;

const statusBox = document.getElementById("statusBox");
const extList = document.getElementById("extList");
const lastBackupTime = document.getElementById("lastBackupTime");
const autoToggle = document.getElementById("autoBackupToggle");

function showStatus(msg) {
  if (msg.startsWith("ready_extensions:")) {
    const exts = JSON.parse(msg.slice("ready_extensions:".length));
    renderExtensions(exts);
    return;
  }
  statusBox.classList.add("visible");
  statusBox.textContent = msg;
}

function renderExtensions(exts) {
  extList.innerHTML = "";
  extList.classList.add("visible");
  statusBox.classList.remove("visible");

  if (exts.length === 0) {
    extList.innerHTML = '<div class="ext-item"><span class="ext-name" style="color:var(--muted)">No extensions found in backup.</span></div>';
    return;
  }

  exts.forEach((e) => {
    const item = document.createElement("div");
    item.className = "ext-item";

    const name = document.createElement("span");
    name.className = "ext-name" + (e.enabled ? "" : " disabled");
    name.textContent = e.name;
    name.title = e.name;

    const link = document.createElement("a");
    link.className = "ext-link";
    link.href = "#";
    link.textContent = "Install →";
    link.addEventListener("click", (ev) => {
      ev.preventDefault();
      ext.tabs.create({ url: e.storeLink });
    });

    item.appendChild(name);
    item.appendChild(link);
    extList.appendChild(item);
  });
}

function setButtonsDisabled(disabled) {
  ["backupBtn", "restoreBookmarks", "restoreExtList"].forEach((id) => {
    document.getElementById(id).disabled = disabled;
  });
}

// Load last backup time & auto-backup setting
ext.runtime.sendMessage({ action: "getLastBackup" }, (data) => {
  if (data && data.lastBackup) {
    const d = new Date(data.lastBackup);
    lastBackupTime.textContent = d.toLocaleString();
  }
});

ext.storage.local.get("autoBackup", ({ autoBackup }) => {
  autoToggle.checked = !!autoBackup;
});

autoToggle.addEventListener("change", () => {
  ext.storage.local.set({ autoBackup: autoToggle.checked });
});

// Listen for status messages from background
ext.runtime.onMessage.addListener((msg) => {
  if (msg.type === "status") {
    showStatus(msg.text);
    if (msg.text.startsWith("✅") || msg.text.startsWith("❌")) {
      setButtonsDisabled(false);
      // Refresh last backup time
      ext.runtime.sendMessage({ action: "getLastBackup" }, (data) => {
        if (data && data.lastBackup) {
          lastBackupTime.textContent = new Date(data.lastBackup).toLocaleString();
        }
      });
    }
  }
});

document.getElementById("backupBtn").addEventListener("click", () => {
  setButtonsDisabled(true);
  extList.classList.remove("visible");
  showStatus("⏳ Starting backup...");
  ext.runtime.sendMessage({ action: "backup" });
});

document.getElementById("restoreBookmarks").addEventListener("click", () => {
  setButtonsDisabled(true);
  extList.classList.remove("visible");
  showStatus("⏳ Restoring bookmarks...");
  ext.runtime.sendMessage({ action: "restore", type: "bookmarks" });
});

document.getElementById("restoreExtList").addEventListener("click", () => {
  setButtonsDisabled(true);
  extList.classList.remove("visible");
  showStatus("⏳ Loading extension list...");
  ext.runtime.sendMessage({ action: "restore", type: "extensions" });
});
