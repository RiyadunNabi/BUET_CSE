// background.js — BrowserSync Drive Backup
// Works in both Chromium (MV3 service worker) and Firefox (MV2 background)

const DRIVE_FOLDER_NAME = "BrowserSync_Backup";
const DRIVE_API = "https://www.googleapis.com/drive/v3";
const DRIVE_UPLOAD = "https://www.googleapis.com/upload/drive/v3";
const IS_FIREFOX = typeof browser !== "undefined";
const ext = IS_FIREFOX ? browser : chrome;

// ─── OAuth ────────────────────────────────────────────────────────────────────

async function getAuthToken(interactive = true) {
  if (!IS_FIREFOX) {
    // Chromium: use identity API
    return new Promise((resolve, reject) => {
      chrome.identity.getAuthToken({ interactive }, (token) => {
        if (chrome.runtime.lastError) reject(chrome.runtime.lastError);
        else resolve(token);
      });
    });
  } else {
    // Firefox: use identity.launchWebAuthFlow
    // You must set your own OAuth client_id below for Firefox
    const CLIENT_ID = "YOUR_GOOGLE_OAUTH_CLIENT_ID.apps.googleusercontent.com";
    const REDIRECT = browser.identity.getRedirectURL();
    const scope = encodeURIComponent("https://www.googleapis.com/auth/drive.file");
    const url =
      `https://accounts.google.com/o/oauth2/auth` +
      `?client_id=${CLIENT_ID}` +
      `&redirect_uri=${encodeURIComponent(REDIRECT)}` +
      `&response_type=token` +
      `&scope=${scope}`;
    const result = await browser.identity.launchWebAuthFlow({ url, interactive });
    const params = new URLSearchParams(result.split("#")[1]);
    return params.get("access_token");
  }
}

// ─── Drive helpers ────────────────────────────────────────────────────────────

async function driveRequest(token, url, options = {}) {
  const res = await fetch(url, {
    ...options,
    headers: {
      Authorization: `Bearer ${token}`,
      ...(options.headers || {}),
    },
  });
  if (!res.ok) throw new Error(`Drive API error: ${res.status} ${await res.text()}`);
  return res.json();
}

async function getOrCreateFolder(token) {
  // Search for existing folder
  const q = encodeURIComponent(
    `name='${DRIVE_FOLDER_NAME}' and mimeType='application/vnd.google-apps.folder' and trashed=false`
  );
  const list = await driveRequest(token, `${DRIVE_API}/files?q=${q}&fields=files(id,name)`);
  if (list.files.length > 0) return list.files[0].id;

  // Create it
  const folder = await driveRequest(token, `${DRIVE_API}/files`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({
      name: DRIVE_FOLDER_NAME,
      mimeType: "application/vnd.google-apps.folder",
    }),
  });
  return folder.id;
}

async function uploadFileToDrive(token, folderId, filename, content) {
  const jsonContent = JSON.stringify(content, null, 2);

  // Check if file already exists
  const q = encodeURIComponent(
    `name='${filename}' and '${folderId}' in parents and trashed=false`
  );
  const list = await driveRequest(token, `${DRIVE_API}/files?q=${q}&fields=files(id)`);

  const metadata = { name: filename, parents: [folderId] };
  const blob = new Blob([jsonContent], { type: "application/json" });

  const form = new FormData();
  form.append("metadata", new Blob([JSON.stringify(metadata)], { type: "application/json" }));
  form.append("file", blob);

  if (list.files.length > 0) {
    // Update existing (don't send parents on update)
    const updateMeta = { name: filename };
    const updateForm = new FormData();
    updateForm.append("metadata", new Blob([JSON.stringify(updateMeta)], { type: "application/json" }));
    updateForm.append("file", blob);
    await fetch(`${DRIVE_UPLOAD}/files/${list.files[0].id}?uploadType=multipart`, {
      method: "PATCH",
      headers: { Authorization: `Bearer ${token}` },
      body: updateForm,
    });
    return list.files[0].id;
  } else {
    const res = await fetch(`${DRIVE_UPLOAD}/files?uploadType=multipart`, {
      method: "POST",
      headers: { Authorization: `Bearer ${token}` },
      body: form,
    });
    const data = await res.json();
    return data.id;
  }
}

async function readFileFromDrive(token, folderId, filename) {
  const q = encodeURIComponent(
    `name='${filename}' and '${folderId}' in parents and trashed=false`
  );
  const list = await driveRequest(token, `${DRIVE_API}/files?q=${q}&fields=files(id)`);
  if (list.files.length === 0) return null;

  const res = await fetch(`${DRIVE_API}/files/${list.files[0].id}?alt=media`, {
    headers: { Authorization: `Bearer ${token}` },
  });
  return res.json();
}

// ─── Data collectors ──────────────────────────────────────────────────────────

async function collectBookmarks() {
  return new Promise((resolve) => {
    ext.bookmarks.getTree((tree) => resolve(tree));
  });
}

async function collectHistory(daysBack = 30) {
  const startTime = Date.now() - daysBack * 24 * 60 * 60 * 1000;
  return new Promise((resolve) => {
    ext.history.search({ text: "", startTime, maxResults: 5000 }, (items) => {
      resolve(
        items.map(({ url, title, visitCount, lastVisitTime }) => ({
          url, title, visitCount, lastVisitTime,
        }))
      );
    });
  });
}

async function collectExtensions() {
  if (!IS_FIREFOX) {
    return new Promise((resolve) => {
      chrome.management.getAll((exts) => {
        resolve(
          exts
            .filter((e) => e.type === "extension" && e.id !== chrome.runtime.id)
            .map(({ name, id, enabled, homepageUrl }) => ({
              name,
              id,
              enabled,
              storeLink: homepageUrl || `https://chrome.google.com/webstore/detail/${id}`,
              browser: "chromium",
            }))
        );
      });
    });
  } else {
    const exts = await browser.management.getAll();
    return exts
      .filter((e) => e.type === "extension" && e.id !== browser.runtime.id)
      .map(({ name, id, enabled, homepageUrl }) => ({
        name,
        id,
        enabled,
        storeLink: homepageUrl || `https://addons.mozilla.org/en-US/firefox/addon/${id}/`,
        browser: "firefox",
      }));
  }
}

// ─── Backup ───────────────────────────────────────────────────────────────────

async function runBackup(sendStatus) {
  try {
    sendStatus("🔑 Authenticating...");
    const token = await getAuthToken(true);

    sendStatus("📁 Getting Drive folder...");
    const folderId = await getOrCreateFolder(token);

    sendStatus("🔖 Backing up bookmarks...");
    const bookmarks = await collectBookmarks();
    await uploadFileToDrive(token, folderId, "bookmarks.json", {
      exportedAt: new Date().toISOString(),
      browser: IS_FIREFOX ? "firefox" : "chromium",
      data: bookmarks,
    });

    sendStatus("🕐 Backing up history...");
    const history = await collectHistory(30);
    await uploadFileToDrive(token, folderId, "history.json", {
      exportedAt: new Date().toISOString(),
      days: 30,
      data: history,
    });

    sendStatus("🧩 Backing up extension list...");
    const extensions = await collectExtensions();
    await uploadFileToDrive(token, folderId, `extensions_${IS_FIREFOX ? "firefox" : "chromium"}.json`, {
      exportedAt: new Date().toISOString(),
      browser: IS_FIREFOX ? "firefox" : "chromium",
      data: extensions,
    });

    // Save last backup time
    ext.storage.local.set({ lastBackup: new Date().toISOString(), folderId });
    sendStatus("✅ Backup complete!");
  } catch (err) {
    sendStatus("❌ Error: " + err.message);
    console.error(err);
  }
}

// ─── Restore ──────────────────────────────────────────────────────────────────

async function runRestore(type, sendStatus) {
  try {
    sendStatus("🔑 Authenticating...");
    const token = await getAuthToken(true);

    const { folderId: savedFolder } = await ext.storage.local.get("folderId");
    sendStatus("📁 Finding backup folder...");
    const folderId = savedFolder || (await getOrCreateFolder(token));

    if (type === "bookmarks" || type === "all") {
      sendStatus("🔖 Restoring bookmarks...");
      const data = await readFileFromDrive(token, folderId, "bookmarks.json");
      if (data) {
        await restoreBookmarks(data.data);
        sendStatus("🔖 Bookmarks restored!");
      } else {
        sendStatus("⚠️ No bookmark backup found.");
      }
    }

    if (type === "extensions" || type === "all") {
      const filename = `extensions_${IS_FIREFOX ? "firefox" : "chromium"}.json`;
      sendStatus("🧩 Loading extension list...");
      const data = await readFileFromDrive(token, folderId, filename);
      if (data) {
        sendStatus("ready_extensions:" + JSON.stringify(data.data));
      } else {
        sendStatus("⚠️ No extension backup found for this browser.");
      }
    }
    if (type !== "extensions" && type !== "all") {
      sendStatus("✅ Restore complete!");
    }
  } catch (err) {
    sendStatus("❌ Error: " + err.message);
    console.error(err);
  }
}

async function restoreBookmarks(tree) {
  // Clear existing bookmarks bar and other bar, then import
  // We import into a new folder to be safe (don't nuke existing ones)
  const restoreRoot = await new Promise((res) => {
    ext.bookmarks.create({ title: `Restored ${new Date().toLocaleDateString()}` }, res);
  });

  async function importNode(node, parentId) {
    if (node.url) {
      await new Promise((res) =>
        ext.bookmarks.create({ parentId, title: node.title || node.url, url: node.url }, res)
      );
    } else if (node.children) {
      if (node.title && node.title !== "Bookmarks bar" && node.title !== "Other bookmarks") {
        const folder = await new Promise((res) =>
          ext.bookmarks.create({ parentId, title: node.title }, res)
        );
        for (const child of node.children) await importNode(child, folder.id);
      } else {
        for (const child of node.children) await importNode(child, parentId);
      }
    }
  }

  for (const rootNode of tree) await importNode(rootNode, restoreRoot.id);
}

// ─── Message handler ──────────────────────────────────────────────────────────

ext.runtime.onMessage.addListener((msg, _sender, sendResponse) => {
  if (msg.action === "backup") {
    runBackup((status) => {
      ext.runtime.sendMessage({ type: "status", text: status }).catch(() => {});
    });
    sendResponse({ ok: true });
  } else if (msg.action === "restore") {
    runRestore(msg.type || "all", (status) => {
      ext.runtime.sendMessage({ type: "status", text: status }).catch(() => {});
    });
    sendResponse({ ok: true });
  } else if (msg.action === "getLastBackup") {
    ext.storage.local.get("lastBackup", (data) => sendResponse(data));
    return true;
  }
  return true;
});

// ─── Auto-backup on startup (optional, configurable) ─────────────────────────

ext.runtime.onStartup.addListener(async () => {
  const { autoBackup, lastBackup } = await ext.storage.local.get(["autoBackup", "lastBackup"]);
  if (!autoBackup) return;
  const last = lastBackup ? new Date(lastBackup) : null;
  const now = new Date();
  if (!last || now - last > 24 * 60 * 60 * 1000) {
    // More than 24h since last backup → auto backup
    runBackup((status) => {
      ext.runtime.sendMessage({ type: "status", text: status }).catch(() => {});
    });
  }
});
